all: build run run_tests

build: build_gcc build_gcc_test build_clang build_clang_test

build_gcc:
	g++ -std=c++17 -o main.exe main.cpp -I.
build_gcc_test:
	g++ -std=c++17 -o fs_tests.exe tests/fs_tests.cpp -I.
build_clang:
	clang++ -std=c++17 -o main.exe main.cpp -I.
build_clang_test:
	clang++ -std=c++17 -o fs_tests.exe tests/fs_tests.cpp -I.

run:
	./main.exe

run_tests:
	./fs_tests.exe
