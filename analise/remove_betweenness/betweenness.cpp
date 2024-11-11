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
vector<pair<ld, pii>> edge_betweenness;
map<pii, int> mapa;
map<int, pii> unmp;
map<pii, set<int>> marcados;
int n, m, dif_m;

// Brandes
void bfs(int a, graph G, int aux)
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
            marcados[{y, x}].insert(a);
        }
        if (x != a)
        {
            betweenness[x] += aux * delta[x];
        }
    }
    for(int i = 0; i < dif_m; i++){
        edge_betweenness[i].first += aux * delta_edge[i];
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
        if(mapa.find({a, b}) == mapa.end()){
            G[a].push_back(b);
            mapa[{a, b}] = dif_m;
            unmp[dif_m] = {a, b};
            dif_m ++;
        }
    }
    edge_betweenness.resize(dif_m);
    for(int i = 0; i < dif_m; i++){
        edge_betweenness[i].second = unmp[i];
    }

    for (int i = 0; i < G.size(); i++)
    {
        bfs(i, G, +1);
    }

    for(int i = 0; i < dif_m; i++){
        auto x = (*max_element(edge_betweenness.begin(), edge_betweenness.end())).second;
        cout << x.first << ' ' << x.second << endl;
        
        // for(int y = 0; y < G.size(); y++){
        for(auto y : marcados[x]){
            bfs(y, G, -1);
        }

        for(auto it = G[x.first].begin(); it != G[x.first].end(); it++){
            if(*it == x.second) {
                G[x.first].erase(it);
                break;
            }
        }

        // for(int i = 0; i < n; i ++){
        //     cout << i << ": "; 
        //     for(auto k : G[i]) cout << k << ' ';
        //     cout << '\n';
        // }
        // cout << '\n';
        // for(int y = 0; y < n; y++){
        for(auto y : marcados[x]){
            bfs(y, G, +1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}