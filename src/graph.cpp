#include <iostream>
#include "graph.hpp"

Vertex::Vertex() : x(0), y(0), z(0) {}

Vertex::Vertex(unsigned short x, unsigned short y, unsigned short z) : x(x), y(y), z(z) {}

double Vertex::operator-(const Vertex& u) {
    double x_diff = 1.0 * pow(x - u.x, 2);
    double y_diff = 1.0 * pow(y - u.y, 2);
    double z_diff = 1.0 * pow(z - u.z, 2);
    return sqrt(x_diff + y_diff + z_diff);
}

size_t Vertex::flatten_index(size_t side) {
    return this->x + this->y * side + this->z * side * side;
}

std::ostream& operator<<(std::ostream& out, Vertex& v) {
    std::cout << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return out;
}

Graph init_graph(size_t side) {
    Graph graph(side);
    for (int i = 0; i < side; i++)
        for (int j = 0; j < side; j++)
            for (int k = 0; k < side; k++) {
                Vertex v(i, j, k);
                if (i + 1 < side) {
                    Vertex u(i + 1, j, k);
                    graph.add_edge(v, u);
                }
                if (j + 1 < side) {
                    Vertex u(i, j + 1, k);
                    graph.add_edge(v, u);
                }
                if (k + 1 < side) {
                    Vertex u(i, j, k + 1);
                    graph.add_edge(v, u);
                }
            }
    return graph;
}

