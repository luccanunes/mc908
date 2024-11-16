#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;

typedef vector<int> vi;
typedef vector<vi> graph;

// Recebe grafo, lê lista de graus e retorna os vértices escolhidos
vi maxdegree(graph G, int k, vi S)
{
    ifstream file("./../algoritmos/main-list/maxdegree_list.txt");
    int a;
    vi ans;
    while (file >> a)
    {
        auto it = find(all(S), a);
        if (it == S.end())
            ans.push_back(a);
        if (ans.size() == k)
            break;
    }

    return ans;
}