#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef vector<unordered_set<int>> graph_set;

vi prado_nunes(const graph &G, int k, const vi &S)
{
    const int steps = 100;
    const double P = 0.2;
    unordered_set<int> excluded_nodes(S.begin(), S.end());
    vector<pair<int, int>> vertex_values; // Par de (valor, vértice)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // Converter o grafo para vector<unordered_set<int>>
    graph_set g_set(G.size());
    for (int u = 0; u < G.size(); ++u)
        for (int v : G[u])
            g_set[u].insert(v);

    // Calcular o valor de cada vértice
    for (int u = 0; u < g_set.size(); ++u)
    {
        if (excluded_nodes.count(u))
            continue;

        vector<bool> visited(g_set.size(), false);
        visited[u] = true;
        vi influenced = {u};
        for (int i = 0; i < steps; ++i)
        {
            vector<pii> taken_edges;
            for (int node : influenced)
                for (int neighbor : g_set[node])
                    if (!visited[neighbor] && dis(gen) < P)
                        taken_edges.push_back({node, neighbor});
            for (auto [a, b] : taken_edges)
            {
                influenced.push_back(b);
                visited[b] = true;
                g_set[a].erase(b);
            }
        }
        vertex_values.push_back({influenced.size() / steps, u});
    }

    // Ordenar os vértices pelo valor em ordem decrescente
    sort(vertex_values.rbegin(), vertex_values.rend());

    // Selecionar os K vértices de maior valor
    vi result;
    for (int i = 0; i < k && i < vertex_values.size(); ++i)
    {
        result.push_back(vertex_values[i].second);
    }

    return result;
}