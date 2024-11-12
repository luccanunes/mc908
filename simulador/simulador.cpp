#include <bits/stdc++.h>
#include "../algoritmos_competicao/betweenness.cpp"
#include "../algoritmos_competicao/closeness.cpp"
#include "../algoritmos_competicao/eigenvector.cpp"
#include "../algoritmos_competicao/maxdegree.cpp"
#include "../algoritmos_competicao/pageranking.cpp"
#include "../algoritmos_competicao/pagerankingrev.cpp"
#include "../algoritmos_competicao/degree_discount.cpp"
#include "../algoritmos_competicao/representative_nodes_min.cpp"
#include "../algoritmos_competicao/representative_nodes_sum.cpp"
#include "../algoritmos_competicao/miranda_porto.cpp"
#include "../algoritmos_competicao/prado_nunes.cpp"
#include "../algoritmos_competicao/random_choice.cpp"
#include "../algoritmos_competicao/pq.cpp"

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef vector<unordered_set<int>> graph_set;
struct alg
{
    function<vi(const graph &, int, const vi &)> fun;
    string name;
    bool deterministic = true;
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

    // Converter o grafo para vector<unordered_set<int>>
    graph_set g_set(g.size());
    for (int u = 0; u < g.size(); ++u)
        for (int v : g[u])
            g_set[u].insert(v);

    for (int step = 1; step <= steps; ++step)
    {
        set<int> new_infected1, new_infected2;

        vector<pii> taken_edges;

        // Propagar infecção para o algoritmo 1
        for (int node : influenced1)
            for (int neighbor : g_set[node])
                if (!visited[neighbor] && dis(gen) < P)
                {
                    taken_edges.push_back({node, neighbor});
                    new_infected1.insert(neighbor);
                }

        // Propagar infecção para o algoritmo 2
        for (int node : influenced2)
            for (int neighbor : g_set[node])
                if (!visited[neighbor] && dis(gen) < P)
                {
                    taken_edges.push_back({node, neighbor});
                    new_infected2.insert(neighbor);
                }

        // Remover candidatos comuns e marcá-los como visitados
        vector<int> common_candidates;
        set_intersection(new_infected1.begin(), new_infected1.end(), new_infected2.begin(), new_infected2.end(), back_inserter(common_candidates));
        for (int v : common_candidates)
        {
            new_infected1.erase(v);
            new_infected2.erase(v);
            visited[v] = true; // Marcar como visitado para bloquear infecções futuras
        }

        for (auto [a, b] : taken_edges)
            g_set[a].erase(b);
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

void compete(const graph &g, alg algorithm1, alg algorithm2, int steps, int K, bool alternate, unordered_map<string, int> &wins, unordered_map<string, vector<int>> &infected_counts, unordered_map<string, unordered_map<string, int>> &pair_wins, unordered_map<string, unordered_map<string, pair<vector<int>, vector<int>>>> &pair_infected)
{
    if (!alternate)
    { // Simulação normal: escolha independente
        vi S;
        vi result1 = algorithm1.fun(g, K, S);
        vi result2 = algorithm2.fun(g, K, S);
        sort(result1.begin(), result1.end());
        sort(result2.begin(), result2.end());
        vi intersection;
        set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), back_inserter(intersection));
        // Remover elementos da interseção de result1 e result2
        for (int v : intersection)
        {
            result1.erase(remove(result1.begin(), result1.end(), v), result1.end());

            result2.erase(remove(result2.begin(), result2.end(), v), result2.end());
        }
        for (int x : result1)
            for (int y : result2)
                if (x == y)
                    assert(false);
        auto [influenced1, influenced2] = simulate(g, result1, result2, steps);
        int infected1 = influenced1.size();
        int infected2 = influenced2.size();
        infected_counts[algorithm1.name].push_back(infected1);
        infected_counts[algorithm2.name].push_back(infected2);
        pair_infected[algorithm1.name][algorithm2.name].first.push_back(infected1);
        pair_infected[algorithm1.name][algorithm2.name].second.push_back(infected2);
        if (infected1 > infected2)
        {
            wins[algorithm1.name]++;
            pair_wins[algorithm1.name][algorithm2.name]++;
        }
        else if (infected2 > infected1)
        {
            wins[algorithm2.name]++;
            pair_wins[algorithm2.name][algorithm1.name]++;
        }
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

void compete_for_gif(const graph &g, alg algorithm1, alg algorithm2, int steps, int K, const string &filename)
{
    vi S;
    vi result1 = algorithm1.fun(g, K, S);
    vi result2 = algorithm2.fun(g, K, S);
    sort(result1.begin(), result1.end());
    sort(result2.begin(), result2.end());
    vi intersection;
    set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), back_inserter(intersection));
    // Remover elementos da interseção de result1 e result2
    for (int v : intersection)
    {
        result1.erase(remove(result1.begin(), result1.end(), v), result1.end());
        result2.erase(remove(result2.begin(), result2.end(), v), result2.end());
    }
    for (int x : result1)
        for (int y : result2)
            if (x == y)
                assert(false);
    simulate(g, result1, result2, steps, true, filename);
}

