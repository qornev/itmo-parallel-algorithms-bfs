#include "bfs.hpp"

double seq_bfs(Graph graph, Vertex* start, Array3D<bool>& visited) {
    double distance = 0;
    std::list<Vertex*> queue;

    queue.push_back(start);
    while (!queue.empty()) {
        Vertex* v = queue.front();
        queue.pop_front();
        visited[v] = true;
        for (Vertex* u : graph[v]) {
            if (!visited[u]) {
                queue.push_back(u);
                visited[u] = true;
                distance += *u - *v;
            }
        }
    }
    return distance;
}
