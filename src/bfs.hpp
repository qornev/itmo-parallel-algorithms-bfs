#include "graph.hpp"

#ifndef BFS_HPP
#define BFS_HPP
double seq_bfs(Graph graph, Vertex* start, Array3D<bool>& visited);

double par_bfs(Graph graph, Vertex* start, Array3D<bool>& visited, Array3D<Vertex*>& parent);

#endif
