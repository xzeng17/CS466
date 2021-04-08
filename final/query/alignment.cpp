#include "alignment.h"

Alignment::Alignment(const string& query, const string& subject, unsigned idx, int s) {
    aline.push_back(query);
    aline.push_back(subject);
    start_idx = idx;
    score = s;
}

bool Alignment::operator<(Alignment& other) {
    return start_idx < other.start_idx;
}
bool Alignment::operator>(Alignment& other) {
    return start_idx > other.start_idx;
}