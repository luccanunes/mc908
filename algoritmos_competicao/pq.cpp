#include <bits/stdc++.h>

using namespace std;

struct PriorityQueue
{
    priority_queue<pair<double, int>> pq;
    unordered_map<int, double> priorities;
    unordered_set<int> in_queue;
    void add_task(int node, double priority)
    {
        pq.push({priority, node});
        priorities[node] = priority;
        in_queue.insert(node);
    }
    pair<int, double> pop_item()
    {
        while (!pq.empty())
        {
            auto [priority, node] = pq.top();
            pq.pop();
            if (in_queue.count(node) && priorities[node] == priority)
            {
                in_queue.erase(node);
                return {node, priority};
            }
        }
        return {-1, 0.0}; // Retorna um valor inválido se a fila estiver vazia
    }
    double get_priority(int node)
    {
        return priorities[node];
    }
};