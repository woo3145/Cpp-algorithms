#include <iostream>

using std::ios;
using std::cout;
using std::cin;

// 카탈란 수(Catalan Number)

// C0 = 1
// C1 = C0*C0
// C2 = C0*C1 + C1*C0
// C3 = C0*C2 + C1*C1 + C2*C0
// C4 = C0*C3 + C1*C2 + C2*C1 + C3*C0
// Cn = C0*Cn-1 + ... Cn-1*C0

// *활용 문제
// 대각선을 피해가는 경로 
// 최적 이진탐색트리 
// 연쇄 행렬 곱셈 최적화
// 올바른 괄호의 경우의 수
// 다각형 나누기 ...

const int MAX = 10001;
const int MOD = 1000000007;

int N;
long long dp[MAX];

void Input() {
    cin >> N;
}

void Catalan() {
    dp[0] = 1;

    for(int i = 1; i < MAX; ++i) {
        dp[i] = 0;
        for(int j = 0; j < i; ++j) {
            dp[i] += dp[j] * dp[i-1-j];
            dp[i] %= MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Catalan();
    cout << dp[N] << '\n';
}
