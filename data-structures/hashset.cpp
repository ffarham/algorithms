/**
 * Farham Ahmad
 * Data Structure: HashSet that supports {add, remove contains}.
*/

typedef long long lld;
    
struct Node {
    int value;
    Node* next;
};

class MyHashSet {
private:
    Node* hashtable[1000];
    
    int hash_function(int key){
        const lld x = key * key;
        return x % 1000;
    }
    
public:
    MyHashSet() {
        for (int i = 0; i < 1000; i++){
            hashtable[i] = nullptr;
        }
    }
    
    void add(int key) {
        if (contains(key)) return;
            
        const int hash_value = hash_function(key);
        
        Node *node = new Node();
        node->value = key;
        
        Node *next_node = hashtable[hash_value];
        node->next = next_node;
        
        hashtable[hash_value] = node;
        
    }
    
    void remove(int key) {
        const int hash_value = hash_function(key);
        
        Node *prev = hashtable[hash_value];
        if (prev == nullptr) return;

        if (prev->value == key) {
            Node *new_head = prev->next;
            delete hashtable[hash_value];
            hashtable[hash_value] = new_head;
            return;
        }
        
        Node *curr = prev->next;
        while (curr != nullptr){
            if (curr->value == key) {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        
    }
    
    bool contains(int key) {
       const int hash_value = hash_function(key);
        
        Node* prev = hashtable[hash_value];
        if (prev == nullptr) return false;

        if (prev->value == key) return true;
        
        Node *curr = prev->next;
        while (curr != nullptr){
            if (curr->value == key) {
                return true;
            }
            prev = curr;
            curr = curr->next;
        } 
        
        return false;
    }
};
