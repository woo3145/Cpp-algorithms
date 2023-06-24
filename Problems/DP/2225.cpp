#include <iostream>

using std::cin;
using std::cout;
using std::ios;

#define MOD 1000000000

// https://www.acmicpc.net/problem/2225
// 합분해

// 0 <= N <= 200사이의 정수 K개로 N을 만드는 경우의 수를 구하는 문제
// 이차원 dp를 사용하는 문제
//          0~N
// 1  1  1  1  1  1  1  1
// 1  2  3  4  5  6  7  8     K == 사용한 정수의 갯수
// 1  3  6  10 15 21 28 36

int N, K;
int dp[201][201];

void Input() {
    cin >> N >> K;
}

void Solve() {
    dp[0][0] = 1;

    for(int i = 1; i <= K; ++i){
        for(int j = 0; j <= N; ++j){
            // 0을 만드는 경우의 수는 0만 사용하는 경우 한가지임
            if(j == 0) {
                dp[i][j] = 1;
                continue;
            }
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
            dp[i][j] %= MOD;
        }
    }
    
    cout << dp[K][N];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    return 0;
}
