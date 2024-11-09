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
    unordered_set<int> s, si, sd;
    for(int v : G[a]) s.insert(v);
    for(int v : Gi[a]) si.insert(v);
    for(int v : G[a]) {
        if(si.find(v) != si.end() && s.find(v) != si.end()){
            s.erase(v);
            si.erase(v);
            sd.insert(v);
        }
    }

    for(int v : s){
        // remove duplicatas
        unordered_set<int> sv;
        for(int u : G[v]) sv.insert(u);

        for(int u : sv){
            if(s.find(u) != s.end()) tot++;
            if(si.find(u) != si.end()) tot++;
            if(sd.find(u) != sd.end()) tot+=2;
        }
    }
    for(int v : si){
        // remove duplicatas
        unordered_set<int> sv;
        for(int u : G[v]) sv.insert(u);

        for(int u : sv){
            if(s.find(u) != s.end()) tot++;
            if(si.find(u) != si.end()) tot++;
            if(sd.find(u) != sd.end()) tot+=2;
        }
    }
    for(int v : sd){
        // remove duplicatas
        unordered_set<int> sv;
        for(int u : G[v]) sv.insert(u);

        for(int u : sv){
            if(s.find(u) != s.end()) tot+=2;
            if(si.find(u) != si.end()) tot+=2;
            if(sd.find(u) != sd.end()) tot+=4;
        }
    }

    ll S = s.size() + si.size() + 2 * sd.size();
    ll Sd = sd.size();

    if(S * (S - 1) + 4 * Sd * (Sd - 1) + 4 * Sd * S <= 0) return 0;
    return (ld)tot / (S * (S - 1) - 2 * Sd);
}
 
void solve(){
    cin >> n >> m;
    G.resize(n);
    Gi.resize(n);
    clust.resize(n);

    set<pii> arestas;

    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        if(arestas.find({a, b}) == arestas.end()){
            arestas.insert({a, b});
            G[a].push_back(b);
            Gi[b].push_back(a);
        }
    }

    ld mean = 0;
    for(int i = 0; i < n; i++) {
        clust[i] = clustering(i);
        mean += clust[i];
    }

    mean /= n;

    sort(clust.begin(), clust.end());
    ofstream outfile("clustering");
    for(int i = 0; i < n; i++) outfile << clust[i] << ' ';
    outfile <<'\n';
    outfile.close();

    cout << mean << '\n';
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}