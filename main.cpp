#include <iostream>
#include <vector>

#define MOD 1000000007

using std::vector;
using std::ios;

int N;
vector<long long> dp;
vector<long long> dpSum;

void Input() {
    std::cin >> N;
    dp.assign(N+1, 0);
    dpSum.assign(N+1, 0);
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    Input();
    dp[1] = 2;
    dp[2] = 7;
    dpSum[2] = 1; // dpSum[3]부터 2가지 방법이 추가됨으로 임시값

    for(int i = 3; i <= N; ++i){
        dpSum[i] = (dp[i-3] + dpSum[i-1]) % MOD;
        dp[i] = (2 * dp[i-1] + 3 * dp[i-2] + 2 * dpSum[i]) % MOD;
    }
    std::cout << dp[N] << '\n';

    return 0;
}