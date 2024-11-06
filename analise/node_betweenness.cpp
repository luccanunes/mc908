#include <bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(), x.end()
#define pc __builtin_popcount
#define F first
#define S second

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;

const int maxn = 1e3 + 5, inf = 2e9, M = 1e9 + 7;
const ll linf = 1e18;
graph G;
vector<ld> betweenness;

// Brandes
void bfs(int a, graph G)
{
    stack<int> ordem;

    queue<int> fila;
    fila.push(a);

    vi dist(G.size(), -1);
    dist[a] = 0;

    vi qtdd(G.size());
    qtdd[a] = 1;

    vector<vi> pai(G.size());

    // O(m)
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

    vector<ld> delta(G.size());

    // O(m)
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
            betweenness[x] += delta[x];
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    betweenness.resize(n);

    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    for (int i = 0; i < G.size(); i++)
    {
        bfs(i, G);
    }

    ofstream outfile("node_betweenness");

    for (auto x : betweenness){
        outfile << x << ' ';
    }

    outfile << '\n';
    outfile.close();
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}