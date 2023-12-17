#include <iostream>
#include <list>

#ifndef GRAPH_HPP
#define GRAPH_HPP
class Vertex {
  public:
    int x, y, z;
    Vertex(int x, int y, int z);
    double operator-(const Vertex& right);

    friend std::ostream& operator<<(std::ostream& out, Vertex& v);
};

template <typename T>
class Array3D {
  private:
    T* data;

    int map_indexes(int x, int y, int z) {
        return x + y * side + z * side * side;
    }
  public:
    size_t side;

    Array3D(size_t side) {
        this->side = side;
        data = new T[side*side*side];
    }

    void init(T value) {
        for (int i = 0; i < side * side * side; i++) {
            data[i] = value;
        }
    }

    T& operator[](Vertex v) {
        return data[map_indexes(v.x, v.y, v.z)];
    }

    T& operator[](Vertex* v) {
        return data[map_indexes(v->x, v->y, v->z)];
    }
};

using Graph = Array3D<std::list<Vertex*>>;

Graph init_graph(size_t side);

#endif
