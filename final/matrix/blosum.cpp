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

int Blosum::getScore(const char& seqA, const char& seqB) {
    if (matrix_.find(seqA) == matrix_.end() || matrix_[seqA].find(seqB) == matrix_[seqA].end()) throw runtime_error("Error: Unknown input");
    return matrix_[seqA][seqB];
}