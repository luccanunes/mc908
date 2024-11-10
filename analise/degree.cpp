#include <bits/stdc++.h>
#define pb push_back
#define INF 2000000000
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;

graph G, Gi;

void solve()
{
    int n, m;
    cin >> n >> m;

    G.resize(n);
    Gi.resize(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        Gi[b].push_back(a);
    }

    ll saida = 0, entrada = 0;

    ofstream outfile1("degree_out");

    for (int i = 0; i < n; i++){
        outfile1 << G[i].size() << '\n';
        saida += G[i].size();
    }

    outfile1.close();

    ofstream outfile2("degree_in");

    for (int i = 0; i < n; i++){
        outfile2 << Gi[i].size() << '\n';
        entrada += Gi[i].size();
    }

    outfile2.close();
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}