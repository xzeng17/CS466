#include "query.h"
#include "../file_loader/fileloader.h"

#include <iostream>

Query::Query(const string& filename) {
    Fileloader fl(filename);
    try {
        title_ = fl.readLine();
    } catch (runtime_error e) {
        std::cout<<"Error: Cannot load query file"<<std::endl;
    }
    if (title_[0] != '>') throw runtime_error("Error: Unaccetable fasta format.");
    
    while (fl.hasNext()) {
        sequence_ += fl.readLine();
    }
    length_ = sequence_.size();

    if (length_ < 10) throw runtime_error("Error: Query is too short, please input at least 10 residues.");
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