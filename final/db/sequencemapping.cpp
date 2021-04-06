#include "sequencemapping.h"
#include <iostream>
using namespace std;
SequenceMapping::SequenceMapping(const string& title) {
    title_ = title;
}

void SequenceMapping::build(const string& sequence) {
    if (sequence.size() < 3) return;
    for (int i=0; i<(int)sequence.size()-2; ++i) {
        string threeAA;
        threeAA = sequence.substr(i, 3);
        if (!contains(threeAA)) {
            map_[threeAA] = set<int>();
        }
        map_[threeAA].insert(idx_++);
    }
}

bool SequenceMapping::contains(const string& key) const {
    return map_.find(key) != map_.end();
}

string SequenceMapping::title() {
    return title_;
}