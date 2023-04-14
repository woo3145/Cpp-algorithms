#include <iostream>
#include <vector>
#include <algorithm>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::sort;

// https://www.acmicpc.net/problem/1253

// 좋다 (투포인터 탐색)
// 한 배열에서 배열안의 다른 두수의 합으로 나타낼 수 있는 수의 개수를 세는 문제

int N;
vector<int> arr;

void Input() {
    cin >> N;
    arr.resize(N);
    for(int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
}

void Solve() {
    int result = 0;
    sort(arr.begin(), arr.end());

    for(int i = 0; i < N; ++i){
        int target = arr[i];

        int left = 0;
        int right = N - 1; // 음수가 있을 수 있기 때문에 범위를 전체로 잡아야함

        while(left < right) {
            int sum = arr[left] + arr[right];

            if(sum == target) {
                if(left == i) {
                    ++left;
                }else if (right == i) {
                    --right;
                }else {
                    ++result;
                    break;
                }
            }else if (sum < target) {
                ++left;
            }else {
                --right;
            }
        }
    }

    cout << result << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    return 0;
}


/* Input
10
1 2 3 4 5 6 7 8 9 10
*/
/* Output
8
*/

