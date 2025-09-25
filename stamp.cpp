#include "parser.h"
#include "stamp.h"
#include <algorithm>

void Stamp::stamp(Data& data, Matrix& matrix) {
    std::cout << "\n>> Stamping...\n";

    std::unordered_set<int> node;
    int mna_size = 0;
    for (const auto& e: data.elements) {
        if (e.type == "V" || e.type == "v") ++mna_size;
        if (e.from) node.insert(e.from);
        if (e.to) node.insert(e.to);
        if (e.group == 2) ++mna_size;
    }
    mna_size += node.size();
    // std::cout << "mna_size: " << mna_size << std::endl;
    // for (auto n: node) std::cout << "node: " << n << std::endl;

    // ! initial matrix
    matrix.mna_matrix.assign(mna_size, std::vector<double>(mna_size, 0));
    matrix.x_matrix.reserve(mna_size);
    matrix.rhs_matrix.reserve(mna_size);
    // show_matrix(matrix);

    // ! stamping
    for (const auto& e: data.elements) {
		std::string from_str = "";
        std::string to_str = "";
        std::string i_str = "";

        // ! Stamping R
		if (e.type == "R") {
            // std::cout << "\n>>> Stamping R...\n";
            // std::cout << e.type << e.id << " " << e.from << " " << e.to << " " << e.value << " " << e.group << std::endl;

            if (e.group == 1) {
                // * Group 1
                if (e.from) {
                    from_str = "V(n" + std::to_string(e.from) + ")";
                    // std::cout << "From: " << from_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(from_str);
                        matrix.rhs_matrix.push_back(0);
                    }
                }
                if (e.to) {
                    to_str = "V(n" + std::to_string(e.to) + ")";
                    // std::cout << "To: " << to_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(to_str);
                        matrix.rhs_matrix.push_back(0);
                    }
                }
            }
            else {
                // * Group 2
                if (e.from) {
                    from_str = "V(n" + std::to_string(e.from) + ")";
                    // std::cout << "From: " << from_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(from_str);
                        matrix.rhs_matrix.push_back(0);
                    }
                }
                if (e.to) {
                    to_str = "V(n" + std::to_string(e.to) + ")";
                    // std::cout << "To: " << to_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(to_str);
                        matrix.rhs_matrix.push_back(0);
                    }
                }

                i_str = "I(" + e.type + std::to_string(e.id) + ")";
                // std::cout << "Current: " << i_str << std::endl;
                
                auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), i_str);
                if (it == matrix.x_matrix.end()) {
                    matrix.x_matrix.push_back(i_str);
                    matrix.rhs_matrix.push_back(0);
                }
            }
            // Stamp MNA
            auto from_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
            auto to_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
            auto i_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), i_str);
            int from_idx = std::distance(matrix.x_matrix.begin(), from_it);
            int to_idx = std::distance(matrix.x_matrix.begin(), to_it);
            int i_idx = std::distance(matrix.x_matrix.begin(), i_it);

            if (e.group == 1) {
                double value = 1/e.value;
                if (from_idx < matrix.x_matrix.size()) matrix.mna_matrix[from_idx][from_idx] += value;
                if (from_idx < matrix.x_matrix.size() && to_idx < matrix.x_matrix.size()) {
                    matrix.mna_matrix[from_idx][to_idx] -= value;
                    matrix.mna_matrix[to_idx][from_idx] -= value;
                }
                if (to_idx < matrix.x_matrix.size()) matrix.mna_matrix[to_idx][to_idx] += value;
            }
            if (e.group == 2) {
                if (from_idx < matrix.x_matrix.size()) {
                    matrix.mna_matrix[from_idx][i_idx] += 1;
                    matrix.mna_matrix[i_idx][from_idx] += 1;
                }
                if (to_idx < matrix.x_matrix.size()) {
                    matrix.mna_matrix[to_idx][i_idx] -= 1;
                    matrix.mna_matrix[i_idx][to_idx] -= 1;
                }
                matrix.mna_matrix[i_idx][i_idx] -= e.value;
            }

            // show_matrix(matrix);
        }
		// ! Stamping V
        else if (e.type == "V") {
            // std::cout << "\n>>> Stamping V...\n";
            // std::cout << e.type << e.id << " " << e.from << " " << e.to << " " << e.value << " " << e.group << std::endl;
            
			if (e.from) {
                from_str = "V(n" + std::to_string(e.from) + ")";
                // std::cout << "From: " << from_str << std::endl;

                // Use vector to stamp
                auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
                if (it == matrix.x_matrix.end()) {
                    matrix.x_matrix.push_back(from_str);
                    matrix.rhs_matrix.push_back(0);
                }
            }
            if (e.to) {
                to_str = "V(n" + std::to_string(e.to) + ")";
                // std::cout << "To: " << to_str << std::endl;

                // Use vector to stamp
                auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
                if (it == matrix.x_matrix.end()) {
                    matrix.x_matrix.push_back(to_str);
                    matrix.rhs_matrix.push_back(0);
                }
            }
            i_str = "I(" + e.type + std::to_string(e.id) + ")";
            // std::cout << "Current: " << i_str << std::endl;
            
            auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), i_str);
            if (it == matrix.x_matrix.end()) {
                matrix.x_matrix.push_back(i_str);
                matrix.rhs_matrix.push_back(e.value);
            }
            else matrix.rhs_matrix[std::distance(matrix.x_matrix.begin(), it)] += e.value;

            // Stamp MNA
            auto from_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
            auto to_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
            auto i_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), i_str);
            int from_idx = std::distance(matrix.x_matrix.begin(), from_it);
            int to_idx = std::distance(matrix.x_matrix.begin(), to_it);
            int i_idx = std::distance(matrix.x_matrix.begin(), i_it);

            if (from_idx < matrix.x_matrix.size() && i_idx < matrix.x_matrix.size()) {
                matrix.mna_matrix[from_idx][i_idx] += 1;
                matrix.mna_matrix[i_idx][from_idx] += 1;
            }
            if (to_idx < matrix.x_matrix.size() && i_idx < matrix.x_matrix.size()) {
                matrix.mna_matrix[to_idx][i_idx] -= 1;
                matrix.mna_matrix[i_idx][to_idx] -= 1;
            }

			// show_matrix(matrix);
        }
		// ! Stamping I
        else if (e.type == "I") {
            // std::cout << "\n>>> Stamping I...\n";
            // std::cout << e.type << e.id << " " << e.from << " " << e.to << " " << e.value << " " << e.group << std::endl;

            if (e.group == 1) {
                // * Group 1
                if (e.from) {
                    from_str = "V(n" + std::to_string(e.from) + ")";
                    // std::cout << "From: " << from_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(from_str);
                        matrix.rhs_matrix.push_back(-e.value);
                    }
                    else {
                        matrix.rhs_matrix[std::distance(matrix.x_matrix.begin(), it)] -= e.value;
                    }
                }
                if (e.to) {
                    to_str = "V(n" + std::to_string(e.to) + ")";
                    // std::cout << "To: " << to_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(to_str);
                        matrix.rhs_matrix.push_back(e.value);
                    }
                    else matrix.rhs_matrix[std::distance(matrix.x_matrix.begin(), it)] += e.value;
                }
            }
            else {
                // * Group 2
                if (e.from) {
                    from_str = "V(n" + std::to_string(e.from) + ")";
                    // std::cout << "From: " << from_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(from_str);
                        matrix.rhs_matrix.push_back(0);
                    }
                }
                if (e.to) {
                    to_str = "V(n" + std::to_string(e.to) + ")";
                    // std::cout << "To: " << to_str << std::endl;

                    // Use vector to stamp
                    auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
                    if (it == matrix.x_matrix.end()) {
                        matrix.x_matrix.push_back(to_str);
                        matrix.rhs_matrix.push_back(0);
                    }
                }

                i_str = "I(" + e.type + std::to_string(e.id) + ")";
                // std::cout << "Current: " << i_str << std::endl;
                
                auto it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), i_str);
                if (it == matrix.x_matrix.end()) {
                    matrix.x_matrix.push_back(i_str);
                    matrix.rhs_matrix.push_back(e.value);
                }
                else matrix.rhs_matrix[std::distance(matrix.x_matrix.begin(), it)] += e.value;

                // Stamp MNA
                auto from_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), from_str);
                auto to_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), to_str);
                auto i_it = std::find(matrix.x_matrix.begin(), matrix.x_matrix.end(), i_str);
                int from_idx = std::distance(matrix.x_matrix.begin(), from_it);
                int to_idx = std::distance(matrix.x_matrix.begin(), to_it);
                int i_idx = std::distance(matrix.x_matrix.begin(), i_it);

                if (from_idx < matrix.x_matrix.size() && i_idx < matrix.x_matrix.size())
                    matrix.mna_matrix[from_idx][i_idx] += 1;
                if (to_idx < matrix.x_matrix.size() && i_idx < matrix.x_matrix.size())
                    matrix.mna_matrix[to_idx][i_idx] -= 1;
                if (i_idx < matrix.x_matrix.size())
                    matrix.mna_matrix[i_idx][i_idx] += 1;
            }

            // show_matrix(matrix);
        }
    }
}

