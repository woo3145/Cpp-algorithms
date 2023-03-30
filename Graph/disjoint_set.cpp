#include <vector>
#include <iostream>

using std::vector;
using std::cout;

class UnionFind {
    private:
        vector<int> root;
    public:
        UnionFind(int size): root(size){
            for(int i = 0; i < size; ++i){
                root[i] = i;
            }
        }
        ~UnionFind(){}

        int find(int x) {
            if(x == root[x]){
                return x;
            }
            return root[x] = find(root[x]); // 부모를 탐색하면서 거리압축 최적화
        }

        bool connected(int x, int y) {
            return find(x) == find(y);
        }

        void merge(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if(rootX == rootY) return;

            root[rootY] = rootX; // X트리에 Y트리 병합
        }
};

int main() {
    UnionFind unionFind(10);
    // 1-2-3-4-5   6-7   8-9
    unionFind.merge(1, 2);
    unionFind.merge(2, 3);
    unionFind.merge(3, 4);
    unionFind.merge(4, 5);
    unionFind.merge(6, 7);
    unionFind.merge(8, 9);
    cout << unionFind.connected(1, 4) << '\n';  // true
    cout << unionFind.connected(5, 7) << '\n';  // false
    cout << unionFind.connected(8, 9) << '\n';  // true
    // 1-2-3-4-5-6-7  8-9
    unionFind.merge(7, 2);
    cout << unionFind.connected(5, 7) << '\n';  // true

    return 0;
}