#include <iostream>
#include <vector>
#include <string>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::string;

// https://www.acmicpc.net/problem/4354

// 문자열 s가 주어졌을 때, 어떤 문자열 a에 대해서 s=a^n을 만족하는 가장 큰 n을 찾는 프로그램을 작성하시오.

// 문자열을 앞에서부터 하나씩 붙여가며 kmp 알고리즘으로 탐색하는 문제
// "abcabc"에서 항상 문자열을 발견하는 위치가 찾는 문자열의 길이 다음에 발견되어야함 (ex. "ab" -> [0, 2, 4, 6, 8])

// 시간초과로 인해 전처리 필요: 원본 문자열에서 찾는 문자열로 나누어 떨어지지 않을때


void createPI (vector<int>& pi, string& str);
bool kmp(string& str, string& pattern);

vector<string> strings;

void Input() {
    string a;
    while(true){
        // cin >> a;
        // if(a == ".") break;        
        strings.push_back("abcd");
        strings.push_back("aaaa");
        strings.push_back("ababab");
    }
}
void Solve() {
    vector<int> answer;
    for(auto& s : strings){
        string tmp = "";
        bool flag = false;
        for(int i = 0; i < s.length(); ++i){
            tmp += s[i];

            if(s.length() % tmp.length() != 0) continue;

            if(kmp(s, tmp)){
                answer.push_back(s.length() / tmp.length());
                flag = true;
                break;
            }
            if(flag){
                break;
            }
        }
    }
    for(auto& a : answer){
        cout << a << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Input();
    Solve();

    // 결과
    // 1
    // 4
    // 3
    
    return 0;
}

void createPI (vector<int>& pi, string& str){
    int prefix = 0;

    for(int i = 1; i < str.length(); ++i){
        while(prefix && str[i] != str[prefix]){
            prefix = pi[prefix - 1];
        }
        if(str[i] == str[prefix]){
            ++prefix;
        }
        pi[i] = prefix;
    }
}

bool kmp(string& str, string& pattern){
    int curIdx = 0;
    vector<int> pi;
    pi.assign(pattern.length(), 0);
    createPI(pi, pattern);

    int flag = 0;
    for(int i = 0; i < str.length(); ++i){
        while(curIdx && str[i] != pattern[curIdx]){
            curIdx = pi[curIdx - 1];
        }
        if(str[i] == pattern[curIdx]){
            ++curIdx;
        }

        // 찾음
        if(curIdx == pattern.length()){
            int findIdx = i - (pattern.length() - 1);
            if(findIdx != flag) return false; // 실패
            flag += pattern.length();
            curIdx = pi[curIdx-1];
        }
    }

    // 다돌면 성공
    return flag == str.length();
}