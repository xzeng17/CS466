#pragma once

#include "query.h"
#include "../db/sequencemapping.h"
#include "../matrix/blosum.h"
#include "pattern.h"
#include "util.hpp"

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

class Score {
    public:
        Score(Query* q, SequenceMapping* sm, Blosum* b);
        vector<string> expendSequence(const string& seqA, const string& seqB);
        void reverseString(string& input);

    private:
        Query* q_;
        SequenceMapping* sm_;
        Blosum* b_;

        const unsigned seedNumber = 3;   //hard coded the limit of seeds
        const int seedCut = 10; // hard coded the cutoff for being a seed, fuzzy match
        const int gap = -10; // hard coded the gap panelty;

        const string& sequence_;
        
        priority_queue<Pattern, vector<Pattern>, greater<Pattern> > pq;
        vector<vector<int> > scores_;
        map<int, set<int> > added_;      // {i: {j}}
        vector<Pattern> seeds_;     // seeds poped from pq;

        void popAll();
        void exactMatch();
        void buildSeeds();  // totally based on the blosum matching score
        void fuzzyMatch(const string& input);
        int tripleScore(const string& triQAA, const string& triSAA);    // Obtain three Amino acids matching score
        void expend();

        bool add(int i, int j);
        bool added(int i);
        bool added(int i, int j);

};
