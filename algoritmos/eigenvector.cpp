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
graph G;
vector<ld> eigenvector;

vector<ld> norm(vector<ld> v)
{
    ld sum = 0;
    for (auto x : v)
        sum += x * x;
    sum = sqrtl(sum);

    for (int i = 0; i < v.size(); i++)
    {
        v[i] /= sum;
    }

    return v;
}

// Von Mises
void vonmises(graph G)
{
    vector<ld> aux(G.size());

    // O (m)
    for (int i = 0; i < G.size(); i++)
    {
        for (auto x : G[i])
        {
            aux[i] += eigenvector[x];
        }
    }

    eigenvector = aux;
    eigenvector = norm(eigenvector);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    eigenvector.resize(n);
    eigenvector[0] = 1;

    graph G(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    int times = 100;
    for (int i = 0; i < times; i++)
    {
        vonmises(G);
    }

    vector<pair<ld, int>> aux(G.size());

    for (int i = 0; i < G.size(); i++)
    {
        aux[i].second = i;
        aux[i].first = eigenvector[i];
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