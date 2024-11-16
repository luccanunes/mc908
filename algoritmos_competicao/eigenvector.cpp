#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;

typedef vector<int> vi;
typedef vector<vi> graph;

// Recebe grafo, lê lista de eigenvector e retorna os vértices escolhidos
vi eigenvector(graph G, int k, vi S)
{
    ifstream file("./../algoritmos/main-list/eigenvector_list.txt");
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