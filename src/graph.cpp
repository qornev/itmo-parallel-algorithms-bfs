#include <iostream>
#include "graph.hpp"

Vertex::Vertex() : x(0), y(0), z(0) {}

Vertex::Vertex(unsigned short x, unsigned short y, unsigned short z) : x(x), y(y), z(z) {}

size_t Vertex::flatten_index(size_t side) {
    return this->x + this->y * side + this->z * side * side;
}

std::ostream& operator<<(std::ostream& out, Vertex& v) {
    std::cout << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return out;
}

size_t Graph::map_indexes(Vertex v) {
    return 3 * (v.flatten_index(side));
}

Graph::Graph(size_t side) {
    this->side = side;
    data = new Vertex[3*side*side*side]{};
    mask = new bool[3*side*side*side]{};

    for (int i = 0; i < side; i++)
        for (int j = 0; j < side; j++)
            for (int k = 0; k < side; k++) {
                Vertex v(i, j, k);
                if (i + 1 < side) {
                    Vertex u(i + 1, j, k);
                    this->add_edge(v, u);
                }
                if (j + 1 < side) {
                    Vertex u(i, j + 1, k);
                    this->add_edge(v, u);
                }
                if (k + 1 < side) {
                    Vertex u(i, j, k + 1);
                    this->add_edge(v, u);
                }
            }
}

std::list<Vertex> Graph::operator[](Vertex v) {
    size_t idx = map_indexes(v);
    std::list<Vertex> adj_vertex;
    for (int i = 0; i < 3; i++) {
        if (mask[idx + i])
            adj_vertex.push_back(data[idx + i]);
    }
    return adj_vertex;
}

void Graph::add_edge(Vertex v, Vertex u) {
    size_t idx = map_indexes(v);
    bool is_inserted = false;
    for (int i = 0; i < 3; i++) {
        if (!mask[idx + i]) {
            data[idx + i] = u;
            mask[idx + i] = true;
            is_inserted = true;
            break;
        }
    }
    if (!is_inserted) throw 20;
}