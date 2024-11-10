#include <bits/stdc++.h>
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;

graph G;
vi dist;

void bfs(int a)
{
    dist.resize(G.size(), G.size() * 2);
    queue<int> fila;

    fila.push(a);
    dist[a] = 0;

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
}

void solve()
{
    int n, m;
    cin >> n >> m;

    G.resize(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    ld mean = 0;

    for (int a = 0; a < n; a++){
        bfs(a);
        for (auto x : dist){
            cout << x << '\n';
            mean += x;
        }
    }
    // cout << '\n';

    // cout << mean / ((ll)n * n) << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}