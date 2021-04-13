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
        
        while (line.size() > 0 && line[0] != '>') {
            sm.addSequence(line);
            if (!fl.hasNext()) break;

            line.clear();
            while (line.size() == 0 && fl.hasNext()) line = fl.readLine();
        }
        sm.build();
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


// for testing purpose, exposing data structure through public API
 vector<SequenceMapping>& Database::getDB() {
     return db_;
 }

 void Database::printMap(const string& title) {
     db_[titles_[title]].printMap();
 }
