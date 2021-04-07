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
        void build(const string& sequence);
        bool contains(const string& key) const;
        const vector<int>& getPos(const string& triAA);
        const string& title() const;
        void printMap();
        void printArr(const vector<int>& arr);

    private:
        int idx_ = 0;
        string title_;
        map<string, vector<int> > map_;

        
};