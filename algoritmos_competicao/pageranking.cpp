#include <bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(), x.end()

using namespace std;

typedef vector<int> vi;
typedef vector<vi> graph;

// Recebe grafo, lê lista de pageranking e retorna os vértices escolhidos
vi pageranking(graph G, int k, vi S)
{
    ifstream file("./../algoritmos/main-list/pageranking_list.txt");
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