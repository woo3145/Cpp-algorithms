#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using std::ios;
using std::cin;
using std::cout;
using std::vector;
using std::map;
using std::string;

// https://www.acmicpc.net/problem/4195
// 친구 네트워크

// Disjoint Set과 Map을 이용하여
// merge가 발생할 때마다 집합에 소속 된 노드의 수를 출력하는 문제

#define MAX_N 200000

int root[MAX_N];
int count[MAX_N];

class UnionFind {
    public:
        UnionFind() {
            for(int i = 0; i < MAX_N; ++i){
                root[i] = i;
                count[i] = 1;
            }
        }
        ~UnionFind(){};

        int Find(int x) {
            if(x == root[x]) {
                return x;
            }
            return root[x] = Find(root[x]);
        }

        bool Connected(int x, int y) {
            return Find(x) == Find(y);
        }

        int Merge(int x, int y) {
            int rootX = Find(x);
            int rootY = Find(y);

            if(rootY == rootX) {
                return count[rootY];
            }
            root[rootY] = rootX;
            int sum = count[rootY] + count[rootX];
            count[rootX] = sum;
            count[rootY] = sum;

            return sum;
        }
};

int N;
int F;

void Input() {
    cin >> F;
    N = 1;
}

void Solve() {
    map<string, int> users;
    UnionFind uf;
    
    for(int i = 0; i < F; ++i){
        string a, b;
        cin >> a >> b;

        if(users[a] == 0) {
            users[a] = N;
            ++N;
        }
        if(users[b] == 0){
            users[b] = N;
            ++N;
        }

        cout << uf.Merge(users[a], users[b]) << '\n';
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int T;
    cin >> T;

    for(int i = 0; i < T; ++i){
        Input();
        Solve();
    }
    return 0;
}