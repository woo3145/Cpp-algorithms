#include <iostream>

using std::ios;
using std::cin;
using std::cout;

#define MAX_N 99999999

int N, M, T;
int board[51][51];

// https://www.acmicpc.net/problem/17822
// 원판 돌리기 문제

// 차근차근 구현하는 문제
// 하나의 수에서 같은 인접수를 구할 때 
// 해당 인접수의 인접수도 같을 수 있기 때문에 임시 테이블에 저장하여 마지막에 변경 해야함

void Input() {
    cin >> N >> M >> T;
    
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> board[i][j];
        }
    }
}
// 원판 회전
void Rotate(int x, int d) {
    int curX = 0;
    while(curX + x <= N) {
        curX += x;

        // 시계
        if(d == 0) {
            int prev = board[curX][M-1];

            for(int i = 0; i < M; ++i){
                int temp = board[curX][i];
                board[curX][i] = prev;
                prev = temp;
            }
        }else {
        // 반시계
            int prev = board[curX][0];
            
            for(int i = M-1; 0 <= i; --i){
                int temp = board[curX][i];
                board[curX][i] = prev;
                prev = temp;
            }
        }
    }
}

// 인접수가 같은 수 제거 
bool Remove() {
    bool temp[51][51];
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            temp[i][j] = false;
        }
    }

    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            bool isChanged = temp[i][j];
            if(isChanged) continue;

            int num = board[i][j];

            int left = j - 1;
            int right = j + 1;
            int outside = i + 1;
            int inside = i - 1;
            if(left < 0) {
                left = M - 1;
            }
            if(M <= right) {
                right = 0;
            }
            if(board[i][left] == num) {
                temp[i][left] = true;
                temp[i][j] = true;
            }
            if(board[i][right] == num) {
                temp[i][right] = true;
                temp[i][j] = true;
            }
            if(outside <= N && board[outside][j] == num) {
                temp[outside][j] = true;
                temp[i][j] = true;
            }
            if(0 < inside && board[inside][j] == num){
                temp[inside][j] = true;
                temp[i][j] = true;
            }
        }
    }

    // 원판의 변화가 있는지 확인
    bool isRemoved = false;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            if(temp[i][j] && board[i][j] != MAX_N) {
                board[i][j] = MAX_N;
                isRemoved = true;
            };
        }
    }

    return isRemoved;
}

// 평균을 구하고 원판 재구축
void ReBuild() {
    int sum = 0;
    int cnt = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            if(board[i][j] == MAX_N) continue;
            ++cnt;
            sum += board[i][j];
        }
    }
    if(cnt == 0) return;

    int avg = sum / cnt;
    int rest = sum % cnt;

    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            if(board[i][j] == MAX_N) continue;
            if(board[i][j] == avg && rest == 0) continue;

            if(board[i][j] <= avg) {
                board[i][j] += 1;
                sum += 1;
            }else if(avg < board[i][j]) {
                board[i][j] -= 1;
                sum -= 1;
            }
        }
    }
}
// 원판의 모든 수 합
int Calc() {
    int sum = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            if(board[i][j] == MAX_N) continue;
            sum += board[i][j];
        }
    }

    return sum;
}

void Solve() {
    for(int t = 0; t < T; ++t) {
        int x, d, k;
        cin >> x >> d >> k;

        for(int i = 0; i < k; ++i){
            Rotate(x,d);
        }

        // 원판의 변화가 없으면 재구축
        bool isChanged = Remove();
        if(!isChanged) {
            ReBuild();
        };
    }

    cout << Calc() << '\n';
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();
    return 0;
}