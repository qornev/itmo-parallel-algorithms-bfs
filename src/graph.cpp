#include <iostream>
#include "graph.hpp"

Vertex::Vertex(int x, int y, int z) : x(x), y(y), z(z) {}

double Vertex::operator-(const Vertex& u) {
    double x_diff = 1.0 * pow(x - u.x, 2);
    double y_diff = 1.0 * pow(y - u.y, 2);
    double z_diff = 1.0 * pow(z - u.z, 2);
    return sqrt(x_diff + y_diff + z_diff);
}

std::ostream& operator<<(std::ostream& out, Vertex& v) {
    std::cout << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return out;
}

Graph init_graph(size_t side) {
    Array3D<Vertex*> vertices(side);
    for (int i = 0; i < side; i++)
        for (int j = 0; j < side; j++)
            for (int k = 0; k < side; k++) {
                Vertex v(i, j, k);
                vertices[v] = new Vertex(i, j, k);
            }

    Graph graph(side);
    for (int i = 0; i < side; i++)
        for (int j = 0; j < side; j++)
            for (int k = 0; k < side; k++) {
                Vertex v(i, j, k);
                if (i + 1 < side) {
                    Vertex u(i + 1, j, k);
                    graph[v].push_back(vertices[u]);
                }
                if (j + 1 < side) {
                    Vertex u(i, j + 1, k);
                    graph[v].push_back(vertices[u]);
                }
                if (k + 1 < side) {
                    Vertex u(i, j, k + 1);
                    graph[v].push_back(vertices[u]);
                }
            }
    return graph;
}
