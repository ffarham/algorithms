/**
 * Farham Ahmad
 * Data Structure: Binary Search Tree node that supports {insert, contains} operations.
*/

#include <iostream>

class Node {
public:
    int val;
    Node *left, *right;
    
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
    Node(int value, Node *l, Node *r) : val(value), left(l), right(r) {}

    void insert(int value){
        if (value <= this->val){
            if (left == nullptr) left = new Node(value);
            else left->insert(value);
        } else {
            if (right == nullptr) right = new Node(value);
            else right->insert(value);
        }
    }

    bool contains(int value){
        if (value == this->val) return true;
        else if (value < this->val) {
            if (left == nullptr) return false;
            return left->contains(value);
        }
        else {
            if (right == nullptr) return false;
            return right->contains(value);
        }
    }

    void print_in_order(){
        if (this->left != nullptr) left->print_in_order();
        std::cout << this->val << " ";
        if (this->right != nullptr) right->print_in_order();
    }
};