#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::min;
using std::max;
using std::pair;
using std::queue;

// https://www.acmicpc.net/problem/17142
// 연구소 3 (조합, bfs)

// 애먹은점
// - 감염시간 계산 시 비활성 바이러스 고려

int N, M;
int board[51][51];
int copyBoard[51][51];
bool visited[51][51];
vector<pair<int, int>> virus;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void Input() {
    cin >> N >> M;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cin >> board[i][j];

            if(board[i][j] == 2) {
                virus.push_back({i, j});
            }
        }
    }
}

// 바이러스를 활성화 시킬 조합을 구하는 함수
void CalcCombination(int r, int idx, vector<pair<int, int>>& cur, vector<vector<pair<int, int>>>& result) {
    if(r == 0) {
        result.push_back(cur);
        return;
    }

    for(int i = idx; i <= virus.size() - r; ++i){
        cur.push_back(virus[i]);
        CalcCombination(r - 1, i + 1, cur, result);
        cur.pop_back();
    }
}

// 모든칸을 감염시킨 시간을 구하는 함수
int Check() {
    int day = 1; // 감염시킬 모든 구역이 바이러스일 경우 1 
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j){
            if(copyBoard[i][j] == 0) return -1; // 감염을 못시킨 구역이 있으면 -1

            if(board[i][j] != 1 && board[i][j] != 2) { // 빈구역 이였던 구역만 계산
                day = max(day, copyBoard[i][j]);
            }
        }
    }
    return day;
}

// 방문배열, 기록배열 초기화
void Init() {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j){
            visited[i][j] = false;
            copyBoard[i][j] = 0;
            if(board[i][j] == 1) {
                copyBoard[i][j] = -1;
            }
        }
    }
}

void Solve() {
    vector<pair<int, int>> temp;
    vector<vector<pair<int, int>>> comb;

    CalcCombination(M, 0, temp, comb);

    int answer = 0;

    for(auto c : comb) {
        queue<pair<int, int>> que;
        Init();

        for(auto& v : c) {
            que.push(v);
            copyBoard[v.first][v.second] = 1;
            visited[v.first][v.second] = true;
        }

        while(!que.empty()) {
            pair<int, int> pos = que.front();
            que.pop();

            for(int i = 0; i < 4; ++i) {
                int ny = pos.first + dy[i];
                int nx = pos.second + dx[i];

                if(ny < 0 || N <= ny || nx < 0 || N <= nx) continue;
                if(visited[ny][nx]) continue;

                if(copyBoard[ny][nx] != 0) continue;
                    
                copyBoard[ny][nx] = copyBoard[pos.first][pos.second] + 1;
                visited[ny][nx] = true;
                que.push({ny, nx});
            }
        }

        int day = Check();
        if(day != -1) {
            answer = answer == 0 ? day : min(answer, day);
        }
    }

    cout << answer - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Input();
    Solve();
    
    return 0;
}
