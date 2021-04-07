#include "db.h"

#include <iostream>

using namespace std;

Database::Database(const string& filename) {
    Fileloader fl(filename);
    try {
        init(fl);
    } catch (runtime_error e) {
        cout<<e.what()<<endl;
    }

    cout<<"Parsed from "<<filename<<". Database has: "<<size()<<" entries!"<<endl;
}

void Database::init(Fileloader& fl) {
    cout<<"Fetching fasta file..."<<endl;
    string line;
    line = fl.readLine();

    // iterator through each fasta entry as a block
    while (fl.hasNext() && line[0] == '>') {
        // cout<<"Processing sequence: "<<line<<endl;
        // process each fasta entry
        //cout<<"showing header: "<<line<<endl;

        SequenceMapping sm(line);
        titles_[line] = (int) db_.size();
        line = fl.readLine();
        string last = "";
        string sndlast = "";
        
        while (line[0] != '>') {
            string concatedLine = sndlast+last+line;
            //cout<<"showing line: "<<concatedLine<<endl;
            sm.build(line);
            if (!fl.hasNext()) break;
            last = line.substr(line.size()-2,1);
            sndlast = line.substr(line.size()-1,1);
            line.clear();
            while (line.size() == 0 && fl.hasNext()) line = fl.readLine();
        }

        db_.push_back(sm);
        // cout<<"Finish processing sequence: "<<sm.title()<<endl;
    }
}

unsigned Database::size() const {
    return db_.size();
}

bool Database::contains(const string& title) const {
    return titles_.find(title) != titles_.end();
}

bool Database::contains(const string& title, const string& aa) {
    if (!contains(title)) return false;
    int idx = titles_[title];
    SequenceMapping& sm = db_[idx];
    return sm.contains(aa);
}


// for testing purpose, exposing datasture through public API
 vector<SequenceMapping> Database::getDB() {
     return db_;
 }