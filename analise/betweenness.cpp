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
vector<ld> edge_betweenness;
map<pair<int, int>, int> mapa;
int n, m, dif_m;

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
    
    vi edge_qtdd(dif_m);

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
                edge_qtdd[mapa[{x, y}]] += qtdd[x];
                qtdd[y] += qtdd[x];
                pai[y].push_back(x);
            }
        }
    }

    vector<ld> delta(G.size());
    vector<ld> delta_edge(dif_m);

    // O(m)
    while (!ordem.empty())
    {
        int x = ordem.top();
        ordem.pop();
        for (int y : pai[x])
        {
            delta[y] += ((ld)qtdd[y] / qtdd[x]) * (1 + delta[x]);
            delta_edge[mapa[{y, x}]] += ((ld)qtdd[y] / qtdd[x]) * (1 + delta[x]);
        }
        if (x != a)
        {
            betweenness[x] += delta[x];
        }
    }
    for(int i = 0; i < dif_m; i++){
        edge_betweenness[i] += delta_edge[i];
    }
}

void solve()
{
    cin >> n >> m;

    betweenness.resize(n);

    graph G(n);
    dif_m = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        if(mapa.find({a, b}) == mapa.end()){
            mapa[{a, b}] = dif_m;
            dif_m ++;
        }
    }
    edge_betweenness.resize(dif_m);

    for (int i = 0; i < G.size(); i++)
    {
        bfs(i, G);
    }

    ofstream outfile("edge_betweenness");

    for (auto x : edge_betweenness){
        outfile << x << ' ';
    }

    outfile << '\n';
    outfile.close();

    ofstream outfile2("node_betweenness");

    for (auto x : betweenness){
        outfile2 << x << ' ';
    }

    outfile2 << '\n';
    outfile2.close();
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}