#include "pq.h"

void PriorityQueue::add_task(int node, double priority)
{
    pq.push({priority, node});
    priorities[node] = priority;
    in_queue.insert(node);
}

std::pair<int, double> PriorityQueue::pop_item()
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

double PriorityQueue::get_priority(int node)
{
    return priorities[node];
}