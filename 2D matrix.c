#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    if (matrixSize == 0 || matrixColSize[0] == 0) return false;

    int rows = matrixSize;
    int cols = matrixColSize[0];
    
    // Treat the 2D matrix as a virtual 1D array ranging from index 0 to (rows * cols - 1)
    int low = 0;
    int high = (rows * cols) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Map the 1D index back to 2D coordinates (row, col)
        int r = mid / cols;
        int c = mid % cols;
        
        int midValue = matrix[r][c];

        if (midValue == target) {
            return true;
        } else if (midValue < target) {
            low = mid + 1; // Search the right half
        } else {
            high = mid - 1; // Search the left half
        }
    }

    return false;
}
