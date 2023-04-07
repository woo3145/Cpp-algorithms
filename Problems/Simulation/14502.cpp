#include <iostream>
#include <vector>
#include <queue>

using std::pair;
using std::queue;
using std::vector;
using std::ios;
using std::cout;
using std::cin;

// https://www.acmicpc.net/problem/14502

int N, M;
vector<vector<int>> map;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int answer = 0;

void Input() {
    cin >> N >> M;
    map.assign(N, vector<int>(M, 0));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> map[i][j];
        }
    }
}


int Bfs(vector<vector<int>> m) {
    queue<pair<int,int>> que;

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(m[i][j] == 2) {
                que.push({i, j});
            }
        }
    }
    while(!que.empty()) {
        int y = que.front().first;
        int x = que.front().second;
        que.pop();

        for(int i = 0; i < 4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny < 0 || N <= ny || nx < 0 || M <= nx) continue;
            if(m[ny][nx] == 0) {
                m[ny][nx] = 2;
                que.push({ny, nx});
            }
        }
    }

    // Count SafeZone
    int safeZone = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(m[i][j] == 0) ++safeZone;
        }
    }

    return safeZone;
}

void backTracking(int y, int x, int depth) {
    if(depth == 3) {
        int cnt = Bfs(map);
        if(answer < cnt) answer = cnt;
        return;
    }
    for(int i = y; i < N; ++i){
        for(int j = i == y ? x : 0; j < M; ++j){
            if(map[i][j] == 0) {
                map[i][j] = 1;
                backTracking(i, j, depth + 1);
                map[i][j] = 0;
            }
        }
    }
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Input();
    backTracking(0, 0, 0);
    cout << answer << '\n';

    return 0;
}


/* Input 
7 7
2 0 0 0 1 1 0
0 0 1 0 1 2 0
0 1 1 0 1 0 0
0 1 0 0 0 0 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0
*/

/* Output
27
*/