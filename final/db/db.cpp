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

void Database::init (Fileloader& fl) {
    cout<<"Fetching fasta file..."<<endl;
    string line;
    line = fl.readLine();

    // iterator through each fasta entry as a block
    while (fl.hasNext() && line[0] == '>') {
        // cout<<"Processing sequence: "<<line<<endl;
        // process each fasta entry
        SequenceMapping sm(line);
        titles_[line] = (int) db_.size();
        line = fl.readLine();
        vector<string> two = {"", ""};
        while (line[0] != '>') {
            sm.build(line);
            if (!fl.hasNext()) break;
            two[0] = line.substr(line.size()-2,1);
            two[1] = line.substr(line.size()-1,1);
            line.clear();
            line = two[0]+two[1]+fl.readLine();
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