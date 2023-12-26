#include <vector>
#include <iostream>

#define ull unsigned long long

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
    // 나머지가 1이라면 위의 페르마 소정리 2번에 따라 a^(d*2^(r-1))(mod N)가 -1 or 1일 수 있기 때문에 판단보류
// d가 홀수라면(마지막) 나머지가 -1 또는 1이 나오면 소수일 가능성이 존재한다.


ull modPow(ull base, ull p, ull mod) {
    ull ret = 1;
    base = base % mod;
    while(p) {
        if(p & 1) ret = (ret * base) % mod;
        base = (base * base) % mod;
        p >>= 1;
    }
    return ret;
}

// true: 합성수
// false: 소수일 가능성
bool miller_rabin(ull num, ull seed) {
    if (num % seed == 0) return true;

    ull d = num - 1;
    while (1) {
		ull tmp = modPow(seed, d, num);
		if (d & 1)
			return (tmp != 1 && tmp != num - 1); // d가 1도 안되고 -1도 안되면 합성수 (false)
		else if (tmp == num - 1) // a^(d*2^r)(mod N)이 -1이라면 소수일 가능성 (결과가 1이면 페르마 정리 2번에 따라 다시 나눠짐)
                                // (나머지가 1이라면 위의 페르마 소정리 2번에 따라 a^(d*2^(r-1))(mod N)가 -1 or 1일 수 있기 때문에 판단보류)
			return 0;
		d >>= 1;

       
	}


    return true;
}

bool isPrime(ull n) {
	if (n < 2 || (n % 2 == 0))
		return (n == 2);

	vector<ull> seeds({2, 7, 61});
	
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
}