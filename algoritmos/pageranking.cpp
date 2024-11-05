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
const ld ap = 0.85;
graph G;
vector<ld> page;
vector<int> degout;

void update(graph G)
{
    vector<ld> aux(G.size());

    // O (m)
    for (int i = 0; i < G.size(); i++)
    {
        aux[i] = (1 - ap) / G.size();
        for (auto x : G[i])
        {
            aux[i] += ap * page[x] / degout[x];
        }
    }

    page = aux;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    page.resize(n, 1 / (ld)n);
    degout.resize(n);

    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[b].push_back(a);
        degout[a]++;
    }

    int times = 100;
    for (int i = 0; i < times; i++)
        update(G);

    vector<pair<ld, int>> aux(G.size());

    for (int i = 0; i < G.size(); i++)
    {
        aux[i].second = i;
        aux[i].first = page[i];
    }

    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());

    for (auto x : aux)
        cout << x.second << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}