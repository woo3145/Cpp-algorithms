#include <string>
#include <iostream>
#include <cmath>

using std::string;
using std::pow;

const int prime = 3;

// 해시함수: 앞에서 부터 아스키 코드 * prime^n
int GetHash(const string& str){
    int hash = 0;
    int p = 1;
    for(int i = 0; i < str.length(); ++i){
        hash += str[i] * p;
        p *= prime;
    }
    return hash;
}

// 해시 충돌을 대비하여 실제 문자열도 비교해준다.
bool CheckEqual(const string& str1, const string& str2, int start){
    for(int i = 0; i < str2.length(); ++i){
        if(str1[start+i] != str2[i]){
            return false;
        }
    }
    return true;
}

// 라빈 카프: 해시를 이용하여 문자열을 비교하는 알고리즘
// "abc" => a * prime^0 + b * prime^1 + c* prime^2;
void RabinCarp(const string& text, const string& pattern) {
    if(text.length() < pattern.length()){
        return;
    }

    int textHash = GetHash(text.substr(0, pattern.length()));
    int patternHash = GetHash(pattern);

    int textLen = text.length();
    int patternLen = pattern.length();
    for(int i = 0; i <= textLen - patternLen; ++i){
        if(textHash == patternHash && CheckEqual(text, pattern, i)){
            std::cout << "패턴 발견: index " << i << '\n';
        }
        textHash -= text[i];
        textHash /= prime;
        textHash += text[patternLen + i] * pow(prime, patternLen - 1);
    }
}

int main() {
    string text = "ababacabacaabacaaba";
    string pattern = "abacaaba";
    RabinCarp(text, pattern);

    // 패턴 발견: index 6
    // 패턴 발견: index 11

    return 0;
}