#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> graph;

const ld ap = 0.85;
vector<ld> page;
vector<int> degout;

// Iteração do PageRanking
void update(graph G)
{
    vector<ld> aux(G.size());

    // O (m)
    for (int i = 0; i < G.size(); i++)
    {
        aux[i] = (1 - ap) / G.size();
        for (auto x : G[i])
        {
            aux[i] += ap * page[x] / degout[x];
        }
    }

    page = aux;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    // Lê o grafo
    graph G(n);
    degout.resize(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[b].push_back(a);
        degout[a]++;
    }

    // 100 iterações para atualizar a centralidade
    page.resize(n, 1 / (ld)n);
    int times = 100;
    for (int i = 0; i < times; i++)
    {
        update(G);
    }

    // Imprime os vértices em ordem de PageRanking
    vector<pair<ld, int>> aux(G.size());

    for (int i = 0; i < G.size(); i++)
    {
        aux[i].second = i;
        aux[i].first = page[i];
    }

    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());

    for (auto x : aux)
    {
        cout << x.second << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}