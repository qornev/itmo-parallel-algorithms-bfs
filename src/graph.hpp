#include <iostream>
#include <list>

#ifndef GRAPH_HPP
#define GRAPH_HPP
class Vertex {
  public:
    unsigned short x, y, z;
    Vertex();
    Vertex(unsigned short x, unsigned short y, unsigned short z);
    double operator-(const Vertex& right);
    size_t flatten_index(size_t side);

    friend std::ostream& operator<<(std::ostream& out, Vertex& v);
};

template <typename T>
class Array3D {
  public:
    T* data;
    size_t side;

    Array3D(size_t side) {
        this->side = side;
        data = new T[side*side*side]{};
    }

    void init(T value) {
        for (int i = 0; i < side * side * side; i++) {
            data[i] = value;
        }
    }

    T& operator[](Vertex v) {
        return data[v.flatten_index(side)];
    }

    T& at(int x, int y, int z) {
        Vertex v(x, y, z);
        return data[v.flatten_index(side)];
    }
};

class Graph {
  private:
    Vertex* data;
    bool* mask;

    size_t map_indexes(Vertex v) {
        return 3 * (v.flatten_index(side));
    }
  public:
    size_t side;

    Graph(size_t side) {
        this->side = side;
        data = new Vertex[3*side*side*side]{};
        mask = new bool[3*side*side*side]{};
    }

    std::list<Vertex> operator[](Vertex v) {
        size_t idx = map_indexes(v);
        std::list<Vertex> adj_vertex;
        for (int i = 0; i < 3; i++) {
            if (mask[idx + i])
                adj_vertex.push_back(data[idx + i]);
        }
        return adj_vertex;
    }

    void add_edge(Vertex v, Vertex u) {
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
};

Graph init_graph(size_t side);

#endif

