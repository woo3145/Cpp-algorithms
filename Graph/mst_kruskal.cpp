
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

struct Edge {
    int from, to, weight;
};

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
            if(x == root[x]) return x;
            return root[x] = find(root[x]);
        }

        void merge(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if(rootX == rootY) return;

            root[rootY] = rootX;
        }

        bool connected(int x, int y) {
            return find(x) == find(y);
        }
};

vector<Edge> edges;
int V, E; // 정점 수 / 간선 수

void Input () {
    std::cin >> V >> E;
    edges.resize(E);
    for(int i = 0; i < E; ++i){
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
}

bool Cmp (const Edge& a, const Edge& b) {
    return a.weight < b.weight; // 오름차순 정렬
}

// 크루스칼: 간선들을 오름차순으로 정렬하여 비용이 적은것부터 사이클을 확인하며 MST 구하기
// 시간복잡도: 정렬에 O(ElogE)
int Kruskal () {
    UnionFind uf(E);
    sort(edges.begin(), edges.end(), Cmp);
    int mstWeight = 0;

    for(const auto& e : edges){
        if(!uf.connected(e.from, e.to)){
            uf.merge(e.from, e.to);
            mstWeight += e.weight;
        }
    }
    return mstWeight;
}

int main () {
    Input();
    int mstWeight = Kruskal();

    std::cout << mstWeight << '\n';
    
    return 0;
}

/* input 
7 12
1 2 3
1 3 2
3 2 1
2 5 2
3 4 4
7 3 6
5 1 5
1 6 2
6 4 1
6 5 3
4 5 3
6 7 4
*/
/* output
12
*/