#ifndef _PARSER_H
#define _PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Element {
	std::string type;
    int id;
	int from;
    int to;
    double value;
    int group;
};

class Data {
    public:
        std::vector<Element> elements;
};

class Parser {
    public:
        void parser(std::string filename, Data& data);
        void check(Data& data);
};

#endif
