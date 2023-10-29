#include <iostream>
#include <climits> // LONG_LONG_MAX
#include <queue>
#include <vector>

using namespace std;

#define MAX 500 + 1 // Ignorar o zero e comecar contagem de vertices em 1

long long original_graph[MAX][MAX]; // Guarda os pesos em relacao a 2 vertices i, j 
long long residual_graph[MAX][MAX]; // Grafo para manipulacao do fluxo

void init_matrix(int node_amt);
void read_graph(int edge_amt);
long long edmonds_karp(int node_amt, int src_node, int dst_node);
void dfs(int node_amt, vector<bool>& visited, int curr_node);

int main() {
    int city_amt, connection_amt;
    
    while (cin >> city_amt >> connection_amt and city_amt != 0 and connection_amt != 0) {
        init_matrix(city_amt);
        read_graph(connection_amt);
        edmonds_karp(city_amt, 1, 2);

        vector<bool> visited(city_amt + 1, false);
        dfs(city_amt, visited, 1);

        for (int i = 1; i <= city_amt; i++) {
            for (int j = 1; j <= city_amt; j++) {
                if (original_graph[i][j] > 0 and visited[i] and !visited[j]) {
                    cout << i << ' ' << j << '\n';
                }
            }
        }

        cout << '\n';
    }

    return EXIT_SUCCESS;
}

void init_matrix(int node_amt) {
    for (int i = 1; i <= node_amt; i++) {
        for (int j = 1; j <= node_amt; j++) {
            // 'Peso' ou capacidade 0 entre vertices: sem conexao, inicialmente.
            // Nos isolados.
            original_graph[i][j] = 0; // Distancia entre vertice i e vertice j
            residual_graph[i][j] = 0; // Distancia entre vertice i e vertice j
        }
    }
}

void read_graph(int edge_amt) {
    // Matriz de adj
    for (int i = 0; i < edge_amt; i++) {
        int u, v;
        long long w;

        cin >> u >> v >> w;

        // Grafos sao dirigidos

        // Pode haver mais de uma conexao entre um mesmo par de vertices
        // (por isso o incremento).
        original_graph[u][v] += w;
        original_graph[v][u] += w;

        residual_graph[u][v] += w;
        residual_graph[v][u] += w;
    }
}

bool bfs(int node_amt, vector<int>& parents, int src_node, int dst_node) {
    vector<bool> visited(node_amt + 1);
    queue<int> q;
    
    parents.assign(node_amt + 1, -1);
    visited.assign(node_amt + 1, false);

    q.push(src_node);
    while (!q.empty()) {
        int u = q.front(); q.pop(); // Tirar vertice da fila
        visited[u] = true; // Visitar vertice

        // Para todas as conexoes de u com v (ha conexao se > 0)
        for (int v = 1; v <= node_amt; v++) {
            if (residual_graph[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                parents[v] = u;

                // 'Nova camada' de vertices para visitar posteriormente
                q.push(v);
            }
        }
    }

    // Se ha um caminho ate dst_node
    if (visited[dst_node]) {
        return true;
    }

    return false;
}

void dfs(int node_amt, vector<bool>& visited, int curr_node) {
    visited[curr_node] = true;
    for (int i = 1; i <= node_amt; i++) {
        if (!visited[i] and residual_graph[curr_node][i] > 0) {
            dfs(node_amt, visited, i);
        }
    }
}

long long find_bottleneck(int node_amt, vector<int>& parents, int src_node, int dst_node) {
    long long bottleneck = LONG_LONG_MAX / 2;

    int v = dst_node;
    while (v != src_node) {
        int u = parents[v]; // Aresta: de u para v
        
        // Achar 'gargalo' do caminho encontrado:
        // maximo de fluxo que passa por aquele caminho
        bottleneck = min(bottleneck, residual_graph[u][v]);

        // Caminhar 'para tras' ate chegar no src_node, procurando
        // maior capacidade possivel para o caminho todo
        v = u;
    }

    return bottleneck;
}

void update_flow(long long bottleneck, int node_amt, vector<int>& parents, int src_node, int dst_node) {
    int v = dst_node;
    while (v != src_node) {
        int u = parents[v]; // Aresta: de u para v
        
        // Transmitir a capacidade maxima 
        residual_graph[u][v] -= bottleneck; // Fwd edge
        
        // Indicar o qto da para retornar do flow
        residual_graph[v][u] += bottleneck; // Backwards edge

        // Caminhar 'para tras' ate chegar no src_node
        v = u;
    }
}

long long edmonds_karp(int node_amt, int src_node, int dst_node) {
    vector<int> parents(node_amt + 1);

    long long max_flow = 0;

    // Enquanto houver caminho
    while (bfs(node_amt, parents, src_node, dst_node)) {
        long long bottleneck = find_bottleneck(node_amt, parents, src_node, dst_node);
        
        update_flow(bottleneck, node_amt, parents, src_node, dst_node);

        // Fluxo total de dados no grafo, considerando todos
        // os caminhos 'parciais'
        max_flow += bottleneck;
    }

    return max_flow;
}