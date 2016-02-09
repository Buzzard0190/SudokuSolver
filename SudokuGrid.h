#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <array>
#include <bitset>
#include <string>


class SudokuGrid {
    
private:
    
    //creates cell to be used in grid
    typedef struct cell {
        int value;
        std::bitset<9> pencils;
        bool fixed;
        bool solved;
    }cell;
    
    //creates grid from cells
    std::array<std::array<cell, 9>, 9> grid;
    
    
public:
    
    //Constructor that creates initial puzzle from an input string
    SudokuGrid(std::string s) {
        
        std::cout << s <<"\n";
        
        for (int i = 8; i >= 0; i--) {
            for (int j = 8; j >= 0; j--) {
                int r = s.back()-48;
                s.pop_back();
                if (r < 0) {
                    clearAllPencils(i, j);
                    grid[i][j].fixed = false;
                    grid[i][j].solved = false;
                    grid[i][j].value = 0;
                } else {
                    clearAllPencils(i, j);
                    grid[i][j].fixed = true;
                    grid[i][j].solved = true;
                    grid[i][j].value = r;
                }
            }
        }
    }
    
    //Read number at grid location (row,col). Returns 0 for empty cell.
    int number(int row, int col) const {
        return grid[row][col].value;
    }
    
    //Set number at grid location (row, col)
    void setNumber(int row, int col, int number) {
        
        if (number == 0) {
            grid[row][col].value = number;
            grid[row][col].solved = false;
            return;
        }
        grid[row][col].value = number;
        grid[row][col].solved = true;
    }
    
    //number at grid location (row,col) is original “fixed” value
    bool isFixed(int row, int col) const {
        return grid[row][col].fixed;
    }
    
    //Cell at (row, col) has been marked as solved
    bool isSolved(int row, int col) const {
        return grid[row][col].solved;
    }
    
    //Mark the cell at (row, col) has having been solved
    void setSolved(int row, int col) {
        grid[row][col].solved = true;
    }
    
    //Is value penciled into the cell at (row, col)
    bool isPencilSet(int row, int col, int n) const {
        if (grid[row][col].pencils[n] == 1) {
            return true;
        }
        return false;
    }
    
    //Are any values at cell
    bool anyPencilsSet(int row, int col) const {
        return grid[row][col].pencils.any();
    }
    
    //Set pencil n in cell (row, col)
    void setPencil(int row, int col, int n) {
        grid[row][col].pencils.set(n);
    }
    
    //Set all nine pencil values in cell (row, col)
    void setAllPencils(int row, int col) {
        for (int i = 0; i < 9; i++) {
            grid[row][col].pencils.set(i);
        }
    }
    
    //Clear pencil n in cell
    void clearPencil(int row, int col, int n) {
        grid[row][col].pencils.reset(n-1);
    }
    
    //Clear all pencil values in cell
    void clearAllPencils(int row, int col) {
        grid[row][col].pencils.reset();
    }
    
    //print the puzzle out
    void printPuzzle(){
        
        //cycles through grid to print
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                
                //seperator for row 3-4 and 6-7
                if (j == 3 || j == 6) {
                    std::cout << "| ";
                }
                
                //if the grid doesnt have a value it prints a . otherwise it prints the number
                if (grid[i][j].value == 0) {
                    std::cout << ". ";
                } else {
                    std::cout << grid[i][j].value << " ";
                }
            }
            
            //new line to jump to next row
            std::cout << "\n";
            
            //prints row of seperators between 3-4 and 6-7
            if (i == 2 || i == 5) {
                std::cout << "------+-------+-------\n";
            }
        }
    }
    
    //counts number of time int is penciled into row
    int numPencilsInRow(int row, int n){
        int num = 0;
        for (int i = 0; i < 9; i++) {
            if (isPencilSet(row, i, n)) {
                num++;
            }
        }
        return num;
    }
    
    //counts number of time int is penciled into col
    int numPencilsInColumn(int col, int n){
        int num = 0;
        for (int i = 0; i < 9; i++) {
            if (isPencilSet(i, col, n)) {
                num++;
            }
        }
        return num;
    }
    
    //counts number of time int is penciled into block
    int numPencilsInBlock(int row, int col, int n){
        
        //count for quantity of pencils
        int num = 0;
        
        //sets row and col to the upper left value of block
        if (row <= 2) {
            row = 0;
        } else if (row <= 5){
            row = 3;
        } else {
            row = 6;
        }
        
        if (col <= 2) {
            col = 0;
        } else if (col <= 5){
            col = 3;
        } else {
            col = 6;
        }
        
        for (int i = row; i < row+3; i++) {
            for (int j = col; j < col+3; j++) {
                if (isPencilSet(i, j, n)) {
                    num++;
                }
            }
        }
        return num;
    }
    
    //checks rows, cols, and blocks to see if int already exisits
    bool conflictingNumber(int r, int c, int n){
        
        //checks row for int
        for (int i = 0; i < 9; i++) {
            if (number(r, i) == n) {
                return true;
            }
        }
        
        //checks col for int
        for (int i = 0; i < 9; i++) {
            if (number(i, c) == n) {
                return true;
            }
        }
        
        //sets row and col to the upper left value of block
        if (r <= 2) {
            r = 0;
        } else if (r <= 5){
            r = 3;
        } else {
            r = 6;
        }
        
        if (c <= 2) {
            c = 0;
        } else if (c <= 5){
            c = 3;
        } else {
            c = 6;
        }
        
        //checks block for int
        for (int i = r; i < r+3; i++) {
            for (int j = c; j < c+3; j++) {
                if (number(i, j) == n) {
                    return true;
                }
            }
        }
        return false;
    }
    
    //pencils in values that are possible for each cell
    void autoPencil() {
        for (int r = 0; r < 9; r++){
            for (int c = 0; c < 9; c++){
                if (number(r,c) == 0) {
                    setAllPencils(r,c);
                    for (int n = 1; n <= 9; n++)
                        if (conflictingNumber(r,c,n))
                            clearPencil(r,c,n);
                }
            }
        }
    }
    
    //deduce will go through and check if there are any obvious cells that can be filled in
    void deduce() {
        bool changed;
        do { // repeat until no changes made
            autoPencil();
            changed = false;
            for (int row = 0; row < 9; row++){
                for (int col = 0; col < 9; col++){
                    for (int n = 0; n < 9; n++){
                        if (isPencilSet(row, col, n) && (numPencilsInRow(row, n) == 1 ||  numPencilsInColumn(col, n) == 1 || numPencilsInBlock(row, col, n) == 1)) {
                                clearAllPencils(row, col);
                                setNumber(row,col,(n+1));
                                setSolved(row,col);
                                autoPencil();
                                changed = true;
                                break;
                        }
                    }
                }
            }
        } while(changed);
    }

    //looks for a cell that is empty
    bool findUnassignedLocation(int &row, int &col){
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 9; col++) {
                if (grid[row][col].solved == false) {
                    return true;
                }
            }
        }
        return false;
    }
    
    //brute force solver will attempt to solve puzzle one cell at a time
    bool solveSudoku() {
        
        int row, col;
        
        if (!findUnassignedLocation(row, col)) return true; // puzzle filled, solution found!
        
        for (int num = 1; num <= 9; num++){
            if (!conflictingNumber(row, col, num)) {
                setNumber(row, col, num); // try next number
                if (solveSudoku()) return true;                 // solved!
                setNumber(row, col, 0);   // not solved, clear number
            }
        }
        return false; // not solved, back track
    }
    
    
    
};

#endif // SUDOKUGRID_H
