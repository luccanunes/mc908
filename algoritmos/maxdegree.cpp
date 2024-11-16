#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;

// Constrói vetor em ordem de grau de saída
vector<pii> max_degree(graph G)
{
    vector<pii> v;

    // Constrói o vetor
    for (int i = 0; i < G.size(); i++)
    {
        v.push_back({G[i].size(), i});
    }

    // Retorna em ordem
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());

    return v;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    // Lê o grafo
    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    // Imprime os vértices em ordem de grau
    vector<pii> deg = max_degree(G);
    
    for (auto x : deg)
        cout << x.second << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}