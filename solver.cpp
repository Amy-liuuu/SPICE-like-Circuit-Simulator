#include "stamp.h"
#include "solver.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>    // std::abs
#include <typeinfo>
#include <iomanip>

void Solver::solver(Matrix& matrix) {
    std::cout << "\n>> Solving...\n";

    int size = matrix.x_matrix.size();
    matrix.solution.assign(size, 0);
    matrix.aug_matrix.assign(size, std::vector<double>(size+1, 0));
    matrix.aug_matrix = matrix.mna_matrix;
    auto rhs_it = matrix.rhs_matrix.begin();
    for (auto& row: matrix.aug_matrix) {
        row.push_back(*rhs_it);
        ++rhs_it;
    }
    // show_matrix(matrix);
    // std::cout << "Rows: " << size << std::endl;

    // ! GE with partial pivoting
    int col_it;
    for (col_it = 0; col_it < size; ++col_it) {
        // ? Interchange pivot row
        // std::cout << col_it << std::endl;
        for (int row_it = size-1; row_it > col_it; --row_it) {
            if (std::abs(matrix.aug_matrix[row_it-1][col_it]) < std::abs(matrix.aug_matrix[row_it][col_it])) {
                // std::cout << "Swap row " << row_it-1 << " and row " << row_it << std::endl;
                double tmp;
                for (int k = 0; k <= size; ++k) {
                    tmp = matrix.aug_matrix[row_it-1][k];
                    matrix.aug_matrix[row_it-1][k] = matrix.aug_matrix[row_it][k];
                    matrix.aug_matrix[row_it][k] = tmp;
                }
            }
            // show_matrix(matrix);
        }
        // show_matrix(matrix);
        // ? Forward Elimination
        // std::cout << "/----- Forward Elimination -----/\n";
        for (int i = col_it+1; i < size; ++i) {
            if (!matrix.aug_matrix[i][col_it]) continue;
            double quotient = matrix.aug_matrix[i][col_it] / matrix.aug_matrix[col_it][col_it];
            for (int j = col_it; j <= size; ++j)
                matrix.aug_matrix[i][j] -= quotient * matrix.aug_matrix[col_it][j];
        }
        // show_matrix(matrix);
    }
    // show_matrix(matrix);

    // ? Backward Elimination
    // std::cout << "/----- Backward Elimination -----/\n";
    for (int i = size-1; i >= 0; --i) {
        double sum = 0;
        // std::cout << "\ni = " << i << std::endl;
        for (int j = i; j < size; ++j) {
            // std::cout << "j = " << j << std::endl;
            // std::cout << std::fixed << std::setprecision(5) << matrix.aug_matrix[i][j] << " * " << matrix.solution[j] << " = " << matrix.aug_matrix[i][j] * matrix.solution[j] << std::endl;
            sum += (matrix.aug_matrix[i][j] * matrix.solution[j]);
            // std::cout << "sum = " << sum << std::endl;
        }
        matrix.solution[i] = (matrix.aug_matrix[i][size] - sum) / matrix.aug_matrix[i][i];
        // std::cout << "sol" << i << " = " << matrix.solution[i] << std::endl;
    }
    // show_matrix(matrix);
}

void Solver::output(std::string out_filename, Matrix& matrix) {
    std::cout << "\n>> Output...\n";

    std::ofstream out_file;
    out_file.open(out_filename, std::ios::out);
    if (!out_file) {
        std::cerr << "Failed to open file: " << out_file << ".\n";
        return;
    }

    out_file << "MNA_matrix =\n";
    for (const auto& mna_row: matrix.mna_matrix) {
        for (const auto& e: mna_row) out_file << std::setw(7) << std::fixed << std::setprecision(3) << e << " ";
        out_file << std::endl;
    }
    
    out_file << "\nMNA_b =\n";
    for (const auto& rhs: matrix.rhs_matrix) out_file << std::setw(6) << std::fixed << std::setprecision(3) << rhs << std::endl;

    out_file << "\nsolution :\n";
    for (int i = 0; i < matrix.x_matrix.size(); ++i)
        out_file << matrix.x_matrix[i] << " = " << std::fixed << std::setprecision(5) << matrix.solution[i] << std::endl;

    out_file.close();
}

void Solver::show_matrix(Matrix& matrix) {
    std::cout << "\n>>> Show matirx...\n";
    for (const auto& row: matrix.aug_matrix) {
        for (const auto& e: row)
            std::cout << std::setw(7) << std::fixed << std::setprecision(3) << e << " ";
    } 
}
