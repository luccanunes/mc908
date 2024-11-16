#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> graph;

// BFS para calcular todas as distâncias a partir de a
vi bfs(graph G, int a)
{
    // Distâncias (INF = m * 2)
    vi dist(G.size(), G.size() * 2);
    dist[a] = 0;

    // Fila da BFS
    queue<int> fila;
    fila.push(a);

    // BFS em O(m)
    while (!fila.empty())
    {
        int x = fila.front();
        fila.pop();

        for (auto y : G[x])
        {
            if (dist[y] >= G.size() * 2)
            {
                fila.push(y);
                dist[y] = dist[x] + 1;
            }
        }
    }

    return dist;
}

// Constrói vetor de closeness
vector<pair<ld, int>> closeness(graph G)
{
    // Define vetor
    vector<pair<ld, int>> closeness(G.size());

    // Para cada vértice, calcula o closeness
    for (int i = 0; i < G.size(); i++)
    {
        vi v = bfs(G, i);
        closeness[i].second = i;
        for (auto x : v)
        {
            closeness[i].first += x;
        }
        closeness[i].first = (G.size() - 1) / closeness[i].first;
    }

    // Ordena
    sort(closeness.begin(), closeness.end());
    reverse(closeness.begin(), closeness.end());

    return closeness;
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

    // Imprime os vértices por ordem de closeness
    vector<pair<ld, int>> close = closeness(G);

    for (auto x : close)
        cout << x.second << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}