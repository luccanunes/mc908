#include <bits/stdc++.h>
#include "pq.h"

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;

// Função para calcular a distância mínima de um nó para um conjunto S
double min_dist(const graph &G, const vi &result, int no)
{
    double min_dist = numeric_limits<double>::infinity();
    for (int u : result)
    {
        if (find(G[no].begin(), G[no].end(), u) != G[no].end())
        {
            min_dist = min(1.0, min_dist); // Cada aresta tem peso 1
        }
    }
    return min_dist == numeric_limits<double>::infinity() ? -1 : min_dist;
}

// Algoritmo representative_nodes_min
vi representative_nodes_min(const graph &G, int k, const vi &S)
{
    vi result;            // Conjunto de nós escolhidos
    PriorityQueue S_dist; // Fila de prioridade para distâncias
    unordered_set<int> excluded_set(S.begin(), S.end());
    set<int> selected; // vetor booleano para rastrear vértices selecionados
    // Inicializar result com os vértices mais distantes
    int u = 0, v = 0;
    double max_weight = -1;
    for (int i = 0; i < G.size(); ++i)
    {
        for (int j : G[i])
        {
            if (max_weight < 1)
            { // Cada aresta tem peso 1
                max_weight = 1;
                u = i;
                v = j;
                break;
            }
        }
    }
    result.push_back(u);
    result.push_back(v);
    selected.insert(u);
    selected.insert(v);
    // Calcular distâncias de cada nó em G para result
    for (int v = 0; v < G.size(); ++v)
        if (!selected.count(v))
            S_dist.add_task(v, -min_dist(G, result, v)); // Usar negativo para obter o valor máximo da fila de prioridade
    // Adicionar novos nós ao conjunto de forma gulosa
    while (result.size() < k)
    {
        auto [u, priority] = S_dist.pop_item(); // Encontrar o valor máximo da distância para o conjunto result
        if (excluded_set.count(u))
            continue;
        result.push_back(u); // Adicionar o nó ao conjunto result
        selected.insert(u);  // Marcar o vértice como selecionado
        // Aumentar a distância apenas para nós conectados a u
        for (int v : G[u])
        {
            if (!selected.count(v))
            {
                double prev_priority = S_dist.get_priority(v);
                double new_priority = max(prev_priority, -1.0); // Atualizar a distância mínima
                S_dist.add_task(v, new_priority);
            }
        }
    }
    return result;
}