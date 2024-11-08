# sudoku-solver-c


<ins>Algorithm Overview</ins>

The code implements a backtracking algorithm to solve Sudoku puzzles.

1.  Backtracking:

    -   Backtracking is a systematic algorithmic technique for finding
        solutions to problems that involve making a sequence of choices.
        In the context of Sudoku solving, backtracking is used to
        explore all possible combinations of numbers until a solution is
        found.

    -   the algorithm starts by selecting an empty cell and trying
        different numbers (from 1 to 9) in that cell.

    -   It recursively explores each possibility until it reaches a
        solution or finds that no valid number can be placed in the
        cell.

    -   If it encounters a case where no valid number can be placed, it
        backtracks to the previous cell and tries a different number.

2.  Validity Check:

    -   The validity check ensures that the Sudoku grid follows the
        rules of the game. It verifies that a number can be legally
        placed in a cell without violating any row, column, or 3x3
        subgrid constraints.

    -   This check is crucial to ensure the given solution is correct.
        Without it, the algorithm might place numbers in cells that
        violate Sudoku rules.

<ins>Functions</ins>

1.  `print(int arr[N][N])`

    -   Purpose: This function is responsible for visualizing the Sudoku
        grid. It aids in understanding the state of the puzzle and the
        solution.

    -   It iterates through the 2D array representing the Sudoku grid
        and prints each cell's value.

    -   Printing the grid at different stages of the solving process can
        help in debugging and understanding the algorithm's behaviour.

    -   It improves the user experience by providing a clear
        representation of the Sudoku puzzle and its solution.

2.  `isAllowed(int grid[N][N], int row, int col, int num)`

    -   Purpose: Checks if it's valid to place `num` in the specified
        `row` and `col` of the Sudoku grid.

    -   It checks if `num` is not already present in the same row,
        column, or 3x3 subgrid.By doing this, it prevents violations of
        Sudoku rules.

    -   This function significantly reduces the search space by
        eliminating invalid choices, thereby improving the efficiency of
        the solving algorithm.

3.  `solveSudoku(int grid[N][N], int row, int col)`

    -   Purpose: This is the core function that solves the Sudoku puzzle
        using recursive backtracking to systematically fill in the
        Sudoku grid.

    -   By trying to fill the Sudoku grid starting from the given `row`
        and `col` with different numbers, it efficiently searches for a
        valid solution.

    -   If a number can be placed at the current cell, it recursively
        calls itself for the next cell.

    -   If a solution is not found, it backtracks and tries a different
        number.

    -   The function returns `1` if a solution is found and `0`
        otherwise.

4.  `main()`

    -   Purpose: Serves as the entry point of the program. It
        coordinates the solving process by initializing the puzzle,
        calling the solving function, and printing the results.

    -   It initializes the Sudoku grid with the input puzzle.

    -   Calls the `solveSudoku` function to solve the puzzle.

    -   Prints the original puzzle and its solution if found.

    -   By encapsulating the solving logic within a separate function,
        the `main()` function maintains modularity and readability.


            #include <stdio.h>
            #include <stdlib.h>
            
            #define N 9 // N is the size of the 2D matrix (N*N)
            
            int count;
            
            // "print" is a function we define to print the "grid"
            void print(int arr[N][N]) {
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        printf("%d ", arr[i][j]);
                    }
                    printf("\n");
                }
            }
            
            // checks whether it's legal to assign the num to the given row & col
            int isAllowed(int grid[N][N], int row, int col, int num) {
                
                // checks if the same num is found in the same row, then return 0
                for (int x = 0; x<= 8; x++) {
                    if (grid[row][x] == num) {
                        return 0;
                    }
                }
                
                // checks if the same num is found in the same col, then return 0
                for (int x = 0; x <= 8; x++) {
                    if (grid[x][col] == num) {
                        return 0;
                    }
                }
                
                // check if the same num is found in the particular 3x3 matrix, then return 0
                // these calculations make sure that 'startRow' and 'startCol' 
                // are the indexes of the top-left cell of the 3x3 subgrid containing the
                // current cell
                int startRow = row - row % 3;
                int startCol = col - col % 3;
                
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        // adding 'startRow' to 'i' and 'startCol' to 'j'
                        // adjusts the indices to correspond to the actual indices
                        // within the Sudoku grid
                        if (grid[i + startRow][j + startCol] == num) {
                            return 0;
                        }
                    }
                }
                return 1;
            }
            
            
            int solveSudoku(int grid[N][N], int row, int col) {
                
                count += 1; // the number of times the function was called. 
                
                // check if 8th row & 9th column is reached (0 indexed matrix), 
                // then return 1 to avoid further backtracking as it means the 
                // puzzle is solved
                if (row == N - 1 && col == N) {
                    return 1;
                } 
                if (col == N) {
                    row++;
                    col = 0;
                }
                
                // check if current position of grid already contains value < 0, then 
                // iterate for next column (with the col+1 part)
                if (grid[row][col] > 0) {
                    return solveSudoku(grid, row, col + 1);
                }
                
                for (int num = 1; num <= N; num++) {
                    
                    // check if it's allowed to place the num (1-9) int eh given row, col
                    // then move to the next column
                    if (isAllowed(grid, row, col, num) == 1) {
                        // assigned the num in the current row & col position 
                        // of the grid & asumming the assigned num in the position is correct
                        grid[row][col] = num;
                        
                        // checking for next possibility with next col
                        if (solveSudoku(grid, row, col + 1) == 1) {
                            return 1;
                        }
                        
                        // removing the assigned num, since assumption was wrong,
                        // and then go for next assumption with diff num value
                        grid[row][col] = 0;
                    }  
                }
                return 0;
            }
            
            int main() {
                // This is hard coding to receive the grid
                int grid[N][N] = {
                    {0, 2, 0, 0, 0, 0, 0, 0, 0}, 
                    {0, 0, 0, 6, 0, 0, 0, 0, 3}, 
                    {0, 7, 4, 0, 8, 0, 0, 0, 0}, 
                    {0, 0, 0, 0, 0, 3, 0, 0, 2},
                    {0, 8, 0, 0, 4, 0, 0, 1, 0}, 
                    {6, 0, 0, 5, 0, 0, 0, 0, 0}, 
                    {0, 0, 0, 0, 1, 0, 7, 8, 0}, 
                    {5, 0, 0, 0, 0, 9, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 4, 0}
                };
                
                // For more samples to check your program, google for solved samples, or
                // check https :// sandiway.arizona.edu/sudoku/examples. html
                printf("The input Sudoku puzzle :\n");
                // "print" is a function we define to print the "grid"
                print(grid);
                
                if (solveSudoku(grid, 0, 0) == 1) {
                    // If the puzzle is solved then:
                    printf("Solution found after %d iterations:\n", count);
                    print(grid);
                } else {
                    printf("No solution exists.");
                }
                return 0;
            }
