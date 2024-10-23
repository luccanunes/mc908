#include <bits/stdc++.h> 
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;

int n, m;
vi vis;
graph G, Gi;
stack<int> S;
vi comp;

void dfs(int k) {
	vis[k] = 1;
	for (int i = 0; i < (int) G[k].size(); i++)
		if (!vis[G[k][i]]) dfs(G[k][i]);

	S.push(k);
}

void scc(int k, int c) {
	vis[k] = 1;
	comp[k] = c;
	for (int i = 0; i < (int) Gi[k].size(); i++)
		if (!vis[Gi[k][i]]) scc(Gi[k][i], c);
}

void kosaraju() {
	for (int i = 0; i < n; i++) vis[i] = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);

	for (int i = 0; i < n; i++) vis[i] = 0;
	while (S.size()) {
		int u = S.top();
		S.pop();
		if (!vis[u]) scc(u, u);
	}
}
 
void solve(){
    cin >> n >> m;
    G.resize(n);
    Gi.resize(n);
    vis.resize(n);
    comp.resize(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        Gi[b].push_back(a);
    }

    kosaraju();

    int maxi = 0;

    for(int i = 0; i < n; i++) maxi = max(maxi, comp[i]);
    cout << maxi + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}