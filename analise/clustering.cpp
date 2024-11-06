#include <bits/stdc++.h> 
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;

int n, m;
vi vis;
graph G;
vector<ld> clust;

// tem que pegar arestas bidirecionais?
ld clustering(int a) {
    ll tot = 0;

    // remove duplicatas
    unordered_set<int> s;
    for(int v : G[a]) s.insert(v);

    for(int v : s){
        // remove duplicatas
        unordered_set<int> sv;
        for(int u : G[v]) sv.insert(u);

        for(int u : sv){
            if(s.find(u) != s.end()) tot++;
        }
    }

    int k = s.size();

    if(k <= 1) return 0;
    return (ld)tot / ((ll)k * (k - 1));
}
 
void solve(){
    cin >> n >> m;
    G.resize(n);
    clust.resize(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
    }
    for(int i = 0; i < n; i++) sort(G[i].begin(), G[i].end());

    for(int i = 0; i < n; i++) clust[i] = clustering(i);

    for(int i = 0; i < n; i++) cout << clust[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}