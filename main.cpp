#include <iostream>
#include <vector>
#include <sstream>
#include "maze.h"

int main(int argc, char** argv){
	int seed = atoi(argv[1]);
    int N = atoi(argv[2]);
    //validate N and M
    int M = atoi(argv[3]);
    std::string fname = argv[4];
	
    Cell cell(N, M, seed);
    cell.path ();
    cell.printGrid (fname);
}