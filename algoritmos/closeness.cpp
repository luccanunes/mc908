#include <bits/stdc++.h> 
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;

vi bfs(graph G, int a){
    vi  dist(G.size(), G.size() * 2);
    queue<int> fila;

    fila.push(a);
    dist[a] = 0;

    while(!fila.empty()){
        int x = fila.front();
        fila.pop();

        for(auto y : G[x]){
            if(dist[y] >= G.size() * 2){
                fila.push(y);
                dist[y] = dist[x] + 1;
            }
        }
    }

    return dist;
}

vector<pair<ld, int>> closeness(graph G){
    vector<pair<ld, int>> closeness(G.size());

    for(int i = 0; i < G.size(); i++){
        vi v = bfs(G, i);
        closeness[i].second = i;
        for(auto x : v){
            closeness[i].first += x;
        }
        closeness[i].first = (G.size() - 1) / closeness[i].first;
    }
    
    sort(closeness.begin(), closeness.end());
    reverse(closeness.begin(), closeness.end());

    return closeness;
}
 
void solve(){
    int n, m; cin >> n >> m;
    
    graph G(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
    }
    
    vector<pair<ld, int>> close = closeness(G);

    ofstream file("closeness_list");
    if (file.is_open()) {
        for(auto x : close){
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