#include <iostream>
#include <vector>
#include <queue>

using std::pair;
using std::vector;
using std::queue;
using std::ios;
using std::cout;
using std::cin;

// https://www.acmicpc.net/problem/13460
// 스타트링크에서 판매하는 어린이용 장난감 중에서 가장 인기가 많은 제품은 구슬 탈출이다. 
// 구슬 탈출은 직사각형 보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음, 빨간 구슬을 구멍을 통해 빼내는 게임이다.

// 보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다. 
// 가장 바깥 행과 열은 모두 막혀져 있고, 보드에는 구멍이 하나 있다. 빨간 구슬과 파란 구슬의 크기는 보드에서 1×1크기의 칸을 가득 채우는 사이즈이고, 각각 하나씩 들어가 있다.
//  게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다. 이때, 파란 구슬이 구멍에 들어가면 안 된다.

// 이때, 구슬을 손으로 건드릴 수는 없고, 중력을 이용해서 이리 저리 굴려야 한다. 
// 왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.

// 각각의 동작에서 공은 동시에 움직인다. 빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다. 
// 빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다. 빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다. 또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다.
//  기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.

// 보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.

struct Position {
    int y;
    int x;
    Position(){};
    Position(int _y, int _x): y(_y), x(_x){};
};

int N, M;
vector<vector<char>> board;
Position red;
Position blue;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int count;

void Input() {
    std::cin >> N >> M;
    board.assign(N,vector<char>(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            std::cin >> board[i][j];
            if(board[i][j] == 'R') {red.y = i; red.x = j;}
            if(board[i][j] == 'B') {blue.y = i; blue.x = j;}
        }
    }
}
// 구슬을 이동시키는 함수
// 이동 후 빨간구슬과 파란구슬이 겹치는지 확인 필요
// 이동 후 구슬이 들어가는지 확인 필요
pair<Position, Position> Move(const Position& r, const Position& b, int direction) {
    int rY = r.y;
    int rX = r.x;
    int bY = b.y;
    int bX = b.x;
    bool crossR = false;
    bool crossB = false;

    while(board[rY+dy[direction]][rX+dx[direction]] != '#') {
        rY += dy[direction];
        rX += dx[direction];
        if(rY == bY && rX == bX) crossB = true;
        if(board[rY][rX] == 'O') break;
    }
    while(board[bY+dy[direction]][bX+dx[direction]] != '#') {
        bY += dy[direction];
        bX += dx[direction];
        if(rY == bY && rX == bX && !crossB) crossR = true;
        if(board[bY][bX] == 'O') break;
    }

    if((rY == bY && rX == bX && board[rY][rX] != 'O')){
        if(crossB) {
            rY -= dy[direction];
            rX -= dx[direction];
        }
        if(crossR) {
            bY -= dy[direction];
            bX -= dx[direction];
        }
    }
    return {Position(rY, rX), Position(bY, bX)};
}

bool Bfs(const Position& r, const Position& b) {
    queue<pair<pair<Position, Position>, int>> que;
    que.push({{r,b}, 0});

    while(!que.empty()){
        Position curRed = que.front().first.first;
        Position curBlue = que.front().first.second;
        int cnt = que.front().second;
        que.pop();

        // 문제조건: 10번 이하로 움직여서 구슬을 못빼면 -1
        if(10 < cnt) {
            count = -1;
            break;
        }
        // 파란구슬이 빠진경우 이후 경로 진행x
        if(board[curBlue.y][curBlue.x] == 'O') {
            continue;
        };
        // 최소경로 발견
        if(board[curRed.y][curRed.x] == 'O') {
            count = cnt;
            return true;
        }

        for(int i = 0; i < 4; ++i){
            pair<Position, Position> nextPos = Move(curRed, curBlue, i);
            if(nextPos.first.y != curRed.y || nextPos.first.x != curRed.x 
            || nextPos.second.y != curBlue.y || nextPos.second.x != curBlue.x) {
                que.push({nextPos, cnt + 1});
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Input();
    bool success = Bfs(red, blue);

    if(success) {
        cout << count << '\n';
    }else {
        cout << -1 << '\n';
    }
    
    return 0;
}

/* Input 
7 7
#######
#...RB#
#.#####
#.....#
#####.#
#O....#
#######
*/

/* Output
5
*/