void Stamp::show_matrix(Matrix& matrix) {
    std::cout << "\n>>>>Show matrix: \n";
    for (int i = 0; i < matrix.x_matrix.size(); ++i) {
        for (int j = 0; j < matrix.x_matrix.size(); ++j)
            std::cout << matrix.mna_matrix[i][j] << " ";
        std::cout << "\t" << matrix.x_matrix[i] << "\t" << matrix.rhs_matrix[i] << std::endl;
    }
}

void Stamp::output(std::string mna_filename, std::string xvec_filename, std::string rhs_filename, Matrix& matrix) {
    std::cout << "\n>> Output...\n";

    std::ofstream mna_file, xvec_file, rhs_file;
    mna_file.open(mna_filename, std::ios::out);
    xvec_file.open(xvec_filename, std::ios::out);
    rhs_file.open(rhs_filename, std::ios::out);
    if (!mna_file) {
        std::cerr << "Failed to open file: " << mna_filename << ".\n";
        return;
    }
    if (!xvec_file) {
        std::cerr << "Failed to open file: " << xvec_filename << ".\n";
        return;
    }
    if (!rhs_file) {
        std::cerr << "Failed to open file: " << rhs_filename << ".\n";
        return;
    }

    for (const auto& mna_row: matrix.mna_matrix) {
        for (const auto& e: mna_row)
            mna_file << e << " ";
        mna_file << std::endl;
    }
    for (const auto & x: matrix.x_matrix) {
        xvec_file << x << std::endl;
    }
    for (const auto& rhs: matrix.rhs_matrix) {
        rhs_file << rhs << std::endl;
    }
    mna_file.close();
    xvec_file.close();
    rhs_file.close();
}
