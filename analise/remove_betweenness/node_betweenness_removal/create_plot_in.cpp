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
typedef vector<set<int>> graph;

const int maxn = 1e3 + 5, inf = 2e9, M = 1e9 + 7;
const ll linf = 1e18;
vi vis;
graph G;

void dfs(int k) {
	vis[k] = 1;
	for (auto x : G[k])
		if (!vis[x]) dfs(x);
}

void solve()
{
    int n, m;
    cin >> n >> m;

    // Lê o grafo
    G.resize(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].insert(b);
        G[b].insert(a);
    }

    // Lê vértices em ordem de remoção
    vi vert(n);
    for (int i = 0; i < n; i++){
        cin >> vert[i];
    }
    
    cout << n << '\n';

    for(int i = -1; i < n; i++){
        if(i >= 0){
            int x = vert[i];
            for(auto y : G[x]){
                G[y].erase(x);
            }
            G[x].clear();
        }

        int tot = 0;
        vis.clear();
        vis.resize(n);
        for(int i = 0; i < n; i++){
            if(vis[i] == 0){
                tot++;
                dfs(i);
            }
        }
        cout << i + 1 << ' ' << tot << '\n';
    }

}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}