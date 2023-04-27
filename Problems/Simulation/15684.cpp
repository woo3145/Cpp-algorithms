#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::min;

// https://www.acmicpc.net/problem/15684
// 사다리 조작 문제

int N, M, H;
vector<vector<int>> board;

int answer = -1;

void Input() {
    cin >> N >> M >> H;
    board.assign(H + 1, vector<int>(N + 1));

    for(int i = 0; i < M; ++i){
        int a, b;
        cin >> a >> b;
        board[a][b] = 1;
        board[a][b+1] = -1;
    }
}

bool IsConnectable(int height, int num) {
    return board[height][num] == 0 && board[height][num+1] == 0;
}

void Connect(int height, int num) {
    board[height][num] = 1;
    board[height][num + 1] = -1;
}
void UnConnect(int height, int num){
    board[height][num] = 0;
    board[height][num + 1] = 0;
}

bool Check() {
    bool valid = true;
    for(int i = 1; i <= N; ++i){
        int cur = i;
        for(int j = 1; j <= H; ++j){
            cur += board[j][cur];
        }
        if(cur != i) {
            valid = false;
            break;
        }
    }
    return valid;
}

void Backtracking (int height, int num, int cnt) {
    if(3 < cnt) return;
    if(Check()) {
        if(answer == -1 || cnt < answer) {
            answer = cnt;
        }
        return;
    }

    for(int i = height; i <= H; ++i){
        for(int j = i == height ? num : 1; j < N; ++j){
            if(IsConnectable(i, j)) {
                Connect(i, j);
                Backtracking(i, j, cnt + 1);
                UnConnect(i, j);
            }
        }
    }
}

void Solve() {
    Backtracking(1, 1, 0);

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Input();
    Solve();
    
    return 0;
}
