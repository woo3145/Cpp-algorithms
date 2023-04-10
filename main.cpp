#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::set;
using std::min;

#define INF 999999999

struct comp {
    bool operator() (const int& left, const int& right) const {
        return left > right;
    }
};

int N, M;
vector<int> dp;
int wok[1001];
set<int, comp> woks;


void Input() {
    cin >> N >> M;
    dp.assign(10001, INF);
    for(int i = 0; i < M; ++i){
        cin >> wok[i];
        woks.insert(wok[i]);
    }
}

void Solve() {
    for(int i = 0; i < M - 1; ++i){
        for(int j = i + 1; j < M; ++j){
            if(wok[i] + wok[j] > 10000) continue;
            woks.insert(wok[i] + wok[j]);
        }
    }
    set<int,comp>::iterator iter;

    for(iter = woks.begin(); iter != woks.end(); ++iter){
        int n = *iter;
        dp[n] = 1;
        for(int i = n + 1; i <= N; ++i){
            if(dp[i-n] == INF) continue;
            dp[i] = min(dp[i], dp[i-n] + 1);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    if(dp[N] == INF) {
        cout << -1 << '\n';
    }else {
        cout << dp[N] << '\n';
    }

    return 0;
}

