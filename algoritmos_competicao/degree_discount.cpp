#include <bits/stdc++.h>
#include "pq.h"
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;

vi degree_discount(const graph &G, int k, const vi &S)
{
    const double p = 0.2;
    unordered_map<int, int> d; // degree of each vertex
    map<int, double> dd;       // degree discount
    unordered_map<int, int> t; // number of selected neighbors
    vi result;                 // selected set of nodes
    unordered_set<int> excluded_nodes(S.begin(), S.end());
    set<int> selected; // rastrear vértices selecionados

    // initialize degree discount
    for (int u = 0; u < G.size(); ++u)
    {
        d[u] = G[u].size(); // each neighbor adds degree 1
        dd[u] = d[u];
        t[u] = 0;
    }

    // add vertices to result greedily
    while (result.size() != k)
    {
        // find the node with the maximum degree discount
        int u = -1;
        double max_dd = -1;
        for (const auto &entry : dd)
        {
            if (entry.second > max_dd)
            {
                max_dd = entry.second;
                u = entry.first;
            }
        }

        if (excluded_nodes.count(u))
            continue;

        dd.erase(u);
        result.push_back(u);
        selected.insert(u); // Marcar o vértice como selecionado

        for (int v : G[u])
        {
            if (!selected.count(v))
            {
                t[v]++;                                             // increase number of selected neighbors
                dd[v] = d[v] - 2 * t[v] - (d[v] - t[v]) * t[v] * p; // discount of degree
            }
        }
    }

    return result;
}