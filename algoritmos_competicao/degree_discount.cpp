#include <bits/stdc++.h>
#include "pq.cpp"

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;

vi degree_discount(const graph &G, int k, const vi &S)
{
    double p = 0.2;
    vi result;
    PriorityQueue dd;          // degree discount
    unordered_map<int, int> t; // number of adjacent vertices that are in S
    unordered_map<int, int> d; // degree of each vertex
    unordered_set<int> excluded_nodes(S.begin(), S.end());
    vector<bool> selected(G.size(), false); // vetor booleano para rastrear vértices selecionados

    // initialize degree discount
    for (int u = 0; u < G.size(); ++u)
    {
        if (excluded_nodes.find(u) == excluded_nodes.end())
        {
            d[u] = G[u].size();    // each neighbor adds degree 1
            dd.add_task(u, -d[u]); // add degree of each node
            t[u] = 0;
        }
    }

    // add vertices to result greedily
    for (int i = 0; i < k; ++i)
    {
        auto [u, priority] = dd.pop_item(); // extract node with maximal degree discount
        if (u == -1)
            break; // No more nodes to select
        result.push_back(u);
        selected[u] = true; // Marcar o vértice como selecionado
        for (int v : G[u])
        {
            if (excluded_nodes.find(v) == excluded_nodes.end() && !selected[v])
            {
                t[v]++;                                                           // increase number of selected neighbors
                double new_priority = d[v] - 2 * t[v] - (d[v] - t[v]) * t[v] * p; // discount of degree
                dd.add_task(v, -new_priority);
            }
        }
    }
    return result;
}