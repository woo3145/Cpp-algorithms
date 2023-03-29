#include <iostream>
#include <cmath>

#define MAX_N 10000

unsigned char arr[(MAX_N + 7) / 8]; // 바이트당 숫자 8개 저장

// n << 1 : n의 제곱
// n >> 1 : n을 2로 나눈 몫
// 2의 제곱수로 나눈 수의 몫은 &연산으로 구할 수 있음
// ex) n % 8 == n & 7  /  n % 16 == n & 15

bool isPrime (int n) {
    return arr[n >> 3] & (1 << (n & 7));
}

void setComposite(int n) {
    arr[n >> 3] &= ~(1 << (n & 7));
}

// 에라토스테네스의 체
void eratos() {
    memset(arr, (1 << 8) - 1, sizeof(arr));

    setComposite(0);
    setComposite(1);

    int sqrtN = std::sqrt(MAX_N);
    for(int i = 2; i <= sqrtN; ++ i){
        if(isPrime(i)){
           for(int j = i * i; j <= MAX_N; j += i) {
            setComposite(j);
           } 
        }
    }
}

int main () {
    eratos();

    for(int i = 0; i < 100; ++i) {
        if(isPrime(i)) {
            std::cout << i << "\n";
        }
    }
    return 0;
}