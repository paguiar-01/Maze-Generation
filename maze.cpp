#include "maze.h"
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <fstream>

Cell::Cell(int r, int c, int s){
    this->row = r;
	this->col = c;
	this->seed = s;
	for (int i = 0; i < this->row; i++){
	    this->grid.push_back({});
	    this->visited.push_back({});
	    for(int j = 0; j < this->col; j++){
	        this->grid[i].push_back(15);
	        this->visited[i].push_back(false);
	    }
	}
	this->grid[0][0] = 7;
	this->grid[row-1][col-1] = 11;
}

void Cell::getNeighbors (int i, int j, std::vector<std::pair<int,int>> &neighbors, std::vector<std::vector<bool>> &visited){
    //std::cout << i << " , " << j << " coordinates\n" << col << " columns\n";
    if (i-1 >= 0 && visited[i-1][j] == false){
        //std::cout << i-1;
        neighbors.push_back(std::make_pair(i-1, j));
        //std::cout << " in bounds top\n";
    }
    if (i+1 < this->row && visited[i+1][j] == false){
        neighbors.push_back(std::make_pair(i+1, j));
        //std::cout << "in bounds bottom\n";
    }
    if (j+1 < this->col && visited[i][j+1] == false){
        neighbors.push_back(std::make_pair(i, j+1));
        //std::cout << "in bounds left\n";
    }
    if (j-1 >= 0 && visited[i][j-1] == false){
        neighbors.push_back(std::make_pair(i, j-1));
        //std::cout << "in bounds right\n";
    }
    //std::cout<< "neighbors gotten\n";
    //std::cout << neighbors.size();
}



void Cell::removeWall (std::pair<int,int> neighbors, std::pair<int,int> A){
    if (neighbors.first == (A.first)-1){
        this->grid[A.first][A.second] = grid[A.first][A.second]-8;
        this->grid[neighbors.first][neighbors.second] = grid[neighbors.first][neighbors.second]-4;
        //std::cout << "n/s wall removed\n";
    }
    else if (neighbors.first == (A.first)+1){
        this->grid[A.first][A.second] = grid[A.first][A.second]-4;
        this->grid[neighbors.first][neighbors.second] = grid[neighbors.first][neighbors.second]-8;
        //std::cout << "s/n wall removed\n";
    }
    else if (neighbors.second == (A.second)-1){
        this->grid[A.first][A.second] = grid[A.first][A.second]-1;
        this->grid[neighbors.first][neighbors.second] = grid[neighbors.first][neighbors.second]-2;
        //std::cout << "w/e wall removed\n";
    }
    else if (neighbors.second == (A.second)+1){
        this->grid[A.first][A.second] = grid[A.first][A.second]-2;
        this->grid[neighbors.first][neighbors.second] = grid[neighbors.first][neighbors.second]-1;
        //std::cout << "e/w wall removed\n" << grid[A.first][A.second] << " east wall\n" << grid[neighbors.first][neighbors.second] << " west wall\n";
    }
}

void Cell::path (){
    if (this->col == 1 && this->row == 1){
        this->grid[0][0] = 3;
        return;
    }
    std::srand(this->seed);
    this->visited[0][0] = true;
    this->A.push_back(std::make_pair(0,0));
    //int i = 0;
    //A.size() != 0
    //std::cout << "here\n";
    while (this->A.size() != 0){
        //std::cout << "in\n";
        int idx = this->A.size() -1;
        std::pair<int, int> current = this->A[idx];
        this->A.pop_back();
        std::vector<std::pair<int,int>> neighbors;
        getNeighbors(current.first, current.second, neighbors, this->visited);
        //std::cout << neighbors.size();
        if (neighbors.size() != 0){
            this->A.push_back(current);
            //std::cout << A.size() << " A size\n";
            int neigh = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
            //std::cout << neigh << " seed\n";
            removeWall (neighbors[neigh], A[idx]);
            this->visited[neighbors[neigh].first][neighbors[neigh].second] = true;
            //std::cout << visited[neighbors[neigh].first][neighbors[neigh].second] << " neighbors\n";
            this->A.push_back(std::make_pair(neighbors[neigh].first, neighbors[neigh].second));
            //std::cout << A.size() << " A size2\n";
        }
        //i++;
    }
    //std::cout<<grid[0][0] << " " << grid[0][1];
}

void Cell::printGrid (std::string file_name){
    // Opens the outfile file, prepares it for writing
    std::ofstream output_file(file_name);

    // Loop rows
    for(unsigned int i = 0; i < this->grid.size(); i++){
        // Loop columns
        for(unsigned int j = 0; j < this->grid[i].size(); j++){
            // Output each value and a space
            output_file << this->grid[i][j] << " ";
        }
        // Output a newline character after every row
        output_file << std::endl;
    }
}