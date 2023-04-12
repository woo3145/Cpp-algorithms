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

void Input() {
    cin >> N;

    for(int i = 0; i < N; ++i){
        cin >> leftArr[i];
    }
    for(int i = 0; i < N; ++i){
        cin >> rightArr[i];
    }
}

void Solve() {
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            if(i == 0 || j == 0) {
                dp[i][j] = leftArr[i] > rightArr[j] ? rightArr[j] : 0;
                continue;
            }

            if(leftArr[i] > rightArr[j]) {
                dp[i][j] = dp[i][j - 1] + rightArr[j];
            }else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]);
            }
        }
    }

    cout << dp[N-1][N-1] << '\n';
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    return 0;
}


