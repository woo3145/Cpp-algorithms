#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::ios;
using std::map;
using std::vector;
using std::sort;

// https://www.acmicpc.net/problem/16235
// 나무 재테크 

// 간단한 구현문제

int N, M, K;
int board[11][11];
int memo[11][11];

vector<int> trees[11][11];
vector<int> dead[11][11];

int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void Input() {
    cin >> N >> M >> K;

    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            int n;
            cin >> n;
            board[i][j] = n;
            memo[i][j] = 5;
        }
    }

    for(int i = 0; i < M; ++i){
        int x, y, z;
        cin >> x >> y >> z;
        trees[x][y].push_back(z);
    }
}

void Spring() {
    // 어린나무 순으로 정렬
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            sort(trees[i][j].begin(), trees[i][j].end());
        }
    }

    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            int cnt = trees[i][j].size();
            int rest = -1;
            for(int k = 0; k < cnt; ++k){
                // 트리의 나이만큼 양분을 먹고 나이 1살 추가
                if(trees[i][j][k] <= memo[i][j]) {
                    memo[i][j] -= trees[i][j][k];
                    trees[i][j][k] += 1;
                }else {
                    // 더이상 못먹으면 그뒤로 죽은나무
                    rest = k;
                    break;
                }
            }
            if(rest == -1) continue;
            // 죽은나무 배열에 삽입
            for(int k = cnt - 1; rest <= k; --k) {
                dead[i][j].push_back(trees[i][j][k]);
                trees[i][j].pop_back();
            }
        }
    }
}

void Summer() {
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            // 해당 칸에 죽은 나무들 양분으로 추가
            while(!dead[i][j].empty()){
                int k = dead[i][j].back();
                dead[i][j].pop_back();
                memo[i][j] += (k / 2);
            }
        }
    }
}

void Autumn() {
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            int cnt = trees[i][j].size();
            for(int k = 0; k < cnt; ++k){
                if(0 < trees[i][j][k] && trees[i][j][k] % 5 == 0) {
                    // 번식
                    for(int d = 0; d < 8; ++d){
                        int ny = i + dy[d];
                        int nx = j + dx[d];

                        if(ny < 1 || N < ny || nx < 1 || N < nx) continue;
                        trees[ny][nx].push_back(1);
                    }
                }
            }
        }
    }
}

void Winter() {
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            memo[i][j] += board[i][j];
        }
    }
}

void Solve() {
    for(int i = 0; i < K; ++i){
        Spring();
        Summer();
        Autumn();
        Winter();
    }
    int answer = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j){
            answer += trees[i][j].size();
        }
    }
    cout << answer << '\n';
}

int main() {   
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    return 0;
}