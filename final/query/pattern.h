#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Pattern {
    // title names
    string query;
    string subject;

    // each index means the first char of the triplet AA!!!
    unsigned qs = 0;    // query index start
    unsigned qe = 0;    // query index end, real end should +2
    unsigned ss = 0;    // subject index start
    unsigned se = 0;    // subject index end, real end should +2
    int score = 0;      // Matching score

    unsigned identities = 0;
    unsigned positives = 0;
    unsigned gaps = 0;


    Pattern(const string& q, const string& s);
    bool operator>(const Pattern& other) const;
    bool operator<(const Pattern& other) const;


    // aligned sequences
    vector<string> commentLeft;     // record + for conserved mutation, AA for match, space for gap
    vector<string> queryLeft;
    vector<string> subjectLeft;     // left are in reversed order
    vector<string> commentRight;
    vector<string> queryRight;
    vector<string> subjectRight;     // in order

    void report();
    unsigned size() const;
    unsigned allStringSize() const;
};