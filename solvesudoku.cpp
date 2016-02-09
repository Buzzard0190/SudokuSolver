#include <string>
#include <iostream>
#include <algorithm>
#include "SudokuGrid.h"

using namespace std;

// XXX

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
    
    
    // XXX
	
    SudokuGrid grid(puzzle);
    grid.printPuzzle();
    
    std::cout << "\n\n";

    grid.deduce();
    grid.solveSudoku();
    
    grid.printPuzzle();
    
    return 0;
}
