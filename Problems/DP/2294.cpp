#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::ios;
using std::min;

#define MAX 999999999

// https://www.acmicpc.net/problem/2294
// 동전 2

// n가지 종류의 동전으로 목표가치 K를 만드는 동전의 최소 갯수를 구하는 문제
// 사용한 동전의 종류는 같고, 순서만 다른 경우 같은 경우로 침

int N, K;
int coin[100];
int dp[10001];

void Input() {
    cin >> N >> K;
    for(int i = 0; i < N; ++i){
        cin >> coin[i];
    }

    for(int i = 0; i <= K; ++i){
        dp[i] = MAX;
    }
}

void Solve() {
    dp[0] = 0;
    for(int c = 0; c < N; ++c){
        int value = coin[c];

        int cur = value;
        while(cur <= K){
            dp[cur] = min(dp[cur], dp[cur - value] + 1);
            ++cur;
        }
    }

    if(dp[K] == MAX) {
        cout << -1 << '\n';
    }else {
        cout << dp[K] << '\n';
    }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Input();
    Solve();
    return 0;
}
