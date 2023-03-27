#include <vector>
#include <iostream>
#include <queue>

using std::vector;
using std::priority_queue;
using std::pair;

#define INF 999999999

vector<vector<pair<int,int>>> graph; // {정점, 비용}
vector<int> dist;

int V, E; // 정점 수 / 간선 수
int R; // 시작노드

void Input() {
    std::cin >> V >> E >> R;
    graph.assign(V + 1, vector<pair<int,int>>());
    dist.assign(V + 1, INF);
    for(int i = 0; i < E; ++i){
        int start, end, cost;
        std::cin >> start >> end >> cost;
        graph[start].push_back({end, cost});
    }
}

// start 부터 각 정점까지의 최단거리를 구함
void Dijkstra(int start) {
    priority_queue<pair<int, int>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        int cost = -pq.top().first;
        int current = pq.top().second;
        pq.pop();

        for(int i = 0; i < graph[current].size(); ++i){
            int next = graph[current][i].first;
            int nextCost = cost + graph[current][i].second;
            if(nextCost < dist[next]){
                dist[next] = nextCost;
                pq.push({-nextCost, next});
            }
        }
    }
}

int main () {
    Input();
    Dijkstra(R);
    
    for(int i = 1; i <= V; ++i){
        std::cout << i << " : " << dist[i] << '\n';
    }
    return 0;
}


/* input 
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
*/
/* output
1 : 1
2 : 0
3 : 3
4 : 7
*/