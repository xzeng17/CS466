#include "sequencemapping.h"
#include "../query/util.hpp"
#include <iostream>

SequenceMapping::SequenceMapping(const string& title) {
    title_ = title;
}

void SequenceMapping::build() {
    for (unsigned i=0; i<size()-2; i++) {
        string triple = sequence_.substr(i, 3);
        if (map_.find(triple) == map_.end()) {
            map_[triple] = vector<int>();
        }
        map_[triple].push_back(i);
    }
}

void SequenceMapping::addSequence(const string& seq) {
    sequence_ += seq;
}

bool SequenceMapping::contains(const string& key) const {
    return map_.find(key) != map_.end();
}

const vector<int>& SequenceMapping::getPos(const string& triAA) {
    return map_[triAA];
}

const string& SequenceMapping::title() const {
    return title_;
}

void SequenceMapping::printMap() {
    for (auto it=map_.begin(); it!=map_.end(); ++it) {
        cout<<"key is: "<<it->first<<" value is: ";
        Util::printArr(it->second);
        cout<<endl;
    }
}

string SequenceMapping::get(unsigned start, unsigned s) {
    if (start>=size()) return "";
    return sequence_.substr(start, s);
}

unsigned SequenceMapping::size() const {
    return sequence_.size();
}