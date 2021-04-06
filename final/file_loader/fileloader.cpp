#include<string>
#include <fstream>
#include <istream>
#include <iostream>
#include "fileloader.h"

using namespace std;


// open a file from filename
Fileloader::Fileloader(const string& filename) {
    filename_ = filename;
    load();
}

Fileloader::~Fileloader() {
    file_.close();
}

void Fileloader::load() {
    file_.open(filename_);

    file_.seekg(0, file_.end);
    // get total word count
    totalByte_ = file_.tellg();
    // set position to the begining
    file_.seekg(0, file_.beg);
}

size_t Fileloader::getByte() {
    return file_.tellg();
}

string Fileloader::readLine() {
    string line;
    getline(file_, line);
    return line;
}

void Fileloader::readAll() {
    while (hasNext()) {
        string line = readLine();
        cout<<line<<endl;
    }
}

bool Fileloader::hasNext() {
    return getByte() < totalByte_;
}