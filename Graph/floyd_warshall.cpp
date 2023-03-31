#include <iostream>
#include <vector>

using std::vector;

#define INF 999999999

int V, E; // 정점 수 / 간선 수
vector<vector<int>> graph;

void Input () {
    std::cin >> V >> E;
    graph.assign(V + 1, vector<int>(V + 1, INF));
    for(int i = 0; i < E; ++i){
        int from, to, weight;
        std::cin >> from >> to >> weight;
        if(weight < graph[from][to]){
            graph[from][to] = weight;
        }
    }
    // 시작점과 끝점이 같은 곳은 0으로 초기화
    for(int i = 1; i <= V; ++i) {
        graph[i][i] = 0;
    }
}

// 플로이드 와샬: 모든 정점을 하나씩 k로 잡고 i -> j 와 i -> k -> j의 경로 중 짧은쪽을 선택
// 점화식: graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])
// 시간복잡도: (OV^3)
void FloydWarshall () {
    for(int k = 1; k <= V; ++k) {
        for(int i = 1; i <= V; ++i) {
            for(int j = 1; j <= V; ++j){
                if(graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

void Print () {
    for(int i = 1; i <= V; ++i){
        for(int j = 1; j <= V; ++j) {
            if(INF <= graph[i][j]) {
                std::cout << "INF" << ' ';
            }else {
                std::cout << graph[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main () {
    Input();
    FloydWarshall();
    Print();

    return 0;
}

/* input 
5 14
1 2 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1
3 5 1
4 5 3
3 5 10
3 1 8
1 4 2
5 1 7
3 4 2
5 2 4
*/
/* output
 0  2  3  1  4 
12  0 15  2  5 
 8  5  0  1  1 
10  7 13  0  3 
 7  4 10  6  0 
*/