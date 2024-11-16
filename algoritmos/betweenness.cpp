#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> graph;

graph G;
vector<pair<ld, int>> betweenness;

// Algoritmo de Brandes
void bfs(int a, graph G)
{
    // Ordem de cálculo do betweenness
    stack<int> ordem;

    // Fila da BFS
    queue<int> fila;
    fila.push(a);

    // Vetor de distâncias
    vi dist(G.size(), -1);
    dist[a] = 0;

    // Quantidade de caminhos mínimos partindo de a que passam por cada vértice
    vi qtdd(G.size());
    qtdd[a] = 1;

    // Todos os pais de um vértice seguindo a ordem da BFS
    vector<vi> pai(G.size());

    // BFS em O(m)
    while (!fila.empty())
    {
        int x = fila.front();
        fila.pop();
        ordem.push(x);

        for (auto y : G[x])
        {
            if (dist[y] < 0)
            {
                fila.push(y);
                dist[y] = dist[x] + 1;
            }

            if (dist[y] == dist[x] + 1)
            {
                qtdd[y] += qtdd[x];
                pai[y].push_back(x);
            }
        }
    }

    // Parte do cálculo do betweenness
    vector<ld> delta(G.size());

    // Cálculo de cada parte em O(m)
    while (!ordem.empty())
    {
        int x = ordem.top();
        ordem.pop();
        for (int y : pai[x])
        {
            delta[y] += ((ld)qtdd[y] / qtdd[x]) * (1 + delta[x]);
        }
        if (x != a)
        {
            betweenness[x].first += delta[x];
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    // Define o vetor de betweenness 
    betweenness.resize(n);
    for (int i = 0; i < n; i++)
    {
        betweenness[i].second = i;
    }

    // Lê o grafo
    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    // Faz a BFS de betweenness para cada vértice
    for (int i = 0; i < G.size(); i++)
    {
        bfs(i, G);
    }

    // Imprime os vértices por ordem de betweenness
    sort(betweenness.begin(), betweenness.end());
    reverse(betweenness.begin(), betweenness.end());

    for (auto x : betweenness)
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