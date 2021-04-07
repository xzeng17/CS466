#include "sequencemapping.h"
#include <iostream>

SequenceMapping::SequenceMapping(const string& title) {
    title_ = title;
}

void SequenceMapping::build(const string& sequence) {
    if (sequence.size() < 3) return;
    for (int i=0; i<(int)sequence.size()-2; ++i) {
        string threeAA;
        threeAA = sequence.substr(i, 3);
        if (!contains(threeAA)) {
            map_[threeAA] = vector<int>();
        }
        map_[threeAA].push_back(idx_++);
    }
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
        printArr(it->second);
        cout<<endl;
    }
}

void SequenceMapping::printArr(const vector<int>& arr) {
    for (unsigned i=0; i<arr.size(); i++) {
        cout<<arr[i]<<", ";
    }
}