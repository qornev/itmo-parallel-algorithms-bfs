#include <iostream>
#include <chrono>
#include "graph.hpp"
#include "bfs.hpp"
using namespace std;
using namespace std::chrono;

bool check(Array3D<unsigned short>& distances) {
    for (int i = 0; i < distances.side; i++)
        for (int j = 0; j < distances.side; j++)
            for (int k = 0; k < distances.side; k++) {
                if (distances.at(i, j, k) != (i + j + k))
                    return false;
            }
    return true;
}

int main(int argc, char* argv[]) {
    int side = 500;
    if (argc > 1)
        side = atoi(argv[1]);

    int n_repeats = 1;
    if (argc > 2)
        n_repeats = atoi(argv[2]);

    cout << "Start initializing graph with sides " << side << endl;
    Graph graph(side);
    cout << "Graph initialization finished" << endl << endl;

    Vertex start(0, 0, 0);
    Array3D<bool> visited(side);
    Array3D<size_t> parent(side);
    Array3D<unsigned short> distances(side);

    cout << "Start algorithm bench" << endl;
    for (int i = 0; i < n_repeats; i++) {
        visited.init(false);
        parent.init(SIZE_T_MAX);
        distances.init(0);
        cout << i + 1 << " attempt" << endl;

        auto start_time = high_resolution_clock::now();

        par_bfs(graph, start, visited, parent, distances);

        auto stop_time = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop_time - start_time);
        cout << "Time: " << duration.count() << " millisec" << endl;

        if (check(distances))
            cout << "All distances are correct" << endl << endl;
        else
            cout << "ERROR: Distances are not correct" << endl << endl;
    }
}
