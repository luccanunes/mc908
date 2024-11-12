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
typedef vector<vi> graph;

const int maxn = 1e3 + 5, inf = 2e9, M = 1e9 + 7;
const ll linf = 1e18;


void solve()
{
    int n, m;
    cin >> n >> m;

    vector<pii> arestas(m);
    vi cmp(n);
    for(int i = 0; i < n; i++) cmp[i] = i;
    int tot = n - 1;

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        arestas[i] = {a, b};
    }

    reverse(arestas.begin(), arestas.end());

    vector<pair<pii, pii>> ans;

    for(int i = 0; i < m; i++){
        pii edge = arestas[i];
        int a = edge.first;
        int b = edge.second;
        int c1 = cmp[a], c2 = cmp[b];
        if(c1 != c2){
            tot++;
            int num = 0;
            for(int i = 0; i < n; i++){
                if(cmp[i] == c1 || cmp[i] == c2){
                    cmp[i] = tot;
                    num ++;
                }
            }
            ans.push_back({{c1, c2}, {num, tot}});
        }
    }

    set<int> faltam;

    for(int i = 0; i < n; i++){
        faltam.insert(cmp[i]);
    }

    for(auto it = faltam.begin(); next(it) != faltam.end(); it++){
        tot++;
        if(it == faltam.begin()){
            ans.push_back({{*it, *next(it)}, {n, tot}});
        }
        else{
            ans.push_back({{tot - 1, *next(it)}, {n, tot}});
        }
    }

    cout << ans.size() << '\n';
    for(auto x : ans){
        cout << x.first.first << ' ' << x.first.second << ' '
             << x.second.first << ' ' << x.second.second << '\n';
    }

}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}