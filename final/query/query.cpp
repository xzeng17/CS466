#include "query.h"
#include "../file_loader/fileloader.h"

#include <iostream>

// Query::Query(const string& filename) {
//     Fileloader fl(filename);
//     try {
//         title_ = fl.readLine();
//     } catch (runtime_error e) {
//         std::cout<<"Error: Cannot load query file"<<std::endl;
//     }
//     if (title_[0] != '>') throw runtime_error("Error: Unaccetable fasta format.");
    
//     while (fl.hasNext()) {
//         sequence_ += fl.readLine();
//     }
//     length_ = sequence_.size();

//     if (length_ < 10) throw runtime_error("Error: Query is too short, please input at least 10 residues.");
// }

Query::Query(const string& title) {
    title_ = title;
}

unsigned Query::size() const {
    return length_;
}

const string& Query::sequence() const {
    return sequence_;
}

const string& Query::title() const {
    return title_;
}

string Query::get(unsigned start, unsigned size) {
    string res;
    if (start >= sequence_.size()) {
        return res;
    }
    unsigned totalSize = start+size;
    for (unsigned i=start; i<totalSize && i<sequence_.size(); i++) {
        res.push_back(sequence_[i]);
    }
    //std::cout<<"full string: "<<sequence()<<std::endl;
    //std::cout<<"substring: "<<res<<std::endl;
    return res;
}

// For building Query
void Query::append(const string& seq) {
    length_ += seq.size();
    sequence_ += seq;
}