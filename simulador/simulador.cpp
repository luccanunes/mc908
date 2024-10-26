#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;

vi simulate(const graph &g, const vi &initialInfected, int steps)
{
    vi influenced = initialInfected;
    vector<bool> visited(g.size(), false);
    for (int node : initialInfected)
    {
        visited[node] = true;
    }

    random_device rd;
    mt19937 gen(rd());

    while (steps > 0)
    {
        vector<int> candidates;
        vector<double> probabilities;

        // Collect candidates and their probabilities
        for (int node : influenced)
        {
            for (int neighbor : g[node])
            {
                if (!visited[neighbor])
                {
                    candidates.push_back(neighbor);
                    int infected_neighbors = 0;
                    for (int n : g[neighbor])
                    {
                        if (visited[n])
                        {
                            infected_neighbors++;
                        }
                    }
                    probabilities.push_back(static_cast<double>(infected_neighbors) / g[neighbor].size());
                }
            }
        }

        if (candidates.empty())
        {
            break; // No more candidates to infect
        }

        // Normalize probabilities
        double sum_prob = accumulate(probabilities.begin(), probabilities.end(), 0.0);
        for (double &prob : probabilities)
        {
            prob /= sum_prob;
        }

        // Infect candidates based on probabilities
        for (size_t i = 0; i < candidates.size(); ++i)
        {
            double infection_chance = probabilities[i];
            bernoulli_distribution d(infection_chance);
            if (d(gen))
            {
                int selected = candidates[i];
                influenced.push_back(selected);
                visited[selected] = true;
            }
        }

        --steps;
    }

    return influenced;
}

void compete(const graph &g,
             function<vi(const graph &, int, const vi &)> algorithm1,
             function<vi(const graph &, int, const vi &)> algorithm2,
             int X, int K, bool alternate = false)
{
    if (!alternate) // Simulação normal: escolha independente
    {
        vi S;
        vi result1 = algorithm1(g, K, S);
        vi result2 = algorithm2(g, K, S);

        vi intersection;
        set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), back_inserter(intersection));
        for (int v : intersection)
        {
            result1.erase(remove(result1.begin(), result1.end(), v), result1.end());
            result2.erase(remove(result2.begin(), result2.end(), v), result2.end());
        }

        vi influenced1 = simulate(g, result1, X);
        vi influenced2 = simulate(g, result2, X);

        if (influenced1.size() > influenced2.size())
            cout << "O algoritmo 1 ganhou com " << influenced1.size() << " nós influenciados." << endl;
        else if (influenced1.size() < influenced2.size())
            cout << "O algoritmo 2 ganhou com " << influenced2.size() << " nós influenciados." << endl;
        else
            cout << "Houve um empate, os algoritmos influenciaram " << influenced1.size() << " nós cada." << endl;
    }
    else // Tipo 2: escolha alternada
    {
        vi S1, S2;
        vi result1, result2;
        for (int i = 0; i < K; ++i)
        {
            result1 = algorithm1(g, 1, S1);
            if (!result1.empty())
                S2.push_back(result1[0]);
            result2 = algorithm2(g, 1, S2);
            if (!result2.empty())
                S1.push_back(result2[0]);
        }
        vi influenced1 = simulate(g, S1, X);
        vi influenced2 = simulate(g, S2, X);
        cout << "O algoritmo 1 influenciou " << influenced1.size() << " nós." << endl;
        cout << "O algoritmo 2 influenciou " << influenced2.size() << " nós." << endl;
    }
}

int main()
{
    graph g(5);
    g[0] = {1, 2};
    g[1] = {0, 3};
    g[2] = {0, 4};
    g[3] = {1};
    g[4] = {2};
    // Example algorithms
    auto algorithm1 = [](const graph &g, int K, const vi &S) -> vi
    {
        // Simple algorithm: Select the first K nodes not in S
        vi result;
        for (int i = 0; i < g.size() && result.size() < K; ++i)
        {
            if (find(S.begin(), S.end(), i) == S.end())
            {
                result.push_back(i);
            }
        }
        return result;
    };
    auto algorithm2 = [](const graph &g, int K, const vi &S) -> vi
    {
        // Another simple algorithm: Select the last K nodes not in S
        vi result;

        for (int i = g.size() - 1; i >= 0 && result.size() < K; --i)
        {
            if (find(S.begin(), S.end(), i) == S.end())
            {
                result.push_back(i);
            }
        }
        return result;
    };
    compete(g, algorithm1, algorithm2, 2, 2, false);
    compete(g, algorithm1, algorithm2, 2, 2, true);
    return 0;
}