#include "vector"
#include "string"
#include "iostream"

using std::vector;
using std::string;
using std::cout;
using std::cin;

vector<string> split(string input, const string& delimiter) {
    vector<string> ret;

    if(delimiter.empty()){
        for(char c : input){
            ret.push_back(string(1, c));
        }
        return ret;
    }

    long long pos = 0;
    string token;
    while((pos = input.find(delimiter)) != string::npos){
        token = input.substr(0, pos);
        ret.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    ret.push_back(input);

    return ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    cout.tie(nullptr);
    cin.tie(nullptr);

    string str = "abcdefg";

    vector<string> result = split(str, "");

    for(const string& c : result){
        cout << c << ' ';
    }
    cout << "\n";
    result = split(str, "d");
    for(const string& c : result){
        cout << c << ' ';
    }

    return 0;
}