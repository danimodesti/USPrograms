#include <iostream>
#include <vector>
#include <queue>

#define IMPOSSIBLE -1

using namespace std;

typedef long long ll;
typedef vector<vector<pair<ll, ll>>> adjacency_list;

void read_graph(adjacency_list &graph, ll edge_amt);
void print_graph(adjacency_list &graph);
ll primMSTCost(adjacency_list &graph);

struct cmp {
    bool operator()(const pair<ll, ll> &a, const pair<ll, ll> &b) const {
        return a.first > b.first;
    }
};

int main() {
    int city_amt, road_amt;
    cin >> city_amt >> road_amt;

    adjacency_list graph(city_amt);

    read_graph(graph, road_amt);
    ll answer = primMSTCost(graph);

    (answer == IMPOSSIBLE) ? cout << "IMPOSSIBLE\n" : cout << answer << '\n';

    return EXIT_SUCCESS;
}

void read_graph(adjacency_list &graph, ll edge_amt) {
    for (ll i = 0; i < edge_amt; i++) {
        ll first_vertex, second_vertex;
        ll distance_between;

        cin >> first_vertex >> second_vertex >> distance_between;

        // Adicionando arestas - grafo nao dirigido
        graph[first_vertex - 1].push_back({second_vertex - 1, distance_between});
        graph[second_vertex - 1].push_back({first_vertex - 1, distance_between});
    }
}

void print_graph(adjacency_list &graph) {
    ll vertex_amt = graph.size();

    for (ll i = 0; i < vertex_amt; i++)
    {
        cout << "adjacentes ao vertice " << i + 1 << ": ";
        for (pair<ll, ll> adj : graph[i])
        { // Vertices adjacentes ao vertice graph[i] e sua distancia em rel. ao graph[i]
            cout << '(' << adj.first + 1 << ", " << adj.second << ") ";
        }

        cout << '\n';
    }
}

ll primMSTCost(adjacency_list &graph) {
    ll vertex_amt = graph.size();
    vector<bool> visited(vertex_amt, false);
    vector<ll> min_distance(vertex_amt, __LONG_LONG_MAX__);
    ll total_cost = 0;

    min_distance[0] = 0;

    // Usando fila de prioridade para obter o vértice de menor custo
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0, 0}); // Peso 0 para o vértice inicial

    while (!pq.empty()) {
        ll min_distance_vertex = pq.top().second;
        ll current_distance = pq.top().first;
        pq.pop();

        if (visited[min_distance_vertex]) {
            continue; // Ignorar vértices já visitados
        }

        visited[min_distance_vertex] = true;
        total_cost += current_distance;

        for (const auto& neighbor : graph[min_distance_vertex]) {
            ll v = neighbor.first;
            ll weight = neighbor.second;
            if (!visited[v] && weight < min_distance[v]) {
                min_distance[v] = weight;
                pq.push({ weight, v });
            }
        }
    }

    for (ll i = 0; i < vertex_amt; ++i) {
        if (min_distance[i] == __LONG_LONG_MAX__) {
            return IMPOSSIBLE; // Não é possível construir uma AGM, retorna -1
        }
    }

    return total_cost;
}