/**
 * Farham Ahmad
 * Data Structure: Singly Linked List
*/

struct Node{
    int value;
    Node* next;
};

class MyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    
public:
    MyLinkedList() {
        head = nullptr;
        size = 0;
    }
    
    int get(int index) {
        if (index+1 > size) return -1;
        
        int curr_index = 0;
        Node* curr = head;
        while(curr != nullptr){
            if (curr_index == index) return curr->value;
            curr_index++;
            curr = curr->next;
        }
        return -1;
    }
    
    void addAtHead(int val) {
        size++;
        
        Node* new_head = new Node;
        new_head->value = val;
        new_head->next = head;
        
        head = new_head;
    }
    
    void addAtTail(int val) {
        size++;
        
        Node* new_node = new Node;
        new_node->value = val;
        new_node->next = nullptr;
        
        // edge case: tail is the head
        if (head == nullptr){
            head = new_node;
            return;
        }
        
        Node* curr = head;
        while (curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = new_node;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size) return;
        
        size++;
        
        Node* new_node = new Node;
        new_node->value = val;
        
        // edge case: index = 0
        if (index == 0){
            new_node->next = head;
            head = new_node;
            return;
        }
        
        int curr_index = 0;
        Node* curr_node = head;
        while (curr_index < index-1){
            curr_node = curr_node->next;
            curr_index++;
        }
        new_node->next = curr_node->next;
        curr_node->next = new_node;
    }

    
    void deleteAtIndex(int index) {
        if (index >= size) return;
        
        size--;
        
        if (index == 0) {
            Node* new_head = head->next;
            delete head;
            head = new_head;
            return;
        }
        
        int curr_index = 0;
        Node* curr_node = head;
        while(curr_index < index-1){
            curr_index++;
            curr_node = curr_node->next;
        }
        
        Node* temp;
        if (curr_node->next != nullptr) {
            temp = (curr_node->next)->next;
        } else {
            temp = nullptr;
        }
        
        delete curr_node->next;
        curr_node->next = temp;
    }
};
