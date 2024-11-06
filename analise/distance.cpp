#include <bits/stdc++.h>
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;

vi bfs(graph G, int a)
{
    vi dist(G.size(), G.size() * 2);
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

    return dist;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    vi tot;
    ld mean = 0;

    ofstream outfile("distance");

    for (int a = 0; a < n; a++){
        vi dist = bfs(G, a);
        for (auto x : dist){
            outfile << x << ' ';
            mean += x;
        }
    }

    outfile << '\n';
    outfile.close();

    cout << mean / ((ll)n * n) << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}