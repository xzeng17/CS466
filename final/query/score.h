#pragma once

#include "query.h"
#include "../db/sequencemapping.h"
#include "../matrix/blosum.h"
#include "pattern.h"

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

class Score {
    public:
        Score(Query* q, SequenceMapping* sm, Blosum* b);
        void popAll();
        
    private:
        Query* q_;
        SequenceMapping* sm_;
        Blosum* b_;
        const unsigned seedNumber = 3;   //hard coded the limit of seeds
        const unsigned seedCut_ = 10; // hard coded the cutoff for being a seed, fuzzy match
        const string& sequence_;
        
        priority_queue<Pattern, vector<Pattern>, greater<Pattern> > pq;
        vector<vector<int> > scores_;
        map<int, set<int> > added_;      // {i: {j}}

        void exactMatch();
        void buildSeeds();  // totally based on the blosum matching score
        int binarySearch(const vector<int>&v, int t);
        void fuzzyMatch(const string& input);
        int tripleScore(const string& triQAA, const string& triSAA);

        bool add(int i, int j);
        bool added(int i);
        bool added(int i, int j);

        
};