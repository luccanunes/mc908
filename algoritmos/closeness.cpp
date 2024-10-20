#include <bits/stdc++.h> 
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;

vi bfs(graph G, int a){
    vi check(G.size());
    vi   pai(G.size());
    vi  dist(G.size(), INF);
    queue<int> fila;

    fila.push(a);
    check[a] = 1;
    dist[a] = 1;

    while(!fila.empty()){
        int x = fila.front();
        fila.pop();

        for(auto y : G[x]){
            if(check[y] != 1){
                fila.push(y);
                check[y] = 1;
                dist[y] = dist[x] + 1;
            }
        }
    }

    return dist;
}

vi closeness(graph G, int k, set<int> S){
    assert(k + S.size() <= G.size());
    vector<pair<ld, int>> closeness(G.size());

    for(int i = 0; i < G.size(); i++){
        vi v = bfs(G, i);
        v[i] = 0;
        closeness[i].second = i;
        for(auto x : v){
            closeness[i].first += x;
        }
        closeness[i].first = (G.size() - 1) / closeness[i].first;
    }
    
    sort(closeness.begin(), closeness.end());
    reverse(closeness.begin(), closeness.end());

    vi resp;
    int i = 0;
    while(resp.size() != k){
        if(S.find(closeness[i].second) == S.end()){
            resp.pb(closeness[i].second);
        }
        i++;
    }

    return resp;
}

// salvar essa lista de closeness seria bom

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);	
    return 0;
}