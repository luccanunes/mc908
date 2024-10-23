#include <bits/stdc++.h> 
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;

vector<pii> max_degree(graph G){
    vector<set<int>> H;
    H.resize(G.size());

    for (int i = 0; i < G.size(); i++)
        for(auto x : G[i])
            H[i].insert(x);

    vector<pii> v;
    for (int i = 0; i < H.size(); i++){
        v.pb({H[i].size(), i});
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());

    return v;
}

void solve(){
    int n, m; cin >> n >> m;
    
    graph G(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    
    vector<pii> deg = max_degree(G);

    ofstream file("degree_no_rep_list");
    if (file.is_open()) {
        for(auto x : deg){
            file << x.second << ' ';
        }
        file.close();
    } else {
        cout << "Failed to create the file.\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);	
    solve();
    return 0;
}