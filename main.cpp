#include <iostream>
#include <vector>
#include <queue>

using std::pair;
using std::vector;
using std::queue;
using std::ios;

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

pair<Position, Position> Left( const Position& r, const Position& b) {
    int rX = r.x;
    int bX = b.x;

    bool crossR = false;
    bool crossB = false;

    while(0 < rX && board[r.y][rX-1] != '#') {
        --rX;
        if(r.y == b.y && rX == bX) crossB = true;
        if(board[r.y][rX] == 'O') break;
    }
    while(0 < bX && board[b.y][bX-1] != '#') {
        --bX;
        if(r.y == b.y && rX == bX && !crossB) crossR = true;
        if(board[b.y][bX] == 'O') break;
    }
    if((r.y == b.y && rX == bX && board[r.y][rX] != 'O')){
        if(crossB) rX += 1;
        if(crossR) bX += 1;
    }
    return {Position(r.y, rX), Position(b.y, bX)};
}
pair<Position, Position> Right(const Position& r, const Position& b) {
    int rX = r.x;
    int bX = b.x;

    bool crossR = false;
    bool crossB = false;

    while(rX < M && board[r.y][rX+1] != '#') {
        ++rX;
        if(r.y == b.y && rX == bX) crossB = true;
        if(board[r.y][rX] == 'O') break;
    }
    while(bX < M && board[b.y][bX+1] != '#') {
        ++bX;
        if(r.y == b.y && rX == bX && !crossB) crossR = true;
        if(board[b.y][bX] == 'O') break;
    }
    if((r.y == b.y && rX == bX && board[r.y][rX] != 'O')){
        if(crossB) rX -= 1;
        if(crossR) bX -= 1;
    }
    return {Position(r.y, rX), Position(b.y, bX)};
} 
pair<Position, Position> Up(const Position& r, const Position& b) {
    int rY = r.y;
    int bY = b.y;

    bool crossR = false;
    bool crossB = false;

    while(0 < rY && board[rY-1][r.x] != '#') {
        --rY;
        if(rY == bY && r.x == b.x) crossB = true;
        if(board[rY][r.x] == 'O') break;
    }
    while(0 < bY && board[bY-1][b.x] != '#') {
        --bY;
        if(rY == bY && r.x == b.x && !crossB) crossR = true;
        if(board[bY][b.x] == 'O') break;
    }
    if((rY == bY && r.x == b.x && board[rY][r.x] != 'O')){
        if(crossB) rY += 1;
        if(crossR) bY += 1;
    }
    return {Position(rY, r.x), Position(bY, b.x)};
}
pair<Position, Position> Down(const Position& r, const Position& b) {
    int rY = r.y;
    int bY = b.y;

    bool crossR = false;
    bool crossB = false;

    while(rY < N && board[rY+1][r.x] != '#') {
        ++rY;
        if(rY == bY && r.x == b.x) crossB = true;
        if(board[rY][r.x] == 'O') break;
    }
    while(bY < N && board[bY+1][b.x] != '#') {
        ++bY;
        if(rY == bY && r.x == b.x && !crossB) crossR = true;
        if(board[bY][b.x] == 'O') break;
    }
    if((rY == bY && r.x == b.x && board[rY][r.x] != 'O')){
        if(crossB) rY -= 1;
        if(crossR) bY -= 1;
    }
    return {Position(rY, r.x), Position(bY, b.x)};
}

bool Bfs(const Position& r, const Position& b) {
    queue<pair<pair<Position, Position>, int>> que;
    que.push({{r,b}, 0});

    while(!que.empty()){
        Position curRed = que.front().first.first;
        Position curBlue = que.front().first.second;
        int cnt = que.front().second;
        que.pop();

        if(10 < cnt) {
            count = -1;
            break;
        }
        if(board[curBlue.y][curBlue.x] == 'O') {
            continue;
        };
        if(board[curRed.y][curRed.x] == 'O') {
            count = cnt;
            return true;
        }

        if(0 < curBlue.y && board[curBlue.y-1][curBlue.x] != '#' || 0 < curRed.y && board[curRed.y-1][curRed.x] != '#'){
            que.push({Up(curRed, curBlue), cnt + 1});
        }
        if(curBlue.y < N && board[curBlue.y+1][curBlue.x] != '#' || curRed.y < N && board[curRed.y+1][curRed.x] != '#'){
            que.push({Down(curRed, curBlue), cnt + 1});
        }
        if(0 < curBlue.x && board[curBlue.y][curBlue.x-1] != '#' || 0 < curRed.x && board[curRed.y][curRed.x-1] != '#'){
            que.push({Left(curRed, curBlue), cnt + 1});
        }
        if(curBlue.x < M && board[curBlue.y][curBlue.x+1] != '#' || curRed.x < M && board[curRed.y][curRed.x+1] != '#'){
            que.push({Right(curRed, curBlue), cnt + 1});
        }
    }

    return false;
}

int main() {
    Input();
    bool success = Bfs(red, blue);

    if(success) {
        std::cout << count << '\n';
    }else {
        std::cout << -1 << '\n';
    }
    
    return 0;
}
