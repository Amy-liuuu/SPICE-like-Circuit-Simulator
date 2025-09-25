#ifndef _SOLVER_H
#define _SOLVER_H

class Solver {
    public:
        void solver(Matrix& matrix);
        void output(std::string out_filename, Matrix& matrix);
        void show_matrix(Matrix& matrix);
};


#endif
