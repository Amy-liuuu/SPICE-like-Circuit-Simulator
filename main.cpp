#include "parser.h"
#include "stamp.h"
#include "solver.h"
#include <ctime>

// time_t start;

int main(int argc, char* argv[]) {
    // start = clock();

    Data data;
    Matrix matrix;
    Parser parser;
    Stamp stamp;
    Solver solver;

    if (argc != 3) {
        std::cerr << "Usage: ./Project2 [input] [output]" << std::endl;
        exit(1);
    }
    std::cout << "\n/----- Case: " << argv[1] << " -----/\n";

    parser.parser(argv[1], data);
    // parser.check(data);
    stamp.stamp(data, matrix);
    // stamp.output(argv[2], argv[3], argv[4], matrix);
    solver.solver(matrix);
    solver.output(argv[2], matrix);
    // time_t end = clock();
    // float t_used = (float)(end - start) / CLOCKS_PER_SEC;
    // std::cout << "\n>> Running Time: " << t_used << " seconds.\n";

    return 0;
}
