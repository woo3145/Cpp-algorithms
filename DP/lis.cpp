#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using std::vector;
using std::lower_bound;
using std::stack;

int N;
vector<int> arr;
vector<int> lis;
vector<int> record;

void Input() {
    std::cin >> N;
    arr.resize(N);

    for(int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }
}

// LIS(longest increasing subsequence)
// lis 배열은 각 요소의 최적의 위치를 찾을 뿐인 배열이다
// ex) {2, 3, 1} 인 배열일 경우 lis배열은 [1, 3]이 되지만 실제 증가수열은 [2, 3]임
// 따라서 각요소가 lis배열에 기록 될 때의 값을 저장시켜두고 출력해야 증가수열을 얻을 수 있다.
void LIS() {
    lis.push_back(arr[0]);
    record.push_back(1);
    for(int i = 1; i < N; ++i) {
        if(lis[lis.size() - 1] < arr[i]) {
            lis.push_back(arr[i]);
            record.push_back(lis.size());
        }else {
            int lowerIdx = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
            lis[lowerIdx] = arr[i];
            record.push_back(lowerIdx + 1);
        }
    }
}

void Print() {
    stack<int> st; // 뒤부터 확인해야함(앞부터 하면 [10,40,30,35]일 경우 10 40 35가 출력됨)
    int size = lis.size();
    std::cout << "Size: " << size << '\n';
    std::cout << "LIS: ";
    for(int i = arr.size() - 1; 0 <= i; --i) {
        if(record[i] == size) {
            --size;
            st.push(arr[i]);
        }
    }
    while(!st.empty()){
        std::cout << st.top() << ' ';
        st.pop();
    }
}

int main() {
    Input();
    LIS();
    Print();
    return 0;
}


/* input 
7
10 20 10 30 20 60 50
*/
/* output
Size: 4
LIS: 10 20 30 50
*/