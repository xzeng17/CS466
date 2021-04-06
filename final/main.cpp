#include <iostream>
#include <string>
#include <fstream>
#include <istream>

#include "file_loader/fileloader.h"
#include "matrix/blosum.h"
#include "db/db.h"
#include "db/sequencemapping.h"

using namespace std;

// int main (int argc, char** argv) {
int main () {
    Blosum b;
    cout<<"Matching score is: "<<b.getScore('C', 'A')<<endl;

    string filename = "assets/gfps.txt";    // fasta file
    Database db(filename);

    return 0;
}