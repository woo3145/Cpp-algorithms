#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::cin;

long long modPow (long long base, long long exp, long long mod) {
    long long ret = 1;
    while(exp){
        if(exp & 1) ret = (ret * base) % mod;
        base = (base*base) % mod;
        exp >>= 1;
    }
    return ret;
}

bool miller(long long num, long long seed){
    if(num % seed == 0) return num == seed;

    long long d = num - 1;
    while (d % 2 == 0) d /= 2;

    long long tmp = modPow(seed, d, num);
    if (tmp == 1 || tmp == num - 1) return false;

    while (d != num - 1) {
        tmp = (tmp * tmp) % num;
        d *= 2;

        if (tmp == 1) return true;
        if (tmp == num - 1) return false;
    }

    return true;
}


bool isPrime(long long num){
    if(num < 2 || num % 2 == 0){
        return num == 2;
    }

    vector<long long> seeds = {2, 3, 5, 7, 11, 13};

    for(const auto& seed : seeds){
        if(num == seed) return true;

        if(miller(num, seed)) return false;
    }  

    return true;
}

int main() {
    long long a = 2305843009213693951;

    cout << isPrime(a);
}
