#include <vector>
#include <iostream>
#include "blosum.h"
#include "../file_loader/fileloader.h"

using namespace std;


Blosum::Blosum() {
    init();
}

Blosum::Blosum(string filename) {
    filename_ = filename;
    init();
}

void Blosum::init() {
    Fileloader fl (filename_);
    string line;
    try {
        line = fl.readLine();
    } catch (runtime_error e) {
        std::cout<<"Failed to load Blosum input."<<std::endl;
    }
    
    vector<char> bar;
    for (char c : line) {
        if (isalpha(c)) {
            bar.push_back(c);
        }
    }

    while (fl.hasNext()) {
        line.clear();
        string line = fl.readLine();
        unsigned idx = 2;
        unsigned barIdx = 0;
        char key = line[0];
        matrix_[key] = map<char, int>();
        while (idx < line.size() && barIdx < bar.size()) {
            matrix_[key][bar[barIdx++]] = getNumber(line, idx);
        }
    }
}

int Blosum::getNumber(const string& line, unsigned& idx) {
    string number;
    while (line[idx] != ',' && idx < line.size()) {
        number.push_back(line[idx++]);
    }
    idx++;
    return stoi(number);
}

int Blosum::getScore(const char& aaA, const char& aaB) {
    if (!validInput(aaA) || !validInput(aaB)) throw runtime_error("Error: Unknown input");
    return matrix_[aaA][aaB];
}

bool Blosum::validInput(const char& aa) const {
    return matrix_.find(aa) != matrix_.end();
}