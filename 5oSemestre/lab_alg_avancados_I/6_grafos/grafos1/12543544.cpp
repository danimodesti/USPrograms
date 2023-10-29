#include <iostream>
#include <vector>
#include <queue>

#define INFINITY __LONG_LONG_MAX__ - 1

using namespace std;

typedef long long ll;
typedef vector<vector<pair<ll, ll>>> adjacency_list;

void read_graph(adjacency_list& graph, ll edge_amt);
void print_graph(adjacency_list& graph);
vector<ll> dijkstra(adjacency_list& graph, ll starting_vertex);

struct cmp {
    bool operator()(const pair<ll, ll>& a, const pair<ll, ll>& b) const {
        return a.first > b.first;
    }
};

int main() {

    ll city_amt, road_amt, query_amt;

    cin >> city_amt >> road_amt >> query_amt;

    adjacency_list graph(city_amt);

    // Responder perguntas possivelmente repetidas. Celulas comecam com vetores vazios
    vector<vector<ll>> MEMO(city_amt, vector<ll>(city_amt, -1));

    read_graph(graph, road_amt);

    for (ll i = 0; i < query_amt; i++) {
        ll starting_vertex, destination_vertex;
        cin >> starting_vertex >> destination_vertex;

        // Pergunta ja foi feita antes?
        if (MEMO[starting_vertex - 1][destination_vertex - 1] == -1) { // Nao calculou ainda
            MEMO[starting_vertex - 1] = dijkstra(graph, starting_vertex - 1);
        }

        ll distance = MEMO[starting_vertex - 1][destination_vertex - 1];
        ll answer = (distance == INFINITY) ? -1 : distance;

        cout << answer << '\n';
    }

    return EXIT_SUCCESS;
}

void read_graph(adjacency_list& graph, ll edge_amt) {
    for (ll i = 0; i < edge_amt; i++) {
        ll first_vertex, second_vertex;
        ll distance_between;

        cin >> first_vertex >> second_vertex >> distance_between;

        // Adicionando arestas - grafo nao dirigido
        graph[first_vertex - 1].push_back({second_vertex - 1, distance_between});
        graph[second_vertex - 1].push_back({first_vertex - 1, distance_between});
    }
}

void print_graph(adjacency_list& graph) {
    ll vertex_amt = graph.size();

    for (ll i = 0; i < vertex_amt; i++) {
        cout << "adjacentes ao vertice " << i + 1 << ": ";
        for (pair<ll, ll> adj : graph[i]) { // Vertices adjacentes ao vertice graph[i] e sua distancia em rel. ao graph[i]
            cout << '(' << adj.first + 1 << ", " << adj.second << ") ";
        }

        cout << '\n';
    }
}

vector<ll> dijkstra(adjacency_list& graph, ll starting_vertex) {
    ll vertex_amt = graph.size();

    vector<ll> distances(vertex_amt);

    // O par guarda primeiro a distancia minima e depois o vertice referente a ela
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> to_select_vertexes;

    // Para cada vertice no grafo... [inicializar distancias a partir do v. de partida]
    for (ll v = 0; v < vertex_amt; v++) {
        distances[v] = INFINITY; 
    }

    // Vertice inicial ja esta nele mesmo
    distances[starting_vertex] = 0;
    to_select_vertexes.push({0, starting_vertex});


    while (!to_select_vertexes.empty()) {
        pair<ll, ll> curr = to_select_vertexes.top();
        to_select_vertexes.pop();

        // Vertice selecionado atualmente; tem a menor 
        // distancia em relacao ao starting_vertex
        ll u = curr.second;
        ll dist_u = curr.first;

        // Testar se informacao de distancia(starting_vertex, u) eh a mais atual
        // (para isso, olhar vetor distances[u]).
        // Se nao for (dist_u <= distances[u]), ignorar esse valor e apenas remover, 
        // pois a fila guarda valores mais atualizados que aparecem depois.
        if (dist_u <= distances[u]) { // Significa que dist_u eh atualizado
            distances[u] = dist_u; // Atualizar v. de distancias com info mais atual de caminho minimo

            // Tentar relaxar
            for (pair<ll, ll> adj : graph[u]) { // Vertices adjacentes ao vertice graph[u] e sua distancia em rel. ao graph[u]
                ll v = adj.first;
                ll distance_between = adj.second; // distancia (u, v) ou c(u, v)

                // Atualizacao de caminho minimo, qdo houver rotas indiretas menores que as atuais para um dado vertice
                ll new_indirect_path = distances[u] + distance_between;
                if (new_indirect_path < distances[v]) { // Relaxamento de vertice v
                    distances[v] = new_indirect_path;

                    // Adicionar valor atual na fila
                    to_select_vertexes.push({distances[v], v});
                }
            }
        }

    }

    return distances;
}