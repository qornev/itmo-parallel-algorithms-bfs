#include "bfs.hpp"
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

void block_define_parent(Graph& graph, std::list<Vertex>::iterator start, std::list<Vertex>::iterator end, Array3D<bool>& visited, Array3D<size_t>& parent) {
    std::list<Vertex>::iterator it;
    for (it = start; it != end; it++) {
        Vertex v = *it;
        for (Vertex u : graph[v]) {
            if (!visited[u]) {
                parent[u] = v.flatten_index(graph.side);
            }
        }
    }
}

void block_construct_sublist(Graph& graph, std::list<Vertex>::iterator start, std::list<Vertex>::iterator end, Array3D<bool>& visited, Array3D<size_t>& parent, std::list<Vertex>& adj_vertex, Array3D<unsigned short>& distances) {
    std::list<Vertex>::iterator it;
    for (it = start; it != end; it++) {
        Vertex v = *it;
        for (Vertex u : graph[v]) {
            if (parent[u] == v.flatten_index(graph.side)) {
                adj_vertex.push_back(u);
                visited[u] = true;
                distances[u] = distances[v] + 1;
            }
        }
    }
}

void par_bfs(Graph& graph, Vertex& start, Array3D<bool>& visited, Array3D<size_t>& parent, Array3D<unsigned short>& distances) {
    int n_workers = __cilkrts_get_nworkers();
    std::list<Vertex> frontier;

    frontier.push_back(start);
    while (!frontier.empty()) {
        int block_size = 24 * n_workers;
        int n_blocks = ceil(frontier.size() / (1.0 * block_size));

        std::list<Vertex>::iterator it = frontier.begin();
        for (int i = 0; i < n_blocks - 1; i++) {
            cilk_spawn block_define_parent(graph, it, next(it, block_size), visited, parent);
            advance(it, block_size);
        }
        cilk_spawn block_define_parent(graph, it, frontier.end(), visited, parent);
        cilk_sync;

        std::list<Vertex> adj_vertex[n_blocks];
        it = frontier.begin();
        for (int i = 0; i < n_blocks - 1; i++) {
            cilk_spawn block_construct_sublist(graph, it, next(it, block_size), visited, parent, adj_vertex[i], distances);
            advance(it, block_size);
        }
        cilk_spawn block_construct_sublist(graph, it, frontier.end(), visited, parent, adj_vertex[n_blocks - 1], distances);
        cilk_sync;

        std::list<Vertex> restored_frontier = adj_vertex[0];
        for (int i = 1; i < n_blocks; i++) {
            if (adj_vertex[i].size() == 0) continue;
            restored_frontier.splice(restored_frontier.end(), adj_vertex[i]);
        }
        frontier = restored_frontier;
    }
}

