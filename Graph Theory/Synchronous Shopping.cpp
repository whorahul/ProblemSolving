#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <limits>
#include <cstring>

using namespace std;

#define MAX_NODES 1003
#define MAX_FISH  1030

int shops[MAX_NODES];
int shortest_path[MAX_NODES][MAX_FISH];
vector<pair<int,int>> graph [MAX_NODES];
set<pair<int, pair<int,int>>> queue;

void InQueue(int node, int mask, int cost) {
    if (shortest_path[node][mask] <= cost) {
        // we can reach here with less cost fuck off!
        return;
    }
    /* update the shortest_path
       - remove the old
       - add the new
    */
    pair<int, pair<int,int>> current = make_pair(shortest_path[node][mask], make_pair(node, mask));
    auto it = queue.find(current);
    if (it != queue.end()) {
        queue.erase(it);
    }
    shortest_path[node][mask] = cost;
    current.first = cost;
    queue.insert(current);  
}
//hackerrank.com/whorahul
void Dijkstra(int src) {
    InQueue(src, shops[src], 0);
    while (!queue.empty()) {
        int cost = queue.begin()->first;
        int current_shops = queue.begin()->second.second;
        src = queue.begin()->second.first;
        queue.erase(queue.begin());
        for (const auto& neighbour: graph[src]) {
            InQueue(neighbour.first, current_shops | shops[neighbour.first], cost + neighbour.second);
        }
    }
}
void ClearStates() {
    memset(shops, 0, sizeof(shops));
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_FISH; j++) {
            shortest_path[i][j] = numeric_limits<int>::max() / 2;
        }
    }
}
int main() {
    int n_cities, n_roads, fish_types_no, t, current_fish_type, from, to, cost;
    cin >> n_cities >> n_roads >> fish_types_no;
    ClearStates();
    for (int i = 1; i <= n_cities; i++) {
        cin >> t;
        while (t--) {
            cin >> current_fish_type;
            shops[i] |= (1 << (current_fish_type - 1));
        }
    }
    while (n_roads--) {
        cin >> from >> to >> cost;
        graph[from].emplace_back(to, cost);
        graph[to].emplace_back(from, cost);
    }
    
    Dijkstra(1);
    //hackerrank.com/whorahul
    int best_time = numeric_limits<int>::max();
    for (int i = 0; i < (1 << fish_types_no) ; i++) {
       for (int j = i; j < (1 << fish_types_no); j++) {
           if ((i | j) == (1 << fish_types_no) - 1) {
               best_time = min (best_time, max(shortest_path[n_cities][i], shortest_path[n_cities][j]));
           }
       } 
    }
    cout << best_time << endl;
    return 0;
}
