/**
 * Farham Ahmad
 * Data Structure: TwoStackQueue with constant time operations on average.
 * 
 * An element is added to the primary stack in constant time. To remove an element in O(1) on average, we use the 
 * secondary queue to maintain the reversed state of the primary stack. The refill method is used to empty the 
 * primary stack and populate the secondary stack. Using this approach, we can achieve constant time pop and peek 
 * operations on average as any one element is moved from the primary stack to the secondary stack only once.
 * 
*/

#include <vector>

class TwoStackQueue {
private:
    std::vector<int> primary;
    std::vector<int> secondary;
    
    void refill(){
        while(primary.size() > 0){
            secondary.push_back(primary.back());
            primary.pop_back();
        }
    }
    
public:
    
    void push(int x) {
        primary.push_back(x);
    }
    
    int pop() {
        if (secondary.size() == 0) refill();
        const int output = secondary.back();
        secondary.pop_back();
        return output;
    }
    
    int peek() {
        if (secondary.size() == 0) refill();
        return secondary.back();
    }
    
    bool empty() {
        return primary.size() == 0 && secondary.size() == 0;
    }
};