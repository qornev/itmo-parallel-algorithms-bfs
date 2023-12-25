#include <iostream>
#include <chrono>
#include "graph.hpp"
#include "bfs.hpp"
using namespace std;
using namespace std::chrono;

#define SIZE 500
#define N_REPEATS 5

int main() {
    cout << "Start initializing graph with sides " << SIZE << endl;
    Graph graph = init_graph(SIZE);
    cout << "Graph initialization finished" << endl << endl;

    Vertex start(0, 0, 0);
    Array3D<bool> visited(SIZE);
    visited.init(false);

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

    return 0;
}

