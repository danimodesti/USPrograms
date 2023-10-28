#include <iostream>
#include <climits>
#include <tuple>
#include <vector>

using namespace std;

typedef pair<int, long> il; // Cada (id, peso); id do no e peso em relacao a outro 
typedef vector<il> vil; // Todas as ligacoes feitas por cada vertice
typedef vector<vil> adjacency_list; // Relacao de todos os vertices com suas conexoes

void read_graph(adjacency_list& graph, int edge_amt);
void print_graph(adjacency_list& graph);
bool bellman_ford(adjacency_list& graph, vector<long>& distances, int src_node);

int main() {
    int node_amt, edge_amt;
    cin >> node_amt >> edge_amt;

    adjacency_list graph(node_amt);
    read_graph(graph, edge_amt);

    vector<long> distances(node_amt);

    bool has_negative_cycle = bellman_ford(graph, distances, 1);
    
    if (has_negative_cycle) {
        cout << "YES\n";
    }

    else {
        cout << "NO\n";
    }

    return EXIT_SUCCESS;
}

void read_graph(adjacency_list& graph, int edge_amt) {
    for (int i = 0; i < edge_amt; i++) {
        int src_node, tgt_node, edge_weight;
        cin >> src_node >> tgt_node >> edge_weight;
        graph[src_node - 1].push_back(make_pair(tgt_node, edge_weight));
    }
}

void print_graph(adjacency_list& graph) {
    int node_amt = graph.size();

    for (int i = 0; i < node_amt; i++) {
        cout << i + 1 << "--> ";

        for (il p : graph[i]) { // Para cada pair p no vii
            cout << "(" << p.first << ", " << p.second << ") ";
        }

        cout << '\n';
    }
}

bool bellman_ford(adjacency_list& graph, vector<long>& distances, int src_node) {
    int node_amt = graph.size();

    // Inicializando vetor de distancias para o vertice de origem com 'infinito'
    distances.assign(node_amt, LONG_MAX / 2);

    // Distancia do vertice de origem ate ele mesmo
    distances[src_node - 1] = 0;

    // Rodar para 'numero maximo de arestas no pior caso' vezes
    for (int i = 0; i < node_amt - 1; i++) {
        for (int u = 1; u <= node_amt; u++) { // Para cada no que faz aresta (src node)
            for (il p : graph[u - 1]) { // Para cada pair p no vii
                int v = p.first; // dst node
                long w = p.second; // peso da aresta/edge uv

                // Relaxa
                if (distances[v - 1] > distances[u - 1] + w) {
                    distances[v - 1] = distances[u - 1] + w;
                }
            }
        }
    }

    // Apos os loops acima, tem-se a distancia minima em relacao ao src node (so faz sentido
    // para grafos sem ciclo negativo)

    // Mais um 'ciclo de relaxamento' para checar se ha ciclo negativo
    for (int u = 1; u <= node_amt; u++) { // Para cada no que faz aresta (src node)
        for (il p : graph[u - 1]) { // Para cada pair p no vii
            int v = p.first; // dst node
            long w = p.second; // peso da aresta/edge uv

            // Se fosse relaxar, tem um ciclo negativo
            if (distances[v - 1] > distances[u - 1] + w) {
                return true;
            }
        }
    }

    return false;
}