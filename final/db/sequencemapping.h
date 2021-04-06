#pragma once

#include <string>
#include <map>
#include <set>

using std::string;
using std::map;
using std::set;

class SequenceMapping {
    public:
        SequenceMapping(const string& title);
        void build(const string& sequence);
        bool contains(const string& key) const;
        string title();
    private:
        int idx_ = 0;
        string title_;
        map<string, set<int>> map_;

        
};