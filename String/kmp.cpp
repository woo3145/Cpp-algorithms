#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

// (longest prefix suffix) array
// lps[i]: 0 ~ i까지의 문자열에서 접미사면서 가장긴 접두사의 길이를 저장
// "abcabc" -> abc , "a"bc"a" , "ab"c"ab" , "abc""abc"
//  000123      0        1          2           3
void CreateLPS(vector<int>& ret, const string& pattern) {
    int patternLen = pattern.length();
    ret.assign(patternLen, 0);

    int prefix = 0; // 접두사 길이

    // 문자열 순회(접두사를 제외한 index 1부터)
    for(int i = 1; i < patternLen; ++i) {
        // 현재 prefix 마지막 문자열이 일치하지 않을 경우 prefix = lps[prefix-1] (prefix가 0이거나 문자열이 같을때까지)
        while(prefix > 0 && pattern[prefix] != pattern[i]) {
            prefix = ret[prefix - 1];
        }
        // 일치하면 prefix 길이 증가
        if(pattern[prefix] == pattern[i]){
            prefix += 1;
        }
        // lps 배열 갱신
        ret[i] = prefix;
    }
}

// KMP: 문자열의 비교는 O(n)으로 작동함
// 패턴 문자열의 lps배열(접미사이면서 가장긴 접두사 배열) 정보를 이용하여 완전탐색(nm)을 할 필요 없이 선형시간(n) 비교가 가능하게 된다.
void KMP(const string& str, const string& pattern) {
    int strLen = str.length();
    int patternLen = pattern.length();
    vector<int> lps;
    CreateLPS(lps, pattern);

    int j = 0; // 탐색중인 pattern의 인덱스

    for(int i = 0; i < strLen; ++i) {
        // 일치: ++j
        // 불일치: j-1 까지는 일치한 것임으로 lis배열에 저장된 접두사의 길이부터 재탐색 하면됨
        while(j > 0 && str[i] != pattern[j]) {
            j = lps[j - 1];
        }
        if(str[i] == pattern[j]) {
            ++j;
        }
        // 패턴이 끝까지 검사 된 경우
        // 현재 j는 마지막 인덱스 + 1을 가르키고 있음
        if(j == patternLen) {
            std::cout << "패턴 발견: index " << i - (patternLen - 1) << '\n';
            j = lps[j - 1];
        }
    }
}

int main() {
    string text = "ababacabacaabacaaba";
    string pattern = "abacaaba";
    KMP(text, pattern);

    // 패턴 발견: index 6
    // 패턴 발견: index 11

    return 0;
}