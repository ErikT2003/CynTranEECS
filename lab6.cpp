//
//  main.cpp
//  Lab06EECS348
//
//  Created by Cyn Tran on 3/20/24.
//

#include <iostream>
#include <fstream>
#include <iomanip>

// Problem 1: Function to read matrix data from a file and store it in a 2D array
void readMatrixFromFile(int**& matrix, int& size, const std::string& filename) {
    std::cout << "Problem 1: Open and read file: " << filename << std::endl;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        exit(1);
    }
    file >> size;
    matrix = new int*[size];
    std::cout << "\nProblem 2: printing matrix:"<<std::endl;
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
}

// Problem 2: Function to display a matrix
void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(5) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

// Problem 3: Function to add two matrices and store the result in a third matrix
int** addMatrices(int** matrix1, int** matrix2, int size) {
    int** result = new int*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

// Problem 4: Function for matrix multiplication
int** multiplyMatrices(int** matrix1, int** matrix2, int size) {
    int** result = new int*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Problem 5: Function to subtract one matrix from another and store the result in a third matrix
int** subtractMatrices(int** matrix1, int** matrix2, int size) {
    int** result = new int*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

// Problem 6: Function to update an element of the first matrix
void updateElement(int** matrix, int row, int col, int value, int size) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        matrix[row][col] = value;
    } else {
        std::cerr << "Error: Invalid row or column index." << std::endl;
    }
}

// Problem 7: Function to find and print the max value of the first matrix
int getMaxValue(int** matrix, int size) {
    int maxVal = matrix[0][0];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
            }
        }
    }
    return maxVal;
}

// Function to deallocate memory allocated for the matrix since we use pointer to contruct the array
void deallocateMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Problem 8: Function to transpose and print the first matrix
void transposeMatrix(int** matrix, int size) {
    // Allocate memory for the transposed matrix
    int** transposed = new int*[size];
    for (int i = 0; i < size; ++i) {
        transposed[i] = new int[size];
        if (transposed[i] == nullptr) {
            std::cerr << "Error: Memory allocation failed for transposed matrix." << std::endl;
            // Deallocate memory already allocated for transposed rows
            for (int j = 0; j < i; ++j) {
                delete[] transposed[j];
            }
            // Deallocate memory for transposed matrix array
            delete[] transposed;
            return; // Return from the function
        }
    }

    // Transpose the matrix
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    // Print the transposed matrix
    printMatrix(transposed, size);

    // Deallocate memory for the transposed matrix
    deallocateMatrix(transposed, size);
}


int main() {
    int size;
    int** matrix1;
    int** matrix2;

    // Read matrix data from file
    readMatrixFromFile(matrix1, size, "matrix_input.txt");
    readMatrixFromFile(matrix2, size, "matrix_input.txt");

    // Perform matrix operations
    std::cout << "Matrix 1:" << std::endl;
    printMatrix(matrix1, size);

    std::cout << "\nMatrix 2:" << std::endl;
    printMatrix(matrix2, size);

    int** resultAdd = addMatrices(matrix1, matrix2, size);
    std::cout << "\nProblem 3: Matrix addition:" << std::endl;
    printMatrix(resultAdd, size);

    int** resultMultiply = multiplyMatrices(matrix1, matrix2, size);
    std::cout << "\nProblem 4: Matrix multiplication:" << std::endl;
    printMatrix(resultMultiply, size);

    int** resultSubtract = subtractMatrices(matrix1, matrix2, size);
    std::cout << "\nProblem 5: Matrix subtraction:" << std::endl;
    printMatrix(resultSubtract, size);

    updateElement(matrix1, 0, 0, 10, size);
    std::cout << "\nProblem 6: Updated Matrix 1:" << std::endl;
    printMatrix(matrix1, size);

    std::cout << "\nProblem 7: Max value of Matrix 1: " << getMaxValue(matrix1, size) << std::endl;

    std::cout << "\nProblem 8: Transpose of Matrix 1:" << std::endl;
    transposeMatrix(matrix1, size);

    // Deallocate memory
    deallocateMatrix(matrix1, size);
    deallocateMatrix(matrix2, size);
    deallocateMatrix(resultAdd, size);
    deallocateMatrix(resultMultiply, size);
    deallocateMatrix(resultSubtract, size);

    return 0;
}

