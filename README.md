# Background Info
Your goal in this assignment is to develop a command line tool that will generate a random maze, given some options provided by the user.

# What is a Maze?
A maze is a puzzle, with starting and ending points, in which a player is tasked to find a path connecting a starting point to an ending point. While many algorithms for automatically generating random mazes have been proposed, in this assignment we will implement a **randomized depth-first search** approach that uses **dynamic arrays**. For the context of this assignment, every maze is two-dimensional and it only contains 1 starting and 1 ending cell. There should be exactly one path connecting both cells. The example below illustrates a random maze of dimensions `n=6, m=12`, `n` rows and `m` columns. Note that the starting point always happens at cell `0, 0` and the ending point at `n-1, m-1`.

***Two dimensional maze photo

# Generating a Maze
A data structure for representing a maze in memory may be a two dimensional array in which every cell encodes whether each of the 4 walls is closed or open. We can assume each cell has 4 walls: `north`, `south`, `east`, and `west`. <br />

The algorithm for generating a maze starts with a grid where only 2 walls are removed, `north` for the starting position, and `south` for the ending position, as illustrated in the 6x6 grid below.

The starting point for a 6x6 maze, with the north wall at (0,0) and south wall at (n-1,m-1) removed

A common approach for maze generation involves removing interior walls iteratively. At each iteration a wall is removed to connect two adjacent cells. This iterative process must follow these rules:

Walls to be removed should be selected randomly.
Use std::rand() (read more) to generate random numbers and std::srand() (read more) to provide a seed to the random number generator
There should be exactly one path connecting the starting and ending cells
Every cell must be reachable from the starting cell
The algorithm below should be followed in your implementation. While this is not the most efficient way to solve the problem of maze generation, for our intents and purposes, it’s a good fit. This algorithm can (and should) be implemented with the support of dynamic arrays (std::vector in C++).

We strongly suggest you to trace this algorithm on paper using a small example (e.g. a 4 x 4 grid) until you fully understand how it works, before starting to code.

create empty dynamic array (henceforth referred to as A)
mark cell [0,0] as visited
insert cell [0,0] at the end of A
while A is not empty
    remove last element from A (henceforth referred to as current)
    current's neighbors not visited yet (henceforth referred to as neighbors)
    if neighbors is not empty
        insert current at the end of A
        pick a random neighbor from neighbors (henceforth referred to as neigh)
        remove the wall between current and neigh
        mark neigh as visited
        insert neigh at the end of A
    endif
endwhile
Picking a random neighbor must follow this procedure:

Check the neighbors of a cell in N-S-E-W order and…
…append the neighbors that were not visited yet into an empty vector neighbors
Then use the index idx, as defined below, to pick a random neighbor with neighbors[idx]
idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
Notes:

The u following the 1 in the 1u in the code above signifies that the 1 is unsigned. In C++, numbers are signed by default (meaning they can be either positive or negative) so by declaring it unsigned, we’re saying it cannot be negative (read more).
RAND_MAX is a predefined macro (read more).
Your Task
Your goal in this assignment is to develop a command line tool that will generate a random maze, given some options (described below) provided by the user.

The options for the user will be provided via the following command line arguments:

<seed>  the seed value for the random number generator
<N>     number of rows in the grid N > 0
<M>     number of cols in the grid M > 0
<fname> file name for the output
The seed argument is very important as it initializes the random number generator. If you change the seed, you will generate a different maze. In your code make sure you call this function exactly once before generating the maze:

std::srand(seed);
The last argument will be used to save the generated maze into a text file. Note that you can provide any value as fname. See the example below:

$ ./generator 0 10 10 example.txt
The files that you will generate will be in the format described below.

The description below assumes you have a basic understanding of binary notation, if you don’t or if you need a refresher, please check out this introduction to binary notation.

The file format for saving the maze is a two dimensional array of integers, where each integer is used to represent a cell and its walls. Each integer in the matrix ranges from 0 to 15. The idea behind this representation is that the walls are encoded using 4 bits (a nibble), and the integers are their corresponding values in decimal notation. The figure below illustrates the encoding, with 4 of the possible 16 possibilities. To see the 4-bit representation of all possible numbers (0-15), see this table.

Two-dimensional maze

When saving the grid, the output file must be a text file in which cell values are separated by a single whitespace, and organized in n rows and m columns (the grid dimensions). For example, the image below shows one grid with 5 rows and 5 columns. The text file representation of the grid appears on the left, and the corresponding maze appears on the right. Note how each number maps into a cell encoding its walls. Note that every integer value is separated by a single whitespace.

Two-dimensional maze

A maze visualization will be useful to visualize and understand what your program is doing. You can:

Copy and paste your program’s output onto this maze web visualizer (courtesy of Isaac Chen).
Convert the raw text file into a PDF using the script in this repl.it.
Requirements
Your submission will be tested and graded by an autograder, for this reason it cannot be stressed enough that your program must exactly follow the assignment specifications:

Design a class for the grid, using a header file for your class declaration (see below)
You should receive no warning or error messages upon compilation with the exact following command
 $ g++ -std=c++11 -Wall main.cpp maze.cpp -o generator
Your command line program should use the following arguments (CLAs), in this exact order:
 <seed>  the seed value for the random number generator
 <N>     number of rows in the grid N > 0
 <M>     number of cols in the grid M > 0
 <fname> file name for the output
Use the seed value correctly, as described in the section above.
Generate maze correctly, per the algorithm described in the section above.
BEFORE HANDING IN: Test that your program works by compiling your program with the command in Requirement #2. Successful execution of this command should create an exectuable file named generator, which you should be able to execute using the arguments as outlined in Requirement #4 (example usecase below).

$ ./generator 0 10 10 example.txt

README.md has been created based on the original assignment description. The original assignment can be found at [https://vcc-csc212.github.io/sp21-archive/dd1/#task](https://vcc-csc212.github.io/sp21-archive/dd2/)
