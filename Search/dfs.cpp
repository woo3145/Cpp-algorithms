#include <vector>
#include <iostream>

using std::vector;

vector<vector<int>> graph;
vector<bool> visited;
int V, E; // 정점 수 / 간선 수
int R; // 시작노드

void Input() {
    std::cin >> V >> E >> R;
    graph.assign(V + 1, vector<int>());
    visited.assign(V + 1, false);
    for(int i = 0; i < E; ++i){
        int start, end;
        std::cin >> start >> end;
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
}

void DFS(int node) {
    visited[node] = true;
    std::cout << "방문 : " << node << "\n";
    for(int i = 0; i < graph[node].size(); ++i){
        int next = graph[node][i];
        if(!visited[next]){
            visited[next] = true;
            DFS(next);
        }
    }

}

int main () {
    Input();
    DFS(R);
    return 0;
}

/* input 
4 5 1
1 2
1 3
1 4
2 4
3 4
*/
/* output
1
2
4
3
*/