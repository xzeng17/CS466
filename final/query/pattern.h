#pragma once
#include <string>

using namespace std;

struct Pattern {
    // title names
    string query;
    string subject;

    // each index means the first char of the triplet AA
    unsigned qs = 0;    // query index start
    unsigned qe = 0;    // query index end
    unsigned ss = 0;    // subject index start
    unsigned se = 0;    // subject index end
    int score = 0;      // Matching score

    Pattern(const string& q, const string& s);
    bool operator>(const Pattern& other) const;
    bool operator<(const Pattern& other) const;

    unsigned size() const;
};