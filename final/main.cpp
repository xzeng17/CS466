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
#include "query/util.hpp"
#include "query/queries.h"

using namespace std;
// test
int gap = -2;
void backTrackPath(vector<vector<int> >& dp, const string& seqA, const string& seqB, unsigned x, unsigned y) {
    int curScore;
    Blosum b;
    Blosum* b_= &b;
    string seqAResult, seqBResult;
    
    while (x>0 && y>0) {
        cout<<"X: "<<x; cout<<"   Y: "<<y<<endl;
        curScore = dp[y][x];
        if (x>0 && y>0 && dp[y-1][x-1] == curScore - b_->getScore(seqA[y-1], seqB[x-1])) {
            seqAResult.push_back(seqA[--y]);
            seqBResult.push_back(seqB[--x]);
        } else if (x>0 && dp[y][x-1] == curScore-gap) {
            seqBResult.push_back(seqB[--x]);
            seqAResult.push_back('-');
        } else if (y>0 && dp[y-1][x] == curScore-gap) {
            seqBResult.push_back('-');
            seqAResult.push_back(seqA[--y]);
        }
    }
    
    Util::reverseString(seqAResult);    Util::reverseString(seqBResult);
    cout<<seqAResult<<endl;
    cout<<seqBResult<<endl;
}





int main (int argc, char** argv) {
// int main () {
    string assetsDir = "assets/";
    string queryDir = "InputQuery/";
    string subjectDir = "InputSubjects/";

    string qname = queryDir + "queries.txt";
    string sname = subjectDir + "gfps.txt";    // fasta file, subjects

    if (argc>=3) {
        qname = queryDir + argv[1];
        sname = subjectDir + argv[2];
    }

    Blosum b;   
    Queries queries(qname);
    Database db(sname);

    for (Query query : queries.getQueries()) {
        for (SequenceMapping sm : db.getDB()) {
            Score score(&query, &sm, &b);
        }
    }
    return 0;
}