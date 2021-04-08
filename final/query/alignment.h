#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Alignment {
    unsigned start_idx;
    int score;
    vector<string> aline;   // query, subject

    Alignment(const string& query, const string& subject, unsigned idx, int s);

    bool operator<(Alignment& other);
    bool operator>(Alignment& other);
};