void run_algorithm_isolated(const graph &g, alg algorithm, const vi &initial_infected_sizes, int steps, int num_runs, ofstream &outfile, bool save = false)
{
    for (int k : initial_infected_sizes)
    {
        int total_infected = 0;
        vi S; // Conjunto de vértices proibido
        // cout << "Vou rodar " << algorithm.name << "!" << endl;
        vi result = algorithm.fun(g, k, S);
        // cout << "Rodei " << algorithm.name << "!" << endl;
        auto [influenced_by_alg, _] = simulate(g, result, {}, steps, save);
        total_infected += influenced_by_alg.size();
        for (int i = 1; i < num_runs; ++i)
        {
            if (!algorithm.deterministic)
                result = algorithm.fun(g, k, S);
            // Simular a propagação da influência
            // auto [influenced_by_alg, _] = simulate(g, result, {}, steps, true, algorithm.name + "_" + to_string(k) + "_" + to_string(i) + ".csv");
            auto [influenced_by_alg, _] = simulate(g, result, {}, steps, save);
            total_infected += influenced_by_alg.size();
        }
        double average_infected = static_cast<double>(total_infected) / num_runs;
        outfile << algorithm.name << "," << k << "," << average_infected << "\n";
        // cout << "Algoritmo " << algorithm.name << " infectou em média " << average_infected << " vértices." << endl;
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

void prepare_gifs(alg alg1, alg alg2)
{
    graph g = read_graph("../redes/126.txt");
    compete_for_gif(g, alg1, alg2, 20, 10, alg1.name + "#" + alg2.name + ".csv");
}

int main()
{
    prepare_gifs(
        {degree_discount, "degree_discount"},
        {miranda_porto, "miranda_porto"});

    // graph g = read_graph("../redes/main.txt");
    // // show_graph(g);

    // vector<alg> algorithms = {
    //     // {betweenness, "betweenness"},
    //     {closeness, "closeness"},
    //     {maxdegree, "maxdegree"},
    //     // {pageranking, "pageranking"},
    //     {pagerankingrev, "pagerankingrev"},
    //     // {degree_discount, "degree_discount"},
    //     // {representative_nodes_min, "representative_nodes_min"},
    //     // {representative_nodes_sum, "representative_nodes_sum"},
    //     {miranda_porto, "miranda_porto"},
    //     {prado_nunes, "prado_nunes"},
    //     // {random_choice, "random_choice", false}
    // };

    // // compete(g, algorithms[1], algorithms[6], steps, initial_infected_count, false);

    // int num_algs = algorithms.size();
    // int steps = 20;
    // int num_runs = 3;

    // vi initial_infected_sizes;
    // for (int i = 10; i <= 90; ++i)
    //     initial_infected_sizes.push_back(i);

    // unordered_map<string, int> wins;
    // unordered_map<string, vector<int>> infected_counts;
    // unordered_map<string, unordered_map<string, int>> pair_wins;
    // unordered_map<string, unordered_map<string, pair<vector<int>, vector<int>>>> pair_infected;
    // for (int i = 0; i < num_algs; ++i)
    // {
    //     for (int j = i + 1; j < num_algs; ++j)
    //     {
    //         for (int initial_infected_count : initial_infected_sizes)
    //         {
    //             for (int rep = 0; rep < num_runs; ++rep)
    //             {
    //                 compete(g, algorithms[i], algorithms[j], steps, initial_infected_count, false, wins, infected_counts, pair_wins, pair_infected);
    //             }
    //         }
    //     }
    // }
    // // Salvar resultados gerais em um arquivo CSV
    // ofstream outfile_general("competition_results_general.csv");
    // outfile_general << "Algorithm,Wins,AverageInfected\n";
    // for (const auto &[alg_name, win_count] : wins)
    // {
    //     double average_infected = accumulate(infected_counts[alg_name].begin(), infected_counts[alg_name].end(), 0.0) / infected_counts[alg_name].size();
    //     outfile_general << alg_name << "," << win_count << "," << average_infected << "\n";
    // }
    // outfile_general.close();
    // // Salvar resultados por par de algoritmos em um arquivo CSV
    // ofstream outfile_pairwise("competition_results_pairwise.csv");
    // outfile_pairwise << "Algorithm1,Algorithm2,Wins1,Wins2,AverageInfected1,AverageInfected2\n";
    // for (const auto &[alg1, opponents] : pair_wins)
    // {
    //     for (const auto &[alg2, win_count] : opponents)
    //     {
    //         if (alg1 < alg2)
    //         { // Garantir que cada par seja mostrado apenas uma vez
    //             int wins1 = win_count;
    //             int wins2 = pair_wins[alg2][alg1];
    //             auto [infected1, infected2] = pair_infected[alg1][alg2];
    //             double average_infected1 = accumulate(infected1.begin(), infected1.end(), 0.0) / infected1.size();
    //             double average_infected2 = accumulate(infected2.begin(), infected2.end(), 0.0) / infected2.size();
    //             outfile_pairwise << alg1 << "," << alg2 << "," << wins1 << "," << wins2 << "," << average_infected1 << "," << average_infected2 << "\n";
    //         }
    //     }
    // }
    // outfile_pairwise.close();

    // ofstream outfile("algorithm_curves.csv");
    // outfile << "Algorithm,InitialInfected,AverageInfected\n";

    // run_algorithm_isolated(g, {pageranking, "pageranking"}, {10}, 10, 1, outfile, true);
    // for (alg f : algorithms)
    // {
    //     run_algorithm_isolated(g, f, initial_infected_sizes, steps, 30, outfile);
    // }
    return 0;
}