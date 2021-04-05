#include <iostream>
#include <string>
#include <fstream>
#include <istream>

#include "file_loader/fileloader.h"
#include "matrix/blosum.h"

using namespace std;

// int main (int argc, char** argv) {
int main () {
    string filename = "assets/gfps.txt";
    Fileloader fl (filename);
    fl.readAll();

    Blosum b;
    cout<<"Matching score is: "<<b.getScore('A', 'A')<<endl;
    return 0;
}