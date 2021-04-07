#include "score.h"
#include <iostream>

Score::Score(Query* q, SequenceMapping* sm, Blosum* b):q_(q), sm_(sm), b_(b), sequence_(q->sequence()) {
    scores_ = vector<vector<int>>(q_->size(), vector<int>());
    exactMatch();
    buildSeeds();
}

void Score::exactMatch() {
    const string& sequence_ = q_->sequence();
    for (unsigned i=0; i<q_->size()-2; ++i) {
        string tripleAA = sequence_.substr(i, 3);
        if (sm_->contains(tripleAA)) {
            const vector<int>& positions = sm_->getPos(tripleAA);
            for (int pos:positions) {
                scores_[i].push_back(pos);
            }
        }
    }
}

void Score::buildSeeds() {
    /*
        example:
            Query Sequence : M E E T T I N G  
 vector<vector<int>>scores_:[0,1,2,..i...6,7]
                vector<int>:[...j...]   // record the subject indecies of exact match
    */
    for (unsigned i=0; i<scores_.size()-2; i++) {
        for (unsigned j=0; j<scores_[i].size(); j++) {
            if (!add(i, j)) continue;

            Pattern pat (q_->title(), sm_->title());
            pat.score += tripleScore(sequence_.substr(i,3), sequence_.substr(i,3));
            pat.qs = i;
            pat.qe = i;
            pat.ss = scores_[i][j];
            pat.se = scores_[i][j];
            unsigned successor = 1;

            while (i+successor < scores_.size()-2) {
                int next = binarySearch(scores_[i+successor], pat.se+1);
                if (next == -1) break;
                if (!add(i+successor, next)) break;
                pat.qe = i+successor;
                pat.se = scores_[i+successor][next];
                pat.score += tripleScore(sequence_.substr(i,3), sequence_.substr(i,3));
                successor++;
            }

            if (pq.size() == seedNumber && pq.top().score < pat.score) pq.pop();
            if (pq.size() < seedNumber) pq.push(pat);
            
        }
    }
}

int Score::binarySearch(const vector<int>&v, int t) {
    if (v.size() < 1) return -1;
    int l = 0, r = (int)v.size()-1;
    while (r >= l) {
        int m = l+(r-l)/2;
        if (v[m] == t) return m;
        if (v[m] < t) {
            l = m+1;
        } else {
            r = m-1;
        }
    }
    return -1;
}

void Score::fuzzyMatch(const string& input) {
    // currently does not support fuzzyMatch, too much work
}

int Score::tripleScore(const string& triQAA, const string& triSAA) {
    int res = 0;
    for (unsigned i=0; i<3; i++) {
        res+=b_->getScore(triQAA[i], triSAA[i]);
    }
    return res;
}

bool Score::add(int i, int j) {
    if (added(i, j)) return false;
    if (!added(i)) {
        added_[i] = set<int>();
    }
    added_[i].insert(j);
    return true;
}

bool Score::added(int i) {
    return added_.find(i) != added_.end();
}

bool Score::added(int i, int j) {
    if (!added(i)) return false;
    return added_[i].find(j) != added_[i].end();
}

void Score::popAll() {
    while (!pq.empty()) {
        Pattern pat = pq.top(); pq.pop();
        string pattern = sequence_.substr(pat.qs, pat.qe-pat.qs+1);
        std::cout<<pattern<<std::endl;
        // std::cout<<"query start: "<<pat.qs<<std::endl;
        // std::cout<<"query end: "<<pat.qe<<std::endl;
        // std::cout<<"subject start: "<<pat.ss<<std::endl;
        // std::cout<<"subject end: "<<pat.se<<std::endl;
        // std::cout<<"Matching score: "<<pat.score<<std::endl;
    }
}