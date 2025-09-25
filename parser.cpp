#include "parser.h"
#include <sstream>

void Parser::parser(std::string filename, Data& data) {
    std::cout << ">> Parsing...\n";
    std::ifstream in_file;
    in_file.open(filename, std::ios::in);
    if (!in_file) {
        std::cerr << "Failed to open file: " << filename << ".\n";
        return;
    }

    std::string line, str;
    std::vector<std::string> net;

    while (getline(in_file, line)) {
        Element element;
        element.group = 1;
        std::stringstream ss(line);
        while (ss >> str) {
            if (str == "G2") {
                element.group = 2;
                break;
            }
            // std::cout << " " << str;
            net.push_back(str);
        }

        // Parser
        element.type = net[0][0];
        element.id = stoi(net[0].substr(1, net[0].length()));
        element.from = net[1] == "0" ? 0 : stoi(net[1].substr(1, net[1].length()));
        element.to = net[2] == "0" ? 0 : stoi(net[2].substr(1, net[2].length()));
        element.value = stod(net[3]);
        data.elements.push_back(element);
        net.clear();
    }
    in_file.close();
}

void Parser::check(Data& data) {
    std::cout << "\n>> Parser checking...";
    for (auto& e: data.elements) {
        std::cout << "\nFrom data: " << e.type << e.id << " " << e.from << " " << e.to << " " << e.value << " " << e.group;
    }
}
