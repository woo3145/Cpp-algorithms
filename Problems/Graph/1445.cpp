#include <iostream>
#include <queue>
#include <cstring>

using std::pair;
using std::priority_queue;
using std::ios;
using std::cout;
using std::cin;
using std::memset;


// https://www.acmicpc.net/problem/1445
// 쓰레기가 있는칸 < 쓰레기와 인접한 빈칸 < 빈칸
// 위의 우선순위로 경로를 탐색하여 쓰레기칸을 최대한 적게 통과하여 도착지점에 도달했을때
// 지나가는 쓰레기의 최소 개수와 쓰레기와 인접칸을 지나온 개수를 세는 문제

// 쓰레기 칸 + 인접칸 으로 우선순위 큐를 만들어 다익스트라 탐색을 진행함

class Pos {
    public:
        int y;
        int x;
        int cnt; // 지나가는 쓰레기 수
        int adjCnt; // 쓰레기 옆을 지나는 수
        Pos(){};
        Pos(int _y, int _x, int _cnt, int _adjCnt):y(_y), x(_x), cnt(_cnt), adjCnt(_adjCnt){};
        ~Pos(){};
        bool operator< (const Pos& otherPos) const {
            if(this->cnt == otherPos.cnt) return this->adjCnt > otherPos.adjCnt;
            return this->cnt > otherPos.cnt;
        }
};

int N, M;

char board[50][50];
bool visited[50][50]; // 최소 거리를 답하는 문제는 아님으로 방문여부만 확인

Pos pos; // 시작 위치
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

Pos answer;

void Input() {
    cin >> N >> M;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j){
            visited[i][j] = false;
            cin >> board[i][j];
            if(board[i][j] == 'S') {
                pos = Pos(i, j, 0, 0);
                visited[i][j] = true;
            }
        }
    }
}

// 인접칸에 쓰레기가 존재하는지 확인
bool CheckAdj(int y, int x) {
    bool existG = false;
    for(int i = 0; i < 4; ++i){
        int ny = y + dy[i];
        int nx = x + dx[i];

        if(ny < 0 || N <= ny || nx < 0 || M <= nx) continue;
        if(board[ny][nx] == 'g') existG = true;
    }
    return existG;
}

void Dijkstra() {
    priority_queue<Pos> pq;
    pq.push({pos});

    while(!pq.empty()){
        Pos curPos = pq.top();
        pq.pop();

        bool end = false;
        for(int i = 0; i < 4; ++i){
            int ny = curPos.y + dy[i];
            int nx = curPos.x + dx[i];

            if(ny < 0 || N <= ny || nx < 0 || M <= nx) continue;
            if(visited[ny][nx]) continue;

            // 문제조건: F는 세지 않음으로 발견시 바로 정답처리
            if(board[ny][nx] == 'F') {
                answer = curPos;
                end = true;
                break;
            }
            
            Pos nPos(ny, nx, curPos.cnt, curPos.adjCnt);
            // 쓰레기 칸을 지나는 경우
            if(board[ny][nx] == 'g') {
                nPos.cnt += 1;
            // 인접칸에 쓰레기가 있는 경우
            }else if (CheckAdj(ny, nx)) {
                nPos.adjCnt += 1;
            }
            pq.push(nPos);
            visited[ny][nx] = true;
        }
        if(end) break;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Input();
    Dijkstra();
    cout << answer.cnt << ' ' << answer.adjCnt << '\n';

    return 0;
}

/* Input
6 6
......
g..F..
......
..gg..
......
...S.g
*/

/* Output
0 2
*/