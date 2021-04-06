#include<string>
#include<vector>

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

    string line = fl.readLine();
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
    if (matrix_.find(aaA) == matrix_.end() || matrix_[aaA].find(aaB) == matrix_[aaA].end()) throw runtime_error("Error: Unknown input");
    return matrix_[aaA][aaB];
}