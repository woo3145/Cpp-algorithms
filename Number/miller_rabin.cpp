#include <vector>
#include <iostream>

#define lint unsigned long long

using std::vector;
using std::cout;
using std::cin;


// 페르마의 소정리
// 1. 소수 p와 정수 a에 대해 다음을 만족함 (a는 p의 배수가 아님)

// a^p(mod p) = a(mod p)
// a^(p-1)(mod p) = 1

// 2. 소수 p에 대해 x^2(mod p) = 1이라면, x(mod p) = -1 or x(mod p) = 1 이다.


// 밀러-라빈 소수 판별

// N이 소수일때 N-1은 짝수가 된다.
// 따라서 다음과 같이 정리 가능 :  N-1 = d * 2^r  (d는 홀수)

// N이 소수라면 정수 a에 대해 페르마의 소정리를 만족하게 된다.
// a^(N-1)(mod N) = 1, a^(d*2^r)(mod N) = 1

// 따라서 d = N-1 부터 2로 나누며 거듭제곱 모듈러 연산을 한다.
// d가 짝수라면 나머지가 -1일때 소수일 가능성이 존재한다.
    // (거듭제곱의 모듈러 연산 결과가 -1이 나오는건 합성수에선 매우 드문 현상)
// d가 홀수라면(마지막) 나머지가 -1 또는 1이 나오면 소수일 가능성이 존재한다.


lint modPow(lint base, lint exp, lint mod) {
    lint ret = 1;
    base = base % mod;
    while(exp) {
        if(exp & 1) ret = ((__int128_t)ret * base) % mod;
        base = ((__int128_t)base * base) % mod;
        exp >>= 1;
    }
    return ret;
}

// true: 합성수
// false: 소수일 가능성
bool miller_rabin(lint num, lint seed) {
    if (num % seed == 0) return true;

    lint d = num - 1;
    while (1) {
		lint tmp = modPow(seed, d, num);
		if (d & 1)
			return (tmp != 1 && tmp != num - 1); // d가 1도 안되고 -1도 안되면 합성수 (false)
		else if (tmp == num - 1) // a^(d*2^r)(mod N)이 -1이라면 소수일 가능성 
			return 0;
		d >>= 1;
	}

    return true;
}

bool isPrime(lint n) {
	if (n < 2 || (n % 2 == 0))
		return (n == 2);

	vector<lint> seeds({2, 7, 61});
	
	for(auto& seed : seeds) {
		if (n == seed)
			return 1;
		if (miller_rabin(n, seed))
			return 0;
	}
	return 1;
}

int main () {

    for(int i = 0; i < 1000; ++i){
        if(isPrime(i)) {
            cout << i << '\n';
        }
    }

    cout << isPrime(2305843009213693952) << '\n';
}