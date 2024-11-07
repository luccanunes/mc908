#include <bits/stdc++.h>
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;

void solve()
{
    int n, m;
    cin >> n >> m;

    set<pii> arestas;

    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        arestas.insert({a, b});
    }

    cout << "A rede possui " << n << " vértices\n";
    cout << "A rede possui " << m << " arcos\n";
    cout << "A rede possui " << arestas.size() << " arcos distintos\n";
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}