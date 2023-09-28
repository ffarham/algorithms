/**
 * Farham Ahmad
 * Data Structure: Trie that supports {add, contains, remove, k_complete}
 * 
 * The k_complete method takes a partial string and returns at most k words that complete the given
 * string. It can be used to auto-complete, recommend or hint to the user based on their input.
*/


#include <iostream>
#include <string>
#include <vector>
#include <queue>

struct Node {
    std::vector<Node*> neighbours;
    char value;
    bool is_valid;
};

class Trie {
public:
    Node *root;

    Trie() {
        root = new Node;
        root->value = '.';
        root->is_valid = false;
    }

    ~Trie(){
        // do a BFS to deallocate all nodes used in the Trie
        std::queue<Node*> work;
        work.push(root);

        while(work.size() != 0)
        {
            Node *node = work.front();
            work.pop();

            for (Node *neighbour : node->neighbours)
            {
                work.push(neighbour);
            }

            delete node;
        }
    }

    void add(std::string str) {
        if (str.length() == 0) return;

        Node *trie_ptr = root;
        for (char& c : str)
        {
            bool found_neighbour = false;
            for (Node *neighbour : trie_ptr->neighbours){
                if (neighbour->value == c)
                {
                    trie_ptr = neighbour;
                    found_neighbour = true;
                    break;
                }
            }
            if (found_neighbour) continue;

            Node *node = new Node;
            node->value = c;
            node->is_valid = false;

            trie_ptr->neighbours.push_back(node);
            trie_ptr = node;

        }

        trie_ptr->is_valid = true;
    }

    bool contains(std::string str) {
        Node *curr = root;
        for (char& c : str)
        {
            bool found_neighbour = false;
            for (Node *node : curr->neighbours)
            {
                if (node->value == c)
                {
                    found_neighbour = true;
                    curr = node;
                    break;   
                }
            }
            if (!found_neighbour) return false;
        }
        return curr->is_valid;
    }

    std::vector<std::string> k_complete(std::string partial_str, int k){
        std::vector<std::string> output;
        int counter = 0;
        
        // find the end at the end of the partial string
        Node *curr = root;
        for (char& c : partial_str)
        {   
            bool found_neighbour = false;
            for (Node *neighbour : curr->neighbours)
            {
                if (neighbour->value == c)
                {
                    curr = neighbour;
                    found_neighbour = true;
                    break;
                }
            }
            if (!found_neighbour) return output;
        }

        // do a BFS starting from the current node
        std::queue<std::pair<std::string, Node*>> candidates;
        partial_str.pop_back();
        candidates.push({partial_str, curr});

        while(!candidates.empty())
        {
            auto pair = candidates.front();
            candidates.pop();
            
            std::string str = pair.first;
            Node *node = pair.second;

            str.push_back(node->value);
            if (node->is_valid)
            {
                output.push_back(str);
                ++counter;
                if (counter == k) break;
            }
            

            for (Node *neighbour : node->neighbours)
            {
                candidates.push({str, neighbour});
            }
        }
        
        return output;
    }
};

int main() {
    std::vector<std::string> inputs = {"library", "library entrance", "library cafe", "old library", "libra", "lime", "lambda"};
    std::vector<std::string> valid_tests = {"library", "lambda", "lime", "library cafe"};
    std::vector<std::string> invalid_tests = {"lib", "lamb", "library cache"};

    Trie *store = new Trie();
    for (auto input : inputs){
        store->add(input);
    }

    int counter = 1;
    for (auto test : valid_tests){
        const bool check = store->contains(test);
        if (check) std::cout << "PASSED TEST CASE " << counter << '\n';
        else {
            std::cout << "FAILED TEST CASE " << counter << '\n';
            std::cout << "Expecting <" << test << "> to be in the trie store.\n"; 
        }
        ++counter;
    }

    for (auto test : valid_tests){
        const bool check = store->contains(test);
        if (check) std::cout << "PASSED TEST CASE " << counter << '\n';
        else {
            std::cout << "FAILED TEST CASE " << counter << '\n';
            std::cout << "Expecting <" << test << "> to not be in the trie store.\n"; 
        }
        ++counter;
    }

    auto candidates = store->k_complete("lib", 10);
    std::cout << "Candidates of 'lib: ";
    for (auto candidate : candidates){
        std::cout << candidate << " ";
    }
    std::cout << '\n';


    delete store;
}