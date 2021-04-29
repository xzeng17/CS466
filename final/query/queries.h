#pragma once
#include <string>
#include <vector>
#include "query.h"
#include "../file_loader/fileloader.h"

using std::vector;
using std::string;

class Queries {
    public:
        Queries(string filename);
        void init(Fileloader& fl);
        const vector<Query>& getQueries() const;
    private:
        vector<Query> queries_;


};