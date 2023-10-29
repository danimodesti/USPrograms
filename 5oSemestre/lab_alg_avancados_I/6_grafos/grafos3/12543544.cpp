#include <iostream>
#include <vector>
#include <queue>

#define IMPOSSIBLE -1

#define BLANK_TEAM 0
#define BLUE_TEAM 1
#define RED_TEAM 2

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> adjacency_list;

void read_graph(adjacency_list& graph, ll edge_amt);
void print_graph(adjacency_list& graph);
bool bfs(adjacency_list& graph, ll starting_vertex, vector<int>& team_assignment);

int main() {
    int pupil_amt, friendship_amt;

    cin >> pupil_amt >> friendship_amt;
    adjacency_list graph(pupil_amt);

    read_graph(graph, friendship_amt);

    vector<int> team_assignment(pupil_amt, BLANK_TEAM);

    bool is_possible = true;
    for (int i = 0; i < pupil_amt; i++) {
        if (team_assignment[i] == BLANK_TEAM and is_possible) {
            is_possible = bfs(graph, i, team_assignment);
        }
    }

    if (is_possible) {
        for (int i = 0; i < pupil_amt; i++) {
            cout << team_assignment[i] << ' ';
        }

        cout << '\n';
    }

    else {
        cout << "IMPOSSIBLE" << '\n';
    }

    return EXIT_SUCCESS;
}

void read_graph(adjacency_list& graph, ll edge_amt) {
    for (ll i = 0; i < edge_amt; i++) {
        ll first_vertex, second_vertex;

        cin >> first_vertex >> second_vertex;

        // Adicionando arestas - grafo nao dirigido
        graph[first_vertex - 1].push_back(second_vertex - 1);
        graph[second_vertex - 1].push_back(first_vertex - 1);
    }
}

void print_graph(adjacency_list& graph) {
    ll vertex_amt = graph.size();

    for (ll i = 0; i < vertex_amt; i++) {
        cout << "adjacentes ao vertice " << i + 1 << ": \n";
        for (ll adj : graph[i]) { // Vertices adjacentes ao vertice graph[i]
            cout << adj + 1 << '\n';
        }

        cout << '\n';
    }
}

bool bfs(adjacency_list& graph, ll starting_vertex, vector<int>& team_assignment) {
    queue<ll> q;
    int vertex_amt = graph.size();

    vector<bool> visited(vertex_amt, false);
    
    q.push(starting_vertex);
    team_assignment[starting_vertex] = BLUE_TEAM;

    while (!q.empty()) {
        ll u = q.front(); q.pop();
        int curr_color = (team_assignment[u] == BLUE_TEAM) ? RED_TEAM : BLUE_TEAM;

        if (!visited[u]) {
            visited[u] = true;

            for (auto neighbor : graph[u]) {
                if (team_assignment[neighbor] == BLANK_TEAM) {
                    q.push(neighbor);
                    team_assignment[neighbor] = curr_color;
                }

                // Nao eh possivel ser grafo bipartido
                else if (team_assignment[neighbor] != curr_color) {
                    return false;
                }
            }
        }
    }

    return true;
}