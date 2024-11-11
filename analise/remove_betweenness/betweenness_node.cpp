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
graph G, Gi;
vector<ld> betweenness;
map<pii, int> mapa;
map<int, pii> unmp;
map<int, set<int>> marcados;
int n, m, dif_m;

// Brandes
void bfs(int a, int aux)
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
            marcados[y].insert(a);
        }
        if (x != a)
        {
            betweenness[x] += aux * delta[x];
        }
    }
}

void solve()
{
    cin >> n >> m;

    betweenness.resize(n);

    G.resize(n);
    Gi.resize(n);
    dif_m = 0;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        if(mapa.find({a, b}) == mapa.end()){
            G[a].push_back(b);
            Gi[b].push_back(a);
            mapa[{a, b}] = dif_m;
            unmp[dif_m] = {a, b};
            dif_m ++;
        }
    }

    for (int i = 0; i < G.size(); i++)
    {
        bfs(i, +1);
    }

    for(int i = 0; i < n; i++){
        auto x = max_element(betweenness.begin(), betweenness.end()) - betweenness.begin();
        cout << x << endl;
        
        // for(int y = 0; y < G.size(); y++){
        for(auto y : marcados[x]){
            bfs(y, -1);
        }

        betweenness[x] = -1;

        for(auto k : Gi[x]){
            for(auto it = G[k].begin(); it != G[k].end(); it++){
                if(*it == x) {
                    G[k].erase(it);
                    break;
                }
            }
        }

        G[x].clear();
        Gi[x].clear();

        for(auto y : marcados[x]){
            bfs(y, +1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}