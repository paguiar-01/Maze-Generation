#include <vector>
#include <utility>
#include <sstream>
#include <fstream>

class Cell{
	private:
		int row;
		int col;
		int seed;
		std::vector<std::vector<int>> grid;
		std::vector<std::pair<int,int>> A;
		std::vector<std::vector<bool>> visited;
		
	public:
		Cell(int r, int c, int s);
		void getNeighbors (int i, int j, std::vector<std::pair<int,int>> &neighbors, std::vector<std::vector<bool>> &visited);
		void removeWall (std::pair<int,int> neighbors, std::pair<int,int> A);
		void path ();
		void printGrid (std::string file_name);
};