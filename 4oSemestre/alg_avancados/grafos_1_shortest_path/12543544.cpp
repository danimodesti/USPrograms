#include <iostream>
#include <climits>

using namespace std;

#define MAX 500 + 1 // Ignorar o zero e comecar contagem de vertices em 1

long distances_matrix[MAX][MAX]; // Guarda os pesos em relacao a 2 vertices i, j 

void init_matrix(int node_amt);
void print_matrix(int node_amt);
void floyd_warshall(int node_amt);
void answer_query(int src_node, int dst_node);

int main() {
    int node_amt, edge_amt, query_amt;
    cin >> node_amt >> edge_amt >> query_amt;

    init_matrix(node_amt);

    // Matriz de adj neste ponto
    for (int i = 0; i < edge_amt; i++) {
        int u, v;
        long w;
        cin >> u >> v >> w;
        distances_matrix[u][v] = w;
        distances_matrix[v][u] = w; // Grafo nao dirigido
    }
    
    floyd_warshall(node_amt);

    for (int i = 0; i < query_amt; i++) {
        int u, v;
        cin >> u >> v;

        answer_query(u, v);
    }

    return EXIT_SUCCESS;
}

void init_matrix(int node_amt) {
    for (int i = 1; i <= node_amt; i++) {
        for (int j = 1; j <= node_amt; j++) {
            if (i == j) {
                distances_matrix[i][j] = 0; // Distancia entre vertice e ele proprio    
            }

            else {
                distances_matrix[i][j] = LONG_MAX / 2;
            }
        }
    }
}

void print_matrix(int node_amt) {
    for (int i = 1; i <= node_amt; i++) {
        for (int j = 1; j <= node_amt; j++) {
            cout << distances_matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

void floyd_warshall(int node_amt) {
    for (int k = 1; k <= node_amt; k++) { // Pivo
        for (int u = 1; u <= node_amt; u++) { // u = src node
            for (int v = 1; v <= node_amt; v++) { // v = dst node
                if (distances_matrix[u][v] >= distances_matrix[u][k] + distances_matrix[k][v]) {
                    distances_matrix[u][v] = distances_matrix[u][k] + distances_matrix[k][v];
                }
            }
        }
    }
}

void answer_query(int src_node, int dst_node) {
    long dist = distances_matrix[src_node][dst_node];

    if (dist != LONG_MAX / 2) {
        cout << distances_matrix[src_node][dst_node] << '\n';
    }

    else {
        cout << -1 << '\n';
    }
}