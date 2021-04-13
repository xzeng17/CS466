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

    string qname = queryDir + "query.txt";
    string sname = subjectDir + "gfps.txt";    // fasta file, subjects

    if (argc>3) {
        qname = argv[1];
        sname = argv[2];
    }

    Blosum b;   Query q(qname);
    Database db(sname);
    vector<SequenceMapping>& sms = db.getDB();


    // Score score(&q, &sms[0], &b);

    // string testSeqA = "VPILVELDGDVNGHKFSVGEGEGDATYGKLTLKFICTTGKLPVPWPTL";
    // string testSeqB = "MSKGEELFTGVVPILVELDGDVNGHKFSVSGEGEGDATYGKLTLKFICTTGKLPVPWPTLVTTLTYGVQCFSRYPDHMKRHDFFKSAMPEGYVQERTISFKDDGNYKTRAEVKFEGDTLVNRIELKGIDFKEDGNILGHKLEYNYNSHNVYITADKQKNGIKANFKTRHNIEDGGVQLADHYQQNTPIGDGPVLLPDNHYLSTQSALSKDPNEKRDHMVLLEFVTAAGITHGMDELYK";

    // vector<vector<int> > dp(testSeqA.size()+1, vector<int>(testSeqB.size()+1, 0));
    // score.editingDistance(testSeqA, testSeqB, dp);
    // backTrackPath(dp, testSeqA, testSeqB, testSeqB.size()-1, testSeqA.size()-1);

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