#include <iostream>
#include <chrono>
#include "graph.hpp"
#include "bfs.hpp"
using namespace std;
using namespace std::chrono;

#define SIZE 301
#define N_REPEATS 5

int main() {
    cout << "Start initializing graph with sides " << SIZE << endl;
    Graph graph = init_graph(SIZE);
    cout << "Graph initialization finished" << endl << endl;

    Vertex* start = new Vertex(0, 0, 0);
    Array3D<bool> visited(SIZE);
    visited.init(false);
    Array3D<Vertex*> parent(SIZE);
    parent.init(nullptr);

    cout << "Start sequential algorithm bench" << endl;
    for (int i = 0; i < N_REPEATS; i++) {
        cout << i + 1 << " attempt" << endl;

        auto start_time = high_resolution_clock::now();

        double distance = seq_bfs(graph, start, visited);

        auto stop_time = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop_time - start_time);

        cout << fixed << "Distance: " << distance << endl;
        cout << "Time: " << duration.count() << " millisec" << endl;
        visited.init(false);
    }
    cout << endl;

    cout << "Start parallel algorithm bench" << endl;
    for (int i = 0; i < N_REPEATS; i++) {
        cout << i + 1 << " attempt" << endl;

        auto start_time = high_resolution_clock::now();

        double distance = par_bfs(graph, start, visited, parent);

        auto stop_time = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop_time - start_time);

        cout << fixed << "Distance: " << distance << endl;
        cout << "Time: " << duration.count() << " millisec" << endl;
        visited.init(false);
        parent.init(nullptr);
    }
    return 0;
}
