#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>

using std::ios;
using std::cout;
using std::cin;
using std::string;
using std::memset;

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
