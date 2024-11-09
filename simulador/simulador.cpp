#include <bits/stdc++.h>
#include "../algoritmos_competicao/betweenness.cpp"
#include "../algoritmos_competicao/closeness.cpp"
// #include "../algoritmos_competicao/eigenvector.cpp"
// #include "../algoritmos_competicao/maxdegree.cpp"
// #include "../algoritmos_competicao/maxdegreenorep.cpp"
// #include "../algoritmos_competicao/pageranking.cpp"
// #include "../algoritmos_competicao/pagerankingrev.cpp"

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;

const double P = 0.2;

pair<vi, vi> simulate(const graph &g, const vi &initialInfected1, const vi &initialInfected2, int steps, bool save = false)
{
    vi influenced1 = initialInfected1;
    vi influenced2 = initialInfected2;
    vector<bool> visited(g.size(), false);

    ofstream outfile("results.csv");
    if (save)
        outfile << "step,algorithm,node\n";

    // Marcar vértices iniciais como visitados
    for (int node : initialInfected1)
    {
        visited[node] = true;
        if (save)
            outfile << 0 << ",alg1," << node << "\n";
    }
    for (int node : initialInfected2)
    {
        visited[node] = true;
        if (save)
            outfile << 0 << ",alg2," << node << "\n";
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int step = 1; step <= steps; ++step)
    {
        set<int> new_infected1, new_infected2;

        // Propagar infecção para o algoritmo 1
        for (int node : influenced1)
        {
            for (int neighbor : g[node])
            {
                if (!visited[neighbor] && dis(gen) < P)
                {
                    new_infected1.insert(neighbor);
                }
            }
        }

        // Propagar infecção para o algoritmo 2
        for (int node : influenced2)
        {
            for (int neighbor : g[node])
            {
                if (!visited[neighbor] && dis(gen) < P)
                {
                    new_infected2.insert(neighbor);
                }
            }
        }

        if (new_infected1.empty() && new_infected2.empty())
            break; // Não há mais candidatos para infectar

        // Remover candidatos comuns e marcá-los como visitados
        vector<int> common_candidates;
        set_intersection(new_infected1.begin(), new_infected1.end(), new_infected2.begin(), new_infected2.end(), back_inserter(common_candidates));
        for (int v : common_candidates)
        {
            new_infected1.erase(v);
            new_infected2.erase(v);
            visited[v] = true; // Marcar como visitado para bloquear infecções futuras
        }

        // Atualizar vértices influenciados e visitados
        for (int v : new_infected1)
        {
            influenced1.push_back(v);
            visited[v] = true;
            if (save)
                outfile << step << ",alg1," << v << "\n";
        }
        for (int v : new_infected2)
        {
            influenced2.push_back(v);
            visited[v] = true;
            if (save)
                outfile << step << ",alg2," << v << "\n";
        }
    }
    outfile.close();
    return {influenced1, influenced2};
}

