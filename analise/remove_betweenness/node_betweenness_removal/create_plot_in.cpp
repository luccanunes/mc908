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

    // define componentes
    vi cmp(n);
    for(int i = 0; i < n; i++) cmp[i] = i;
    int tot = n;

    // lê arestas em ordem de remoção
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        arestas[i] = {a, b};
    }

    reverse(arestas.begin(), arestas.end());
    vector<int> ans;

    ans.push_back(tot);
    for(int i = 0; i < m; i++){
        pii edge = arestas[i];
        int a = edge.first;
        int b = edge.second;
        int c1 = cmp[a], c2 = cmp[b];
        if(c1 != c2){
            for(int i = 0; i < n; i++){
                if(cmp[i] == c2){
                    cmp[i] = c1;
                }
            }
            tot--;
        }
        ans.push_back(tot);
    }

    reverse(ans.begin(), ans.end());

    cout << m + 1 << '\n';
    for(int i = 0; i <= m; i++){
        cout << i << ' ' << ans[i] << '\n';
    }

}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}