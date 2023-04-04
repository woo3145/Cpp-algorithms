#include <iostream>

#define MAX_N 31

// 2*n 타일링(1*2, 2*1, 2*2)
void Tiling_2xN(int n) {
    int dp[MAX_N];
    dp[1] = 1;
    dp[2] = 3;

    for(int i = 3; i < MAX_N; ++i){
        dp[i] = (dp[i-1] + 2 * dp[i-2]) % 10007;
    }
    std::cout << dp[n] << '\n';
}

// 3*n 타일링(1*2, 2*1)
void Tiling_3xN(int n) {
    int dp[MAX_N] = {0};
    int dpSum[MAX_N] = {0}; // dp의 누적합 (dpSum[6] = dp[2] + dp[4] + dp[6])
    dp[2] = 3; dpSum[2] = 3;
    
    // 예시
    dp[4] = dp[2]*3 + 2; // 나눠지지 않는 2개의 예외 (중간에 1*2가 껴있는 경우)
    dp[6] = dp[4]*3 + dp[2]*2 + 2;
    // 6의 경우: dp[4] * 2칸을 채우는 경우의 수 3
    // dp[2] * 4칸을 채우는 예외모양 2, 
    // 6칸을 채우는 예외모양 2
    dp[8] = dp[6]*3 + dp[4]*2 + dp[2]*2 + 2;
    // 위처럼 4이상부터는 예외모양이 2개씩 늘어나기 때문에 처리를 해줘야한다.

    for(int i = 4; i < MAX_N; i += 2){
        dp[i] = dp[i-2]*3 + dpSum[i-4]*2 + 2;
        dpSum[i] = dp[i] + dpSum[i-2];

        // 누적합 배열을 사용하지 않을 경우 매번 누적합 계산 (dp[0]에 1을 넣어줘야함)
        // dp[i] = dp[i-2]*3;
        // for(int j = i-4; 0 <= j; j -= 2){
        //     dp[i] += dp[j] * 2;
        // }
    }

    std::cout << dp[n] << '\n'; // 571
}


int main() {
    Tiling_2xN(8); // 171
    Tiling_3xN(8); // 153
    return 0;
}