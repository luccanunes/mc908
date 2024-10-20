#include <bits/stdc++.h> 
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;

vi max_degree(graph G, int k, set<int> S){
    assert(k + S.size() <= G.size());
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

    vi resp;
    int i = 0;
    while(resp.size() != k){
        if(S.find(v[i].second) == S.end()){
            resp.pb(v[i].second);
        }
        i++;
    }

    return resp;
}

// salvar essa lista de graus seria bom

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);	
    return 0;
}