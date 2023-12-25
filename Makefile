build-seq:
	xcrun /opt/opencilk/bin/clang++ src/bench_seq.cpp src/seq_bfs.cpp src/graph.cpp -o bin/bench_seq -O3 -std=c++11

bench-seq: build-seq
	./bin/bench_seq 500 5 > results/bench_seq.txt

build-par:
	xcrun /opt/opencilk/bin/clang++ src/bench_par.cpp src/par_bfs.cpp src/graph.cpp -o bin/bench_par -O3 -std=c++11 -fopencilk

bench-par: build-par
	CILK_NWORKERS=4 ./bin/bench_par 500 5 > results/bench_par.txt