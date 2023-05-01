#include <iostream>
#include <vector>
#include <stack>

using std::ios;
using std::cin;
using std::cout;
using std::vector;
using std::stack;
using std::pair;

// https://www.acmicpc.net/problem/17143
// 낚시왕

// 간단한 구현문제

// 상어가 이동할때 제자리로 돌아오는 규칙을 찾아 최적화를 해야함

struct Shark {
    int direction;
    int speed;
    int size;

    Shark(int _s, int _d, int _size):direction(_d), speed(_s), size(_size) {};
    Shark(){};
    ~Shark(){};
};

int R, C, M;
vector<Shark> ocean[101][101];

int king = 0;
int sizeSum = 0;

int dy[5] = {0, -1, 1, 0, 0};
int dx[5] = {0, 0, 0, 1, -1}; // 1: 위, 2: 아래, 3: 오른쪽, 4: 왼쪽

void Input() {
    cin >> R >> C >> M;

    for(int i = 0; i < M; ++i){
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;

        // 제자리로 돌아오는 값을 미리 계산해줌
        if(d == 1 || d == 2) {
            s = s % (R * 2 - 2);
        }else {
            s = s % (C * 2 - 2);
        }
        Shark shark(s, d, z);
        
        ocean[r][c].push_back(shark);
    }
    
}

// 낚시왕이 오른쪽으로 한칸 이동한다.
bool MoveKing() {
    ++king;
    if(C < king){
        return false;
    }
    return true;
}

// 낚시왕의 위치 아래에 있는 가장 가까운 상어를 잡는다.
void Fishing() {
    int deep = 1;
    while(deep <= R) {
        if(!ocean[deep][king].empty()) {
            Shark shark = ocean[deep][king].back();
            ocean[deep][king].pop_back();
            sizeSum += shark.size;
            break;
        }
        ++deep;
    }
}

// 상어가 이동한다.
void MoveShark() {
    stack<pair<pair<int, int>, Shark>> st;

    // 스택에 상어를 모두 담는다.
    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j){
            while(!ocean[i][j].empty()){
                Shark shark = ocean[i][j].back();
                ocean[i][j].pop_back();
                st.push({{i, j}, shark});
            }
        }
    }

    while(!st.empty()) {
        pair<int, int> pos = st.top().first;
        Shark shark = st.top().second;
        st.pop();

        // 상어 이동
        int cnt = shark.speed;
        int ny = pos.first;
        int nx = pos.second;

        while(0 < cnt) {
            ny += dy[shark.direction];
            nx += dx[shark.direction];

            if(ny < 1) {
                ny = 2;
                shark.direction = 2;
            }else if(R < ny){
                ny = R - 1;
                shark.direction = 1;
            }else if(nx < 1) {
                nx = 2;
                shark.direction = 3;
            }else if(C < nx) {
                nx = C - 1;
                shark.direction = 4;
            }
            --cnt;
        }
        // 이동완료된 상어 ocean에 집어넣기
        ocean[ny][nx].push_back(shark);
    }
}

void EatShark() {
    for(int i = 1; i <= R; ++i){
        for(int j = 1; j <= C; ++j){
            Shark bigShark(0, 0, 0);
            while(!ocean[i][j].empty()){
                Shark shark = ocean[i][j].back();
                ocean[i][j].pop_back();
                if(bigShark.size < shark.size) {
                    bigShark = shark;
                }
            }
            if(0 < bigShark.size) ocean[i][j].push_back(bigShark);
        }
    }
}

void Solve() {
    while(MoveKing()) {
        Fishing();
        MoveShark();
        EatShark();
    }
    
    cout << sizeSum << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    return 0;
}