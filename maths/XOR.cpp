/**
 * Farham Ahmad
 * 
 * Algorithm to determine the XOR from integer a to integer b in constant time.
 * Reference: https://math.stackexchange.com/questions/782634/xoring-consecutive-integers-has-an-interesting-property-does-anyone-know-why
*/

#include <iostream>
#include <assert.h>
#include <bitset>

class InvalidModulo : public std::exception {
public:
    char *what(){
        return "Failed to determine the modulo!";
    }
};

int xor_one_to_n(int n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n+1;
        case 3: return 0;
        default:
            throw InvalidModulo();
    }
}

int global_xor(int a, int b) {
    
    assert(a >= 0);
    assert(b >= 0);
    assert(a < b);

    int prev = (a == 0 ? 0 : xor_one_to_n(a-1));
    int end = xor_one_to_n(b);

    return prev ^ end;
}

int main() {
    // TESTING

    int ans = global_xor(2,5);
    std::bitset<32> binary(ans);
    std::cout << binary << '\n';

    return 0;
}