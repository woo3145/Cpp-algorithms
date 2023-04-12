#include <iostream>
#include <vector>
#include <algorithm>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::max;

int N;

int leftArr[2001];
int rightArr[2001];
int dp[2001][2001];

// https://www.acmicpc.net/problem/10835
// 카드게임 문제

void Input() {
    cin >> N;

    for(int i = 0; i < N; ++i){
        cin >> leftArr[i];
    }
    for(int i = 0; i < N; ++i){
        cin >> rightArr[i];
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            dp[i][j] = -1;
        }
    }
}

int recursive(int left, int right) {
    if(N < left || N < right) {
        return 0;
    }
    if(dp[left][right] != - 1) {
        return dp[left][right];
    }
    // 왼쪽카드만 버린경우/양쪽을 버린경우 중 큰값
    dp[left][right] = max(recursive(left+1, right), recursive(left+1, right+1));

    // 오른쪽 카드가 작으면 점수 추가
    if(leftArr[left] > rightArr[right]) {
        dp[left][right] = max(dp[left][right], recursive(left, right + 1) + rightArr[right]);
    }

    return dp[left][right];
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    
    cout << recursive(0, 0) << '\n';

    return 0;
}
