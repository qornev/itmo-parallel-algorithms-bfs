#include "graph.hpp"

#ifndef BFS_HPP
#define BFS_HPP
void seq_bfs(Graph& graph, Vertex& start, Array3D<bool>& visited, Array3D<unsigned short>& distances);

void par_bfs(Graph& graph, Vertex& start, Array3D<bool>& visited, Array3D<size_t>& parent, Array3D<unsigned short>& distances);

#endif