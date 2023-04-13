#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::ios;
using std::cout;
using std::cin;
using std::vector;
using std::pair;
using std::priority_queue;
using std::sort;

// https://www.acmicpc.net/problem/17472
// 다리 만들기 2 (구현 + 그래프탐색 + MST)

// 1. Dfs로 섬을 마킹
// 2. 모든 땅을 돌면서 섬과 다른섬을 직선으로 이을때 이어지면 간선 생성
// 3. 생성된 간선으로 크루스칼 알고리즘을 통해 최소비용 구하기

// 조건
// - 다리길이 최소 2이상

struct Edge {
    int from;
    int to;
    int dist;
};

int N, M;
int map[10][10];
bool visited[10][10];

vector<Edge> edges;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

const int MAX = 999999999;

void Input() {
    cin >> N >> M;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j){
            cin >> map[i][j];
        }
    }
}

void Dfs(int y, int x, int num) {
    visited[y][x] = true;
    map[y][x] = num;
    for(int i = 0; i < 4; ++i){
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(ny < 0 || N <= ny || nx < 0 || M <= nx) continue;
        if(visited[ny][nx]) continue;
        if(map[ny][nx] == 0) continue;
        Dfs(ny, nx, num);
    }
}
// dfs로 섬 구분
int MarkIsland() {
    int islandNum = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(visited[i][j] || map[i][j] == 0) continue;
            ++islandNum;
            Dfs(i, j, islandNum);
        }
    }
    return islandNum;
}

// 현재섬과 연결할 수 있는 섬을 찾으면 간선으로 추가 
void FindRoot(int y, int x, int startIsland) {
    for(int i = 0; i < 4; ++i){
        int ny = y + dy[i];
        int nx = x + dx[i];
        int dist = 0;
        bool isFind = false;
        while(true) {
            if(ny < 0 || N <= ny || nx < 0 || M <= nx) break; // 맵밖이면
            if(map[ny][nx] != 0) {
                // 새 육지를 발견 한 경우
                if(startIsland != map[ny][nx]) isFind = true;
                break;
            };
            ny += dy[i];
            nx += dx[i];
            dist += 1;
        }
        if(isFind && 2 <= dist) {
            Edge newEdge;
            newEdge.from = startIsland;
            newEdge.to = map[ny][nx];
            newEdge.dist = dist;
            edges.push_back(newEdge);
        }
    }
} 

bool Cmp (const Edge& a, const Edge& b){
    return a.dist < b.dist;
}

class UnionFind {
    private:
        vector<int> root;
    public:
        UnionFind(int size): root(size + 1) {
            for(int i = 1; i <= size; ++i){
                root[i] = i;
            }
        }
        ~UnionFind(){}

        int find(int x) {
            if(root[x] == x) return x;
            return root[x] = find(root[x]);
        }

        void merge(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if(rootX == rootY) return;
            root[rootY] = rootX;
        }

        bool isConnected(int x, int y){
            return find(x) == find(y);
        }
};

void Kruskal(int islandNum) {
    UnionFind uf(islandNum);
    sort(edges.begin(), edges.end(), Cmp);

    int answer = 0;
    int edgeCount = 0;
    for(auto& edge : edges){
        if(!uf.isConnected(edge.from, edge.to)) {
            uf.merge(edge.from, edge.to);
            answer += edge.dist;
            ++edgeCount;
        }
    }
    
    // 모든 노드가 이어지면 항상 (간선의 개수 = 노드의 개수 - 1)
    if(islandNum - 1 == edgeCount) {
        cout << answer << '\n';
    }else {
        cout << -1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();
    // 섬 마킹
    int islandNum = MarkIsland();

    // 육지를 돌며 간선 생성
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j){
            if(map[i][j] == 0) continue;
            FindRoot(i, j, map[i][j]);
        }
    }

    // 생성된 간선으로 크루스칼 알고리즘
    Kruskal(islandNum);

    return 0;
}


/* Input
7 8
0 0 0 0 0 0 1 1
1 1 0 0 0 0 1 1
1 1 0 0 0 0 0 0
1 1 0 0 0 1 1 0
0 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1
*/
/* Output
9
*/

