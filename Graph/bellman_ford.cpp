#include <iostream>
#include <vector>

using std::vector;
using std::pair;

#define INF 999999999

struct Edge {
    int from, to, weight;
};

vector<Edge> edges; // {정점, 비용}
vector<int> dist;

int V, E; // 정점 수 / 간선 수
int R; // 시작노드

void Input() {
    std::cin >> V >> E >> R;
    edges.resize(E);
    dist.assign(V + 1, INF);
    for(int i = 0; i < E; ++i){
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
}

// 벨만포드: start부터 각 정점까지의 최단거리를 구함
// 다익스트라와 비슷하지만 인접노드가 아닌 모든 노드를 확인하기 때문에 음수간선이 존재해도 최적해를 구할 수 있음(대신 느림)
// V - 1 번 반복 (한정점에서 다른 정점까지 가는 최대 간선 수)
// V번째에 갱신이 된다면 음수 사이클이 존재한다는 의미
// 시간복잡도: O(VE)
bool BellmanFord(int start) {
    dist[start] = 0;

    for(int i = 0; i < V; ++i) {
        for(const auto& edge : edges) {
            int from = edge.from;
            int to = edge.to;
            int weight = edge.weight;

            if(dist[from] != INF && dist[from] + weight < dist[to]){
                dist[to] = dist[from] + weight;
                if(i == V - 1){
                    return false;
                }
            }
        }
    }

    return true;
}

void Print() {
    for(int i = 1; i <= V; ++i){
        std::cout << i << ": " << dist[i] << '\n';
    }
}

int main() {
    Input();
    bool success = BellmanFord(R);

    if(success) {
        Print();
    }else {
        std::cout << "음수 사이클 존재\n"; 
    }

    return 0;
}

/* input 
3 4 1
1 2 4
1 3 3
2 3 -1
3 1 -2
*/
/* output
1 : 0
2 : 4
3 : 3
*/