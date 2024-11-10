#include <bits/stdc++.h>
#include "../algoritmos_competicao/betweenness.cpp"
#include "../algoritmos_competicao/closeness.cpp"
#include "../algoritmos_competicao/eigenvector.cpp"
#include "../algoritmos_competicao/maxdegree.cpp"
#include "../algoritmos_competicao/pageranking.cpp"
#include "../algoritmos_competicao/pagerankingrev.cpp"
#include "../algoritmos_competicao/degree_discount.cpp"
#include "../algoritmos_competicao/random_choice.cpp"

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;
struct alg
{
    function<vi(const graph &, int, const vi &)> fun;
    string name;
};

const double P = 0.2;

pair<vi, vi> simulate(const graph &g, const vi &initialInfected1, const vi &initialInfected2, int steps, bool save = false, string save_path = "results.csv")
{
    vi influenced1 = initialInfected1;
    vi influenced2 = initialInfected2;
    vector<bool> visited(g.size(), false);

    ofstream outfile(save_path);
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
            for (int neighbor : g[node])
                if (!visited[neighbor] && dis(gen) < P)
                    new_infected1.insert(neighbor);

        // Propagar infecção para o algoritmo 2
        for (int node : influenced2)
            for (int neighbor : g[node])
                if (!visited[neighbor] && dis(gen) < P)
                    new_infected2.insert(neighbor);

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
             alg algorithm1,
             alg algorithm2,
             int steps, int K, bool alternate = false)
{
    if (!alternate)
    { // Simulação normal: escolha independente
        vi S;
        vi result1 = algorithm1.fun(g, K, S);
        vi result2 = algorithm2.fun(g, K, S);

        sort(result1.begin(), result1.end());
        sort(result2.begin(), result2.end());

        // cout << "K: " << K << ' ' << result1.size() << endl;
        // cout << "Initial choice\n";
        // cout << "1: ";
        // for (int x : result1)
        //     cout << x << ' ';
        // cout << endl;
        // cout << "2: ";
        // for (int x : result2)
        //     cout << x << ' ';
        // cout << endl;

        vi intersection;
        set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), back_inserter(intersection));

        // Remover elementos da interseção de result1 e result2
        for (int v : intersection)
        {
            result1.erase(remove(result1.begin(), result1.end(), v), result1.end());
            result2.erase(remove(result2.begin(), result2.end(), v), result2.end());
        }

        // cout << "After removal of intersection\n";
        // cout << "1, " << result1.size() << ": ";
        // for (int x : result1)
        //     cout << x << ' ';
        // cout << endl;
        // cout << "2, " << result2.size() << ": ";
        // for (int x : result2)
        //     cout << x << ' ';
        // cout << endl;

        for (int x : result1)
            for (int y : result2)
                if (x == y)
                    assert(false);
        auto [influenced1, influenced2] = simulate(g, result1, result2, steps, true, algorithm1.name + "#" + algorithm2.name + ".csv");

        // if (influenced1.size() > influenced2.size())
        //     cout << "O algoritmo 1 ganhou com " << influenced1.size() << " nós influenciados." << endl;
        // else if (influenced1.size() < influenced2.size())
        //     cout << "O algoritmo 2 ganhou com " << influenced2.size() << " nós influenciados." << endl;
        // else
        //     cout << "Houve um empate, os algoritmos influenciaram " << influenced1.size() << " nós cada." << endl;
        cout << "O algoritmo " << algorithm1.name << " influenciou " << influenced1.size() << " nós." << endl;
        cout << "O algoritmo " << algorithm2.name << " influenciou " << influenced2.size() << " nós." << endl;
    }
    else
    { // Tipo 2: escolha alternada
        vi S1, S2;
        vi result1, result2;
        for (int i = 0; i < K; ++i)
        {
            result1 = algorithm1.fun(g, 1, S1);
            if (!result1.empty())
                S2.push_back(result1[0]);
            result2 = algorithm2.fun(g, 1, S2);
            if (!result2.empty())
                S1.push_back(result2[0]);
        }
        auto [influenced1, influenced2] = simulate(g, S1, S2, steps);
        cout << "O algoritmo 1 influenciou " << influenced1.size() << " nós." << endl;
        cout << "O algoritmo 2 influenciou " << influenced2.size() << " nós." << endl;
    }
}

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

    graph g = read_graph("../redes/15.txt");
    // show_graph(g);

    vector<alg> algorithms = {
        {betweenness, "betweenness"},
        {closeness, "closeness"},
        {eigenvector, "eigenvector"},
        {maxdegree, "maxdegree"},
        {pageranking, "pageranking"},
        {pagerankingrev, "pagerankingrev"},
        {degree_discount, "degree_discount"},
        {random_choice, "random_choice"}};

    int steps = 5, initial_infected_count = 3;
    // compete(g, algorithms[1], algorithms[6], steps, initial_infected_count, false);

    int num_algs = algorithms.size();

    for (int i = 0; i < num_algs; ++i)
    {
        for (int j = i + 1; j < num_algs; ++j)
        {
            cout << algorithms[i].name << " vs. " << algorithms[j].name << endl;
            compete(g, algorithms[i], algorithms[j], steps, initial_infected_count, false);
            cout << "\n";
        }
    }
    return 0;
}