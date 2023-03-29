#include <iostream>

int GCD (int a , int b) {
    int mod = a % b;
    while(mod != 0) {
        a = b;
        b = mod;
        mod = a % b;
    }
    return b;
}

int main () {
    std::cout << GCD(36, 40) << '\n'; // 4
    return 0; 
}