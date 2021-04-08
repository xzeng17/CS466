#pragma once
#include <string>

using namespace std;

struct Pattern {
    string query;
    string subject;
    unsigned qs = 0;    // query index start
    unsigned qe = 0;    // query index end
    unsigned ss = 0;    // subject index start
    unsigned se = 0;    // subject index end
    int score = 0;      // Matching score

    Pattern(const string& q, const string& s);
    bool operator>(const Pattern& other) const;
    bool operator<(const Pattern& other) const;
};