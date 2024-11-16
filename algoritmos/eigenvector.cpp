#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> graph;

graph G;
vector<ld> eigenvector;

// Calcula a norma de um vetor v
vector<ld> norm(vector<ld> v)
{
    ld sum = 0;
    for (auto x : v)
        sum += x * x;
    sum = sqrtl(sum);

    for (int i = 0; i < v.size(); i++)
    {
        v[i] /= sum;
    }

    return v;
}

// Algoritmo de Von Mises para autovetor
void vonmises(graph G)
{
    vector<ld> aux(G.size());

    // O (m)
    for (int i = 0; i < G.size(); i++)
    {
        for (auto x : G[i])
        {
            aux[i] += eigenvector[x];
        }
    }

    eigenvector = aux;
    eigenvector = norm(eigenvector);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    eigenvector.resize(n);
    eigenvector[0] = 1;

    // Lê o grafo
    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    // 100 iterações de VonMises
    int times = 100;
    for (int i = 0; i < times; i++)
    {
        vonmises(G);
    }

    // Imprime vértices em ordem de autovalor
    vector<pair<ld, int>> aux(G.size());

    for (int i = 0; i < G.size(); i++)
    {
        aux[i].second = i;
        aux[i].first = eigenvector[i];
    }

    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());

    for (auto x : aux)
        cout << x.second << '\n';
}

// Só funciona se conexo
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}