void compete(const graph &g,
             function<vi(const graph &, int, const vi &)> algorithm1,
             function<vi(const graph &, int, const vi &)> algorithm2,
             int steps, int K, bool alternate = false)
{
    if (!alternate)
    { // Simulação normal: escolha independente
        vi S;
        vi result1 = algorithm1(g, K, S);
        vi result2 = algorithm2(g, K, S);

        sort(result1.begin(), result1.end());
        sort(result2.begin(), result2.end());

        // cout << "K: " << K << ' ' << result1.size() << endl;
        cout << "Initial choice\n";
        cout << "1: ";
        for (int x : result1)
            cout << x << ' ';
        cout << endl;
        cout << "2: ";
        for (int x : result2)
            cout << x << ' ';
        cout << endl;

        vi intersection;
        set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), back_inserter(intersection));

        // Remover elementos da interseção de result1 e result2
        for (int v : intersection)
        {
            result1.erase(remove(result1.begin(), result1.end(), v), result1.end());
            result2.erase(remove(result2.begin(), result2.end(), v), result2.end());
        }

        cout << "After removal of intersection\n";
        cout << "1, " << result1.size() << ": ";
        for (int x : result1)
            cout << x << ' ';
        cout << endl;
        cout << "2, " << result2.size() << ": ";
        for (int x : result2)
            cout << x << ' ';
        cout << endl;

        for (int x : result1)
        {
            for (int y : result2)
                if (x == y)
                    assert(false);
        }
        auto [influenced1, influenced2] = simulate(g, result1, result2, steps, true);

        // if (influenced1.size() > influenced2.size())
        //     cout << "O algoritmo 1 ganhou com " << influenced1.size() << " nós influenciados." << endl;
        // else if (influenced1.size() < influenced2.size())
        //     cout << "O algoritmo 2 ganhou com " << influenced2.size() << " nós influenciados." << endl;
        // else
        //     cout << "Houve um empate, os algoritmos influenciaram " << influenced1.size() << " nós cada." << endl;
        cout << "O algoritmo 1 influenciou " << influenced1.size() << " nós." << endl;
        cout << "O algoritmo 2 influenciou " << influenced2.size() << " nós." << endl;
    }
    else
    { // Tipo 2: escolha alternada
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
        auto [influenced1, influenced2] = simulate(g, S1, S2, steps);
        cout << "O algoritmo 1 influenciou " << influenced1.size() << " nós." << endl;
        cout << "O algoritmo 2 influenciou " << influenced2.size() << " nós." << endl;
    }
}

// Função para ler o grafo de um arquivo de texto
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<vector<int>> graph;

graph read_graph(const string &filename)
{
    ifstream infile(filename);
    graph adj_list;
    string line;

    // Ler a primeira linha para obter o número de vértices e arestas
    if (getline(infile, line))
    {
        istringstream iss(line);
        int num_vertices, num_edges;
        if (!(iss >> num_vertices >> num_edges))
        {
            cerr << "Erro ao ler o número de vértices e arestas" << endl;
            return adj_list;
        }

        // Redimensionar a lista de adjacência para acomodar todos os vértices
        adj_list.resize(num_vertices);

        // Ler as arestas
        while (getline(infile, line))
        {
            istringstream iss(line);
            int u, v;
            if (!(iss >> u >> v))
            {
                cerr << "Erro ao ler uma aresta" << endl;
                break;
            }
            adj_list[u].push_back(v);
        }
    }

    return adj_list;
}

void show_graph(const graph &adj_list)
{
    for (size_t i = 0; i < adj_list.size(); ++i)
    {
        cout << "Node " << i << ":";
        for (int neighbor : adj_list[i])
        {
            cout << " " << neighbor;
        }
        cout << endl;
    }
}

int main()
{
    // graph g(5);
    // g[0] = {1, 2};
    // g[1] = {0, 3};
    // g[2] = {0, 4};
    // g[3] = {1};
    // g[4] = {2};

    graph g = read_graph("../redes/533.txt");
    // show_graph(g);

    compete(g, betweenness, closeness, 10, 20, false);

    // show_graph(g);

    // Example algorithms
    // auto algorithm1 = [](const graph &g, int K, const vi &S) -> vi
    // {
    //     // Simple algorithm: Select the first K nodes not in S
    //     vi result;
    //     for (int i = 0; i < g.size() && result.size() < K; ++i)
    //     {
    //         if (find(S.begin(), S.end(), i) == S.end())
    //         {
    //             result.push_back(i);
    //         }
    //     }
    //     return result;
    // };
    // auto algorithm2 = [](const graph &g, int K, const vi &S) -> vi
    // {
    //     // Another simple algorithm: Select the last K nodes not in S
    //     vi result;

    //     for (int i = g.size() - 1; i >= 0 && result.size() < K; --i)
    //     {
    //         if (find(S.begin(), S.end(), i) == S.end())
    //         {
    //             result.push_back(i);
    //         }
    //     }
    //     return result;
    // };
    // compete(g, algorithm1, algorithm2, 300, 70, false);
    // compete(g, algorithm1, algorithm2, 2, 2, true);
    return 0;
}