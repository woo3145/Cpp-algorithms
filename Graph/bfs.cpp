#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;

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

void BFS(int start) {
    queue<int> que;
    que.push(start);
    visited[start] = true;

    while(!que.empty()) {
        int current = que.front();
        que.pop();
        std::cout << "방문 : " << current << "\n";
        for(int i = 0; i < graph[current].size(); ++i){
            int next = graph[current][i];
            if(!visited[next]){
                que.push(next);
                visited[next] = true;
            }
        }
    }

}

int main () {
    Input();
    BFS(R);
    return 0;
}

/* input 
5 5 1
1 4
1 2
2 3
2 4
3 4
*/
/* output
1
4
2
3
*/