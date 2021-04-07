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
        bool contains(const string& title) const;   // fasta title of sequence name
        bool contains(const string& title, const string& aa);   // the permutation of amino acid tirplet
        unsigned size() const;
        
        void printMap(const string& title);
        vector<SequenceMapping> getDB();   // for test purpose
    private:
        void init(Fileloader& fl);
        vector<SequenceMapping> db_;
        map<string, int> titles_;
};