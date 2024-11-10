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
