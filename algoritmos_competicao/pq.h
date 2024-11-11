#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <queue>
#include <unordered_map>
#include <unordered_set>

struct PriorityQueue
{
    std::priority_queue<std::pair<double, int>> pq;
    std::unordered_map<int, double> priorities;
    std::unordered_set<int> in_queue;

    void add_task(int node, double priority);
    std::pair<int, double> pop_item();
    double get_priority(int node);
};

#endif // PRIORITY_QUEUE_H