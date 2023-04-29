#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>

using std::ios;
using std::cout;
using std::cin;
using std::string;
using std::memset;

// https://www.acmicpc.net/problem/2602
// 돌다리 건너기 문제

// 3차원 cache로 다리타입/다리위치/탐색한글자 를 기록하는 문제
// ex) 0/4/3 이면 천사다리의 4번째 값으로부터 다리 끝까지 "문자열의 3번째 값부터 문자열의 끝까지 탐색할 수 있는 경우의 수"가 기록됨
// 0 ~ bridgeSize 까지 첫글자가 일치하는지 확인 후 일치하는 값들만 반대쪽 다리의 다음값 탐색
// => 들어온 다리의 위치 ~ bridgeSize 까지 다음값이 일치하는지 확인하여 일치하면 반대쪽 다음값 탐색
// => 반복하다가 문자열 끝까지 탐색이 완료된 경우 1반환
// => 되돌아 가면서 ret값에 누적

string S;
string B[2];
int cache[2][101][21];

void Input() {
    cin >> S >> B[0] >> B[1];
    memset(cache, -1, sizeof(cache));
}

int Recursive(int type, int bridgeIdx, int strIdx) {
    // 문자열의 마지막까지 탐색됨
    if(strIdx == S.size()) return 1;

    int &ret = cache[type][bridgeIdx][strIdx];
    if(ret != -1) return ret;

    ret = 0;

    // 현재 들어온 bridgeIdx부터 다리끝까지 S[strIdx] 값과 일치하는지 확인하여 반대쪽 다리 다음칸부터 문자열 다음값 재탐색
    int size = B[0].size();
    for(int i = bridgeIdx; i < size; ++i){
        if(S[strIdx] == B[type][i]) {
            ret += Recursive(!type, i+1, strIdx+1);
        }
    }

    return ret;
}

void Solve() {
    cout << Recursive(0, 0, 0) + Recursive(1, 0, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Input();
    Solve();
    
    return 0;
}
