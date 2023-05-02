#include <iostream>
#include <vector>
#include <stack>


using std::cout;
using std::cin;
using std::ios;
using std::vector;
using std::stack;

// https://www.acmicpc.net/problem/17837
// 새로운 게임 2

// 구현문제

struct Pawn{
    int y;
    int x;
    int direction;
    Pawn(int _y, int _x, int _d):y(_y), x(_x), direction(_d){};
    ~Pawn(){};
};

int N, K;
int map[13][13];
vector<int> board[13][13];
vector<Pawn> pawns;

int dy[5] = {0, 0, 0, -1, 1};
int dx[5] = {0, 1, -1, 0, 0}; 


void Input() {
    cin >> N >> K;
    
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cin >> map[i][j];
        }
    }

    int y, x, d;
    for(int i = 0; i < K; ++i){
        cin >> y >> x >> d;
        pawns.push_back(Pawn(y, x, d));
        board[y][x].push_back(i);
    }
}

void Print() {
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cout << board[i][j].size() << ' ';
        }
        cout << '\n';
    }
}

int Play() {
    int turn = 0;

    while(turn <= 1000){
        ++turn;
        bool done = false;
        for(int i = 0; i < K; ++i){
            int d = pawns[i].direction;
            int y = pawns[i].y;
            int x = pawns[i].x;
            int ny = y + dy[d];
            int nx = x + dx[d];
            
            // 체스판을 나가거나 다음칸이 파란칸
            if(ny < 1 || N < ny || nx < 1 || N < nx || map[ny][nx] == 2) {
                // 방향 전환
                if(d == 1) d = 2;
                else if(d == 2) d = 1;
                else if(d == 3) d = 4;
                else if(d == 4) d = 3;
                pawns[i].direction = d;

                // 반대쪽이 파란칸인지 확인
                ny = y + dy[d];
                nx = x + dx[d];
                // 체스판을 나가거나 반대쪽도 파란칸이면 이동 x
                if(ny < 1 || N < ny || nx < 1 || N < nx || map[ny][nx] == 2) continue;
            }

            int idx = 0;
            // 현재 말의 인덱스 찾기
            while(board[y][x][idx] != i) {
                ++idx;
            }


            // 흰칸
            if(map[ny][nx] == 0) {
                stack<int> st;
                int cnt = board[y][x].size() - idx;

                // 옮길 말 스택에 담기
                while(cnt) {
                    --cnt;
                    int top = board[y][x].back();
                    board[y][x].pop_back();
                    st.push(top);
                }
                // 다음칸으로 이동
                while(!st.empty()){
                    int top = st.top();
                    st.pop();
                    board[ny][nx].push_back(top);
                    pawns[top].y = ny;
                    pawns[top].x = nx;
                }
            
            // 빨간칸
            }else if(map[ny][nx] == 1) {
                int size = board[y][x].size();
                // 다음칸으로 이동
                while(idx < size){
                    int top = board[y][x].back();
                    board[y][x].pop_back();
                    board[ny][nx].push_back(top);
                    pawns[top].y = ny;
                    pawns[top].x = nx;
                    --size;
                }
            }

            if(4 <= board[ny][nx].size()) {
                done = true;
                break;
            }
        }
        if(done) break;
    }

    if(1000 < turn) {
        return -1;
    }
    return turn;
}


void Solve() {
    cout << Play() << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    Input();
    Solve();

    return 0;
}