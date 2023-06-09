#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::ios;
using std::vector;

// https://www.acmicpc.net/problem/1717
// 집합의 표현

// Disjoint Set 문제

class UnionFind {
    private:
        vector<int> root;
    public:
        UnionFind(int size) {
            root.reserve(size + 1);
            for(int i = 0; i <= size; ++i){
                root[i] = i;
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

        void Merge(int x, int y) {
            int rootX = Find(x);
            int rootY = Find(y);

            if(rootY == rootX) {
                return;
            }
            root[rootY] = rootX;
        }
};

int N, M;

void Input() {
    cin >> N >> M;
}

void Solve() {
    UnionFind uf(N);

    for(int i = 0; i < M; ++i){
        int command;
        int x, y;
        cin >> command >> x >> y;

        if(command == 0) {
            uf.Merge(x, y);
        }else {
            bool result = uf.Connected(x, y);

            if(result) {
                cout << "YES" << "\n";
            }else {
                cout << "NO" << "\n";
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    Solve();

    return 0;
}