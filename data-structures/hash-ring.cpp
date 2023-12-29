/**
 * Farham Ahmad
 * Data Structure: Consistent Hashing based on an abstract hash-ring (see
 * reference 1).
 * 
 * To map an object on the hash-ring, we use the build in hash on strings.
 * The hash-ring will be implemented as a binary search tree using the c++
 * set class, similar to ordered set implementation of reference
 * 3. Each server node will be replicated as virtual nodes 'replication
 * factor' number of times.
 * 
 * The reason why the replication factor is set to 200 because the results
 * of reference 4 suggests that 'one or two hundered replicas achieves an
 * acceptable balance'. When distributing 10,000 keys to 10 servers with 
 * 200 virtual nodes for each server on the hash ring, using the built in
 * hash function, we get a 4.6% standard deviation from mean of 1000.
 * 
 * 
 * References:
 * 1. https://en.wikipedia.org/wiki/Consistent_hashing
 * 2. https://stackoverflow.com/questions/11871245/knuth-multiplicative-hash
 * 3. https://github.com/lafikl/consistent/blob/master/consistent.go
 * 4. https://tom-e-white.com/2007/11/consistent-hashing.html
*/

#include <iostream>
#include <string>
#include <stdint.h>
#include <math.h>
#include <numeric>
#include <set>
#include <unordered_map>
#include <assert.h>


class HashRing {
private:

  const int replication_factor = 200;
  std::set<std::size_t> hash_ring;
  std::unordered_map<std::size_t, int> hash2server;
  std::unordered_map<int, std::vector<std::size_t>> server2hashes;

public:

  HashRing(){}

  void insert(int id) {

    std::vector<std::size_t> hashes;

    for (int i = 0; i < replication_factor; i++)
    {
      std::string value = "server "+std::to_string(id)+ " version " + std::to_string(i);
      std::size_t hash_value = std::hash<std::string>{}(value);

      // NOTE: assuming no collisions
      hashes.push_back(hash_value);
      hash_ring.insert(hash_value);
      hash2server.insert({hash_value, id});
    }
    server2hashes.insert({id, hashes});
  }

  void remove(int id) 
  {
    auto hashes = server2hashes[id];

    for (auto hash : hashes) {
      auto pos = hash_ring.find(hash);
      assert (pos != hash_ring.end());
      hash_ring.erase(pos);
    }
  }

  int assign(int id)
  {
    std::string value = "key " + std::to_string(id);
    std::size_t hash_value = std::hash<std::string>{}(value);

    auto pos = hash_ring.upper_bound(hash_value); // O(log n)
    std::size_t hashed_server = (pos == hash_ring.end()) 
      ? *hash_ring.begin() 
      : *pos;
    return hash2server[hashed_server];

  }

  friend std::ostream& operator<<(std::ostream& os, const HashRing& hr);

};

std::ostream& operator<<(std::ostream& os, const HashRing& hr) { 
    os << "HASH RING:\n";
    for (auto item: hr.hash_ring) {
      int server = hr.hash2server.find(item)->second;
      os << server << ' ';
    }
    os << '\n';
    return os;
  }

int main() {
  // DEVELOPMENT AND TESTING

  HashRing hr;
  const int servers = 10;
  std::vector<double> server_allocations;

  for (int i = 0; i < servers; i++) {
    hr.insert(i);
    server_allocations.push_back(0);
  }
  std::cout << hr << '\n';

  for (int k = 0; k < 10000; k++) {
    int server = hr.assign(k);
    server_allocations[server]++;
  }
  
  for (int server = 0; server < servers; server++){
    std::cout << "server: " << server << " allocations: " << server_allocations[server] << '\n'; 
  }

  double sum = std::accumulate(server_allocations.begin(), server_allocations.end(), 0);
  double mean = sum / server_allocations.size();

  double accum = 0.0;
  std::for_each (std::begin(server_allocations), std::end(server_allocations), [&](const double d) {
      accum += (d - mean) * (d - mean);
  });
  double stdev = sqrt(accum / (server_allocations.size()-1));

  std::cout << "\nSTATS:\n";
  std::cout << "MEAN: " << mean << '\n';
  std::cout << "STD DEV: " << stdev << '\n';

  return 0;
} 