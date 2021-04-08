#include "pattern.h"

Pattern::Pattern(const string& q, const string& s) {
    query = q;
    subject = s;
}

bool Pattern::operator>(const Pattern& other) const {
    return score > other.score;
}

bool Pattern::operator<(const Pattern& other) const {
    return score < other.score;
}