/**
 * Farham Ahmad
 * Data Structure: Least Recently Used Cache with constant time {add, find} operations.
*/

#include <stdint.h>
#include <unordered_map>


#define MAX_CACHE_CAPACITY 100
#define MEMORY_ADDRESS uint64_t


/**
 * The primary data structure used to maintain the cache is a queue implemented as a doubly-linked list.
 * The doubly-linked list with pointers to the head and tail allow us to pop the least recently used element
 * from the tail of the queue, and add the most recently used element from the head of the queue in constant
 * time. To also determine if an element exists, and move it to the back of the queue in constant time, we
 * use a hashmap to store the address of the list node in cache. This allows us to quickly access the list 
 * node instead of having to traverse the doubly-linked list. The cache node must also store the address of the 
 * memory location of its value to allow efficient (constant time on average) deletion of its entry in the 
 * hashmap, when that node is popped off from the queue.
 * 
 * To ensure cache consistency, we invalidate the cache by deleting the node representing the memory location 
 * that has either been updated or deleted. An alternative is 'Write Through Caching' where we do two writes,
 * the first to update the cache and the second to update the memory. However, two writes is expensive. An 
 * improvement is 'Write Behind Caching' where we update the cache and then update the memory asynchronously.
 * For the purpose of implementation, we simply invalidate the cache.
 * 
 * Note: M2 uses 64-bit architecture, so pointers will be 64 bits
*/

struct Node {
    MEMORY_ADDRESS address;
    int32_t value;     
    Node *prev;        
    Node *next;        
};

struct LRU_Queue{
    Node *head;
    Node *tail;
    uint8_t capacity; 
};

class LRU_Cache {
private:

    LRU_Queue queue;
    std::unordered_map<MEMORY_ADDRESS, Node*> hashmap;

public: 

    void add(MEMORY_ADDRESS address, int32_t value){
        if (queue.capacity == MAX_CACHE_CAPACITY) pop();
        
        Node *new_node = new Node();
        new_node->address = address;
        new_node->value = value;
        new_node->next = queue.head ? queue.head : nullptr;
        new_node->prev = nullptr;

        queue.head = new_node;
        if (queue.capacity == 0) queue.tail = queue.head;

        hashmap[address] = new_node;
        ++queue.capacity;
    } 

    void pop(){
        if (queue.capacity == 0) return;

        auto position = hashmap.find(queue.tail->address);
        hashmap.erase(position);

        if (queue.capacity == 1)
        {  
            delete queue.tail;
            queue.head = nullptr;
            queue.tail = nullptr;
        }
        else 
        {
            Node *temp = queue.tail->prev;
            delete queue.tail;
            queue.tail = temp;
        }

        --queue.capacity;
    }

    int32_t find(MEMORY_ADDRESS address){
        auto position = hashmap.find(address);
        if (position == hashmap.end()) return NULL;

        // handle a cache hit
        Node *node = position->second;
        if (address == queue.head->address) return node->value;

        Node *prev = node->prev;
        Node *next = node->next;
        if (prev) prev->next = next;
        if (next) next->prev = prev;

        node->prev == nullptr;
        node->next = queue.head;
        queue.head = node;

        return node->value;
    }

    void invalidate_cache(MEMORY_ADDRESS address){
        auto position = hashmap.find(address);
        if (position == hashmap.end()) return;

        hashmap.erase(position);

        if (queue.capacity == 1)
        {
            delete queue.head;
            queue.head = nullptr;
            queue.tail == nullptr;
        }
        else if (address == queue.head->address)
        {
            Node *temp = queue.head->next;
            delete queue.head;
            queue.head = temp;
        }
        else if (address == queue.tail->address)
        {
            Node *temp = queue.tail->prev;
            delete queue.tail;
            queue.tail = temp;
        }
        else
        {
            Node *node = position->second;

            Node *prev = node->prev;
            Node *next = node->next;
            prev->next = next;
            next->prev = prev;

            delete node;
        }

        --queue.capacity;
    }
};

