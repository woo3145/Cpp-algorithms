#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;

vector<vector<int>> graph;

int V, E; // 정점 수 / 간선 수

void Input() {
    std::cin >> V >> E;
    graph.resize(V + 1);
    for(int i = 0; i < E; ++i){
        int start, end;
        std::cin >> start >> end;
        graph[start].push_back(end);
    }
}

// 위상정렬
// 1. 진입차수 배열 생성 후 차수가 0인 정점을 큐에 담아줌
// 2. 큐가 빌때까지 큐에서 원소를 뽑아 인접한 정점의 차수를 감소시켜 차수가 0이 되면 큐에 담아줌
void TopologySort () {
    vector<int> inDegree(V + 1, 0);

    // 진입차수 추가
    for(int i = 1; i <= V; ++i){
        for(const int& v : graph[i]){
            ++inDegree[v];
        }
    }

    // 진입차수가 0인 정점 큐에 삽입
    queue<int> que;
    for(int i = 1; i <= V; ++i){
        if(inDegree[i] == 0) {
            que.push(i);
        }
    }

    // 위상정렬
    int idx = 0;
    vector<int> order(V);
    while(!que.empty()){
        int cur = que.front();
        que.pop();

        order[idx] = cur;
        ++idx;
        for(const int& v : graph[cur]) {
            --inDegree[v];
            if(inDegree[v] == 0) {
                que.push(v);
            }
        }
    }

    // 출력
    if(idx != V) {
        std::cout << "사이클 존재" <<idx << V << '\n';
        return;
    }
    for(int i = 0; i < V; ++i){
        std::cout << order[i] << ' ';
    }
}

int main () {
    Input();
    TopologySort();

    return 0;
}

/* input 
4 2
4 2
3 1
*/
/* output
3 4 1 2
*/