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

vi random_choice(const graph &G, int k, const vi &S)
{
    vi ans;
    set<int> available_nodes, excluded_nodes(S.begin(), S.end());

    // Adicionar todos os vértices que não estão em S ao conjunto de vértices disponíveis
    for (int i = 0; i < G.size(); ++i)
        if (excluded_nodes.find(i) == excluded_nodes.end())
            available_nodes.insert(i);

    // Gerador de números aleatórios
    random_device rd;
    mt19937 gen(rd());

    // Selecionar aleatoriamente K vértices
    while (ans.size() < k && !available_nodes.empty())
    {
        uniform_int_distribution<> dis(0, available_nodes.size() - 1);
        auto it = available_nodes.begin();
        advance(it, dis(gen));
        ans.push_back(*it);
        available_nodes.erase(it);
    }

    return ans;
}