#include <bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(), x.end()

using namespace std;

typedef vector<int> vi;
typedef vector<vi> graph;

// Recebe grafo, lê lista de pageranking reverso e retorna os vértices escolhidos
vi pagerankingrev(graph G, int k, vi S)
{
    ifstream file("./../algoritmos/main-list/pagerankingrev_list.txt");
    int a;
    vi ans;
    while (file >> a)
    {
        auto it = find(all(S), a);
        if (it == S.end())
            ans.pb(a);
        if (ans.size() == k)
            break;
    }

    return ans;
}
