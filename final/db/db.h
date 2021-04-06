#pragma once

#include <vector>
#include <map>
#include <string>
#include <set>
#include "sequencemapping.h"
#include "../file_loader/fileloader.h"

using namespace std;


class Database {
    public:
        Database(const string& filename);
        bool contains(const string& tripleAA) const;
        bool contains(const string& tripleAA, const string& aa);
        unsigned size() const;

    private:
        void init(Fileloader& fl);
        vector<SequenceMapping> db_;
        map<string, int> titles_;
};