build-bench-seq:
	xcrun /opt/opencilk/bin/clang++ src/bench_seq.cpp src/seq_bfs.cpp src/graph.cpp -o bin/bench_seq -O3 -std=c++11

bench-seq: build-bench-seq
	./bin/bench_seq

build-bench-par:
	xcrun /opt/opencilk/bin/clang++ src/bench_par.cpp src/par_bfs.cpp src/graph.cpp -o bin/bench_par -O3 -std=c++11 -fopencilk

bench-par: build-bench-par
	CILK_NWORKERS=4 ./bin/bench_par

build-bench-all:
	xcrun /opt/opencilk/bin/clang++ src/bench_all.cpp src/par_bfs.cpp src/seq_bfs.cpp src/graph.cpp -o bin/bench_all -O3 -std=c++11 -fopencilk

bench-all: build-bench-all
	CILK_NWORKERS=4 ./bin/bench_all
