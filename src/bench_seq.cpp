#include <iostream>
#include <chrono>
#include "graph.hpp"
#include "bfs.hpp"
using namespace std;
using namespace std::chrono;

#define SIZE 200
#define N_REPEATS 5

int main() {
    cout << "Start initializing graph with sides " << SIZE << endl;
    Graph graph = init_graph(SIZE);
    cout << "Graph initialization finished" << endl;

    for (int i = 0; i < N_REPEATS; i++) {
        cout << i + 1 << " attempt" << endl;
        auto start_time = high_resolution_clock::now();
        Vertex* start = new Vertex(0, 0, 0);
        cout << fixed << "Distance: " << seq_bfs(graph, start) << endl;
        auto stop_time = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop_time - start_time);
        cout << "Time: " << duration.count() << " millisec" << endl;
    }
    return 0;
}
