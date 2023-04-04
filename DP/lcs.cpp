#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::reverse;

int N;

// LCS(Longest Common Subsequence/Substring)
// Subsequence와 Substring 차이 ex) "ABCDE", "ABEF"
// Subsequence = ABE, Substring = AB

// 2차원 dp배열에서 행은 str1, 열은 str2이기 때문에 dp[i-1][j-1]은 두개의 문자열에에서 동시에 이전문자를 나타냄
// 따라서 현재 매치중인 문자가 같으면 dp[i-1][j-1]에 기록된 값에서 +1을 하면 공통 수열또는 문자열을 구할 수 있음
// ++ 공통 문자열을 구할땐 아래에서 문자열이 일치하지 않을경우 dp배열에 0을 넣어주면 됨
string LCS(const string str1, const string& str2) {
    const int M = str1.length();
    const int N = str2.length();
    int dp[M + 1][N + 1];

    for(int i = 0; i <= M; ++i){
        for(int j = 0; j <= N; ++j){
            if(i == 0 || j == 0) {
                dp[i][j] = 0;
            }else if (str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    string lcs;

    int i = M;
    int j = N;

    while(0 < i && 0 < j){
        if(str1[i-1] == str2[j-1]){
            lcs += str1[i-1];
            --i;
            --j;
        }else if (dp[i-1][j] > dp[i][j-1]){
            --i;
        }else {
            --j;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}


int main() {
    string s1 = "ABCDE";
    string s2 = "ABEF";

    std::cout << LCS(s1, s2) << '\n';
    return 0;
}


/* output
ABE
*/