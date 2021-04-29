#include "queries.h"
#include <iostream>
using std::cout;
using std::endl;

Queries::Queries(string filename) {
    Fileloader fl(filename);
    try {
        init(fl);
    } catch (runtime_error e) {
        cout<<e.what()<<endl;
    }
    cout<<"Parsed from InputQuery/"<<filename<<". Queries has: "<<queries_.size() <<" entries!"<<endl;
}

void Queries::init(Fileloader& fl) {
    cout<<"Fetching Queries..."<<endl;
    string line;
    
    // iterator through each fasta entry as a block
    while (fl.hasNext()) {
        line = fl.readLine();
        if (line[0] != '>') {
            line.clear();
            continue;
        }
        Query q (line);
        //cout<<"Title is : "<<line<<endl;
        line.clear();
        line = fl.readLine();
        while (line.size() > 0 && isalpha(line[0])) {
            q.append(line);
            //cout<<line<<endl;
            line.clear();
            if (fl.hasNext()) line = fl.readLine();
        }
        if (q.size() > 0) queries_.push_back(q);
    }
}

const vector<Query>& Queries::getQueries() const {
    return queries_;
}