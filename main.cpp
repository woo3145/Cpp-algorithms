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


void Solve() {
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Input();
    Solve();
    
    return 0;
}
