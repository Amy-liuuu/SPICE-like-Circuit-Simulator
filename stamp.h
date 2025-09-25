#ifndef _STAMP_H
#define _STAMP_H
#include "parser.h"
#include <vector>
#include <unordered_set>

class Matrix {
    public:
        std::vector<std::vector<double>> mna_matrix;
        std::vector<std::string> x_matrix;
        std::vector<double> rhs_matrix;
        std::vector<std::vector<double>> aug_matrix;
        std::vector<double> solution;
};

class Stamp {
    public:
        void stamp(Data& data, Matrix& matrix);
        void output(std::string mna_filename, std::string xvec_filename, std::string rhs_filename, Matrix& matrix);
        void show_matrix(Matrix& matrix);
};

#endif
