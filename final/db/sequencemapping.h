#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::set;

using namespace std;
class SequenceMapping {
    public:
        SequenceMapping(const string& title);
        void build();

        bool contains(const string& key) const;
        const vector<int>& getPos(const string& triAA);
        const string& title() const;
        void printMap();
        string get(unsigned start, unsigned size);
        unsigned size() const;

    //private:
        void addSequence(const string& seq);

        int idx_ = 0;
        string title_;
        map<string, vector<int> > map_;
        string sequence_;    // subject original sequence
        
};