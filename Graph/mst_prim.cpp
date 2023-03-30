#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;
using std::pair;

vector<vector<pair<int,int>>> graph; // {정점, 비용}
vector<bool> visited;

int V, E; // 정점 수 / 간선 수
int R; // 시작노드

void Input() {
    std::cin >> V >> E >> R;
    graph.assign(V + 1, vector<pair<int,int>>());
    visited.assign(V + 1, false);
    for(int i = 0; i < E; ++i){
        int start, end, cost;
        std::cin >> start >> end >> cost;
        graph[start].push_back({end, cost});
        graph[end].push_back({start, cost});
    }
}

// 프림: 하나의 노드부터 시작하여 연결된 모든 간선을 우선순위 큐에 넣으면서 방문하지 않은 가장 짧은 간선만 택하여 연결
// 시간복잡도: ElogV
// 주의) 프림 알고리즘은 무방향 그래프에서만 가능하기 때문에 겹치는 방향이 있는 단방향 그래프면 크루스칼을 사용해야 한다.
int prim () {
    priority_queue<pair<int,int>> pq;
    visited[R] = true;
    int mstWeight = 0;

    // 시작노드와 연결 된 간선 추가
    for(const auto& edge : graph[R])  {
        pq.push({-edge.second, edge.first});
    }

    while(!pq.empty()){
        int cost = -pq.top().first;
        int current = pq.top().second;
        pq.pop();

        // 방문안한 노드라면 간선 연결후 큐에 이어진 간선 추가
        if(visited[current]) continue;
        visited[current] = true;
        mstWeight += cost;

        for(const auto& edge : graph[current]){
            pq.push({-edge.second, edge.first});
        }
    }

    return mstWeight;
}

int main () {
    Input();
    int mstWeight = prim();

    std::cout << mstWeight << '\n';

    return 0;
}

/* input 
7 12 1
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