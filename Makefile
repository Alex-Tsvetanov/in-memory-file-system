all: build run

build:
	g++ -std=c++17 -o main.exe main.cpp -I.

run:
	./main.exe
