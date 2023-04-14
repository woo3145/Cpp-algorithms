#include <iostream>
#include <algorithm>

using std::ios;
using std::cout;
using std::cin;
using std::min;

// https://www.acmicpc.net/problem/10736
// XOR삼형제 2(애드 훅)
// 1~N의 정수에서 수열을 만들때 임의의 3개의 수를 XOR연산할때 0이 되지 않는 가장 긴 수열을 찾는문제
// 비트가 하나라도 살아있으면 됨으로 수열의 범위를 가장왼쪽비트, 두번째비트가 하나씩 켜진 범위로 잡으면 된다.
// ex)
// A: 1 X 0 0 0 0 0 0
// B: 0 1 0 0 0 0 0 0
// X에는 1이 들어가면 안된다. 이유는 B이상의 수를 고를때 3개를 고르면 "항상" 두번째 비트가 켜지기 때문에
// X에 1이 들어가면 0으로 만들 수 있기 때문이다.

// 추가로 최대 길이를 위해 A의 범위를 1 X 1 1 1 1 1 1로 잡아두고 해당 값이 N보다 클경우 N까지로 잡는다.


int N;

void Input() {
    cin >> N;
}

void Solve() {
    if(N == 1) {
        cout << "1\n1\n";
        return;
    }
    int firstBit = 1;

    // N의 가장 왼쪽 비트를 구한다.
    while(firstBit << 1 <= N) {
        firstBit <<= 1;
    }
    int secondBit = firstBit >> 1;
    
    int max = min(N + 1, firstBit | secondBit);

    cout << max - secondBit << '\n';
    for(int i = secondBit; i < max; ++i) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;

    for(int i = 0; i < T; ++i){
        Input();
        Solve();
    }

    return 0;
}


/* Input
2
28
33
*/
/* Output
16
8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
18
16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
*/