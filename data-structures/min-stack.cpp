/**
 * Farham Ahmad
 * Data Structure: MinStack with constant time {add, top, pop, get_min} operations.
 * 
 * The main idea is to store a pair of values, with the second element of the pair storing the minimum value at that 
 * stack layer and below. This value is induced during add.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class EmptyStackException : public std::exception {
public:
    char *what(){
        return "The stack is empty!";
    }
};

class MinStack {
private:
    std::vector<std::pair<int,int>> stack;

public:
    void add(int value){
        if (stack.size() == 0) {
            stack.push_back({value, value});
        } else {
            stack.push_back({value, std::min(stack.back().second, value)});
        }
    }

    int top(){
        if (stack.size() == 0) throw EmptyStackException();
        return stack.back().first;
    }

    void pop(){
        if (stack.size() == 0) throw EmptyStackException();
        stack.pop_back();
    }

    int get_min(){
        return stack.back().second;
    }
};

// --- TESTING ---

int main(){
    MinStack stack;
    stack.add(2);
    stack.add(5);
    stack.add(7);
    stack.add(1);

    std::cout << "top: " << stack.top() << " min: " << stack.get_min() << '\n';
    stack.pop();
    std::cout << "top: " << stack.top() << " min: " << stack.get_min() << '\n';

    try {
        while(true){
            stack.pop();
        }
    } catch (EmptyStackException e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}