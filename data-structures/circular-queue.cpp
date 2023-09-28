/**
 * Farham Ahmad
 * Data Structure: Circular queue using a fixed size vector.
 * 
 * We add enqueue from the head and dequeue from the tail. Thus the front of the queue is the tail.
*/

#include <vector>

class CircularQueue {
private:
    std::vector<int> queue;
    int head;
    int tail;
    int size;
    int max_size;
    
public:
    CircularQueue(int k) : head(0), tail(0), size(0), max_size(k) {
        queue.resize(k);
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        queue[head] = value;
        head = (head+1)%max_size;
        ++size;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        tail = (tail+1)%max_size;
        --size;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return queue[tail];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        int index = head == 0 ? max_size-1 : head-1;
        return queue[index];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == max_size;
    }
};
