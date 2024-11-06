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
graph G, Gi;
vector<ld> clust;

ld clustering(int a) {
    ll tot = 0;

    // remove duplicatas
    unordered_set<int> s;
    for(int v : G[a]) s.insert(v);
    for(int v : Gi[a]) s.insert(v);

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
    Gi.resize(n);
    clust.resize(n);

    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        Gi[b].push_back(a);
    }

    ld mean = 0;
    for(int i = 0; i < n; i++) {
        clust[i] = clustering(i);
        mean += clust[i];
    }

    mean /= n;

    ofstream outfile("clustering");
    for(int i = 0; i < n; i++) outfile << clust[i] << ' ';
    outfile <<'\n';
    outfile.close();

    cout << mean << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}