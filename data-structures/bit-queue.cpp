/**
 * Farham Ahmad
 * Data Structure: Bit Queue maintained by an unsigned 64 bit integer.
 * 
 * Notes: least significant bit is the most recent bit added.
*/

#include <iostream>
#include <stdint.h>

#define MAX_QUEUE_SIZE 64

class BitQueue {
private:
    uint64_t queue;         
    int valid_bits;     // count of the 64 bits that are valid

public:
    BitQueue() : valid_bits(0), queue(0) {}

    void push(int value, int bit_size){
        if (valid_bits + bit_size > MAX_QUEUE_SIZE) return;

        if (valid_bits != 0) this->queue <<= bit_size;
        this->queue |= value;
        this->valid_bits += bit_size;
    }

    uint64_t pop(int bit_size){
        if (bit_size > valid_bits) return -1;
        if (bit_size == 64) return this->queue;

        const int remaining = valid_bits - bit_size;
        const uint64_t output = (queue & (((1 << bit_size) - 1) << remaining)) >> remaining;
        queue &= (1 << remaining) - 1;
        this->valid_bits -= bit_size;
        return output;
    }
};

int main()
{
    BitQueue *bitQ = new BitQueue();
    bitQ->push(275, 9);
    bitQ->push(515, 10);
    printf("%lld\n", bitQ->pop(9));
    printf("%lld\n", bitQ->pop(10));
    
    delete bitQ;
    
    return 0;
}