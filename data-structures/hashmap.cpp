/**
 * Farham Ahmad
 * Data Structure: HashMap that supports {put, get, remove} operations.
*/

typedef long long lld;

struct Node {
    int key;
    int value;
    Node *next;
};

class MyHashMap {
private:
    Node* hashtable[1000];
    int hash_function(int key) {
        const lld x = key * key;
        return x % 1000;
    }
public:
    MyHashMap() {
        for (int i = 0; i < 1000; i++){
            hashtable[i] = nullptr;
        }
    }
    
    void put(int key, int value) {
        const int hash_value = hash_function(key);
        
        Node *node = new Node();
        node->key = key;
        node->value = value;
        
        Node *next_node = hashtable[hash_value];
        node->next = next_node;
        
        hashtable[hash_value] = node;
    }
    
    int get(int key) {
        const int hash_value = hash_function(key);
        
        Node *prev = hashtable[hash_value];
        
        if (prev == nullptr) return -1;
        if (prev->key == key) return prev->value;
        
        Node *curr = prev->next;
        while (curr != nullptr) {
            if (curr->key == key) return curr->value;
            prev = curr;
            curr = curr->next;
        }
        return -1;
    }
    
    void remove(int key) {
        const int hash_value = hash_function(key);
        
        Node *prev = hashtable[hash_value];
        
        if (prev == nullptr) return;
        if (prev->key == key) {
            delete hashtable[hash_value];
            hashtable[hash_value] = prev->next;
        }
        
        Node *curr = prev->next;
        while (curr != nullptr) {
            if (curr->key == key) {
                prev->next = curr->next;
                delete curr;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};
