#include <iostream>
#include <string>
#include <fstream>
#include <istream>

#include "file_loader/fileloader.h"
#include "matrix/blosum.h"
#include "db/db.h"
#include "db/sequencemapping.h"
#include "query/pattern.h"
#include "query/query.h"
#include "query/score.h"

using namespace std;

// int main (int argc, char** argv) {
int main () {
    string assets="assets/";

    Blosum b;
    // cout<<"Matching score is: "<<b.getScore('J', 'A')<<endl;

    string sname = assets+"gfps.txt";    // fasta file, subjects
    Database db(sname);

    string qname = assets+"query.txt";
    Query q (qname);
    vector<SequenceMapping> sms = db.getDB();
    
    //sms[0].printMap();

    Score score (&q, &sms[0], &b);

    score.popAll();

    // string name = "assets/gfps.txt";
    // Fileloader fl(name);
    // while (fl.hasNext()) cout<<"Read line: "<<fl.readLine()<<endl;
    return 0;
}