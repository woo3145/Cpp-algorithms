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

int LCM (int a, int b) {
    return (a * b) / GCD(a, b);
}

int main () {
    std::cout << LCM(36, 40) << '\n'; // 360
    return 0; 
}