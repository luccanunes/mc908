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

const int maxn = 1e3+5, inf = 2e9, M = 1e9 + 7;
const ll linf = 1e18;
graph G;

vi betweenness(graph G, int k, vi S){
    ifstream file("./../algoritmos/betweenness_list");
    int a;
    vi ans;
    while (file >> a) {
        auto it = find(all(S), a);
        if(it == S.end()) ans.pb(a);
        if(ans.size() == k) break;
    }

    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    return 0;
}