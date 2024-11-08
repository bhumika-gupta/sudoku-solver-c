// ACTUAL CODE (not sudoku_solve.c)

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