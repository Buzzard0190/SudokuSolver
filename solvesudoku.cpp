#include <string>
#include <iostream>
#include <algorithm>
#include "SudokuGrid.h"

using namespace std;

// Main code provided by instructor to check input
int main(int argc, char *argv[]) {
    string puzzle;
    cin >> puzzle;
    if (puzzle.length() != 9*9 ||
        !all_of(puzzle.begin(), puzzle.end(),
                [](char ch) {
                    return ch == '.' || ('1' <= ch && ch <= '9');
                })) {
                    cerr << "bogus puzzle!" << endl;
                    exit(1);
                }
    
    
    //calls constructor to build sudoku grid
    SudokuGrid grid(puzzle);
    
    //prints initial puzzle and spacing
    grid.printPuzzle();
    std::cout << "\n\n";

    //deduce values to make the brute force solve quicker
    grid.deduce();
    
    //runs brute force solver and will print error if unable to solve
    if (grid.solveSudoku()) {
        grid.printPuzzle();
    } else {
        std::cout << "Unable to solve puzzle";
    }
    
    return 0;
}
