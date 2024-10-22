#include <bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(), x.end()
#define pc __builtin_popcount
#define F first
#define S second
 
using namespace std;
 
typedef long long int  ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;
 
const int maxn = 1e3+5, inf = 2e9, M = 1e9 + 7;
const ll linf = 1e18;
int n, m;
vector<int> ans;
graph G;
vector<vector<pair<int, int>>> dist; 

void bfs(int a, graph G){
    queue<int> fila;
    fila.push(a);
    vi check(G.size());
    check[a] = 1;

    while(!fila.empty()){
        int x = fila.front();
        fila.pop();

        for(auto y : G[x]){
            if(check[y] != 1){
                fila.push(y);
                check[y] = 1;
                dist[a][y].first = dist[a][x].first + 1; 
                dist[a][y].second = 1;
            }
            else if(dist[a][y].first == dist[a][x].first + 1) dist[a][y].second += dist[a][x].second;
        }
    }
}
 
void solve(){
    int n, m; cin >> n >> m;
    graph G(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dist.resize(n);
    for(int i = 0; i < n; i++) dist[i].resize(n);

    for(int i = 0; i < G.size(); i++){
        bfs(i, G);
    }

    for()

}
 
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    //int t; cin >> t; for(int i = 1; i <= t; i++)
    solve();
    return 0;
}