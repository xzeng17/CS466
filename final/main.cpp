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
    string assetsDir = "assets/";
    string queryDir = "InputQuery/";
    string subjectDir = "InputSubjects/";

    string qname = queryDir + "query.txt";
    string sname = subjectDir + "gfps.txt";    // fasta file, subjects

    Blosum b;   Query q(qname);
    Database db(sname);
    vector<SequenceMapping>& sms = db.getDB();

    for (SequenceMapping sm : sms) {
        Score score(&q, &sm, &b);
    }
    // sms[0].printMap();
    // cout<<"test get function"<<endl;
    // cout<<sms[0].get(3,30000)<<endl;

    

    // string name = "assets/gfps.txt";
    // Fileloader fl(name);
    // while (fl.hasNext()) cout<<"Read line: "<<fl.readLine()<<endl;
    return 0;
}