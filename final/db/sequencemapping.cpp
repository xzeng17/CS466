#include "sequencemapping.h"
#include "../query/util.hpp"
#include <iostream>

SequenceMapping::SequenceMapping(const string& title) {
    title_ = title;
}

void SequenceMapping::build(const string& sequence) {
    if (sequence.size() < 3) return;

    if (subject_.empty()) {
        subject_.push_back(sequence);
        startIdx_.push_back(0);
    } else {
        subject_.push_back(sequence.substr(2, sequence.size()));
        startIdx_.push_back(subject_[subject_.size()-1].size()+startIdx_[startIdx_.size()-1]);
    }

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

string SequenceMapping::get(unsigned start, unsigned size) {
    
    int arrIdx = Util::largestSmallerEqual(startIdx_, start);
    if (arrIdx < 0 || size == 0) return "";
    string res;

    while (size && start < seqSize()) {
        for (unsigned i=start - startIdx_[arrIdx]; i<subject_[arrIdx].size() && size; i++) {
            res.push_back(subject_[arrIdx][i]);
            size--;
            start++;
        }
        arrIdx++;
    }
    return res;
}

unsigned SequenceMapping::seqSize() {
    return startIdx_[startIdx_.size()-1]+subject_[subject_.size()-1].size();
}