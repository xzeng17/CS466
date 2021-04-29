#include "pattern.h"
#include <iostream>
using std::cout;
using std::endl;

Pattern::Pattern(const string& q, const string& s) {
    query = q;
    subject = s;
}

bool Pattern::operator>(const Pattern& other) const {
    return score > other.score;
}

bool Pattern::operator<(const Pattern& other) const {
    return score < other.score;
}

unsigned Pattern::size() const {
    /*  0    5
        AABCDEFG
        s    e
    */
    return qe-qs+3;
}

unsigned Pattern::allStringSize() const {
    return commentLeft.size() + queryLeft.size() + subjectLeft.size() + commentRight.size() + queryRight.size() + subjectRight.size(); 
}

void Pattern::report() {
    if ((queryLeft.size() != commentLeft.size() && commentLeft.size() != subjectLeft.size()) 
        || allStringSize() == 0) { 
        // cout<<"!!! Bad format !!!"<<endl;
        return; // include a simple check;
    }
    printf("\033[36m<--------------------------Report---------------------------->\033[0m\n");
    cout<<"Query:   "<<query<<endl;
    cout<<"Subject: "<<subject<<endl;

    double ident =  (double)identities  /   (double)size();
    double posit =  (double)positives   /   (double)size();
    double gap =    (double)gaps        /   (double)size();
    cout<<"      Identities: "<<ident<<"      Positives: "<<posit<<"      Gaps: "<<gap<<"      Scores: "<<score<<endl;

    string queryRes;
    string commentRes;
    string subjectRes;

    for (int i = (int) queryLeft.size()-1; i>=0; i--) {
        queryRes+=queryLeft[i];
        commentRes+=commentLeft[i];
        subjectRes+=subjectLeft[i];
    }
    //cout<<"queryRes: "<<queryRes<<" at line: "<<__LINE__<<endl;        // debug
    //cout<<"commentRes: "<<commentRes<<" at line: "<<__LINE__<<endl;    // debug
    //cout<<"subjectRes: "<<subjectRes<<" at line: "<<__LINE__<<endl;    // debug
    for (unsigned i=0; i<queryRight.size(); i++) {
        //cout<<queryRight.size()<<commentRight.size()<<subjectRight.size()<<endl;  // debug
        queryRes+=queryRight[i];
        commentRes+=commentRight[i];
        subjectRes+=subjectRight[i];
    }
    //cout<<"queryRes: "<<queryRes<<" at line: "<<__LINE__<<endl;        // debug
    //cout<<"commentRes: "<<commentRes<<" at line: "<<__LINE__<<endl;    // debug
    //cout<<"subjectRes: "<<subjectRes<<" at line: "<<__LINE__<<endl;    // debug
    cout<<queryRes<<"  Query: "<<qs+1<<"-"<<qe+2+1<<endl;   
    cout<<commentRes<<endl;
    cout<<subjectRes<<"  Subject: "<<ss+1<<"-"<<se+2+1<<endl;   // report 1 indexed based
    printf("\033[32m<--------------------------End---------------------------->\033[0m\n");
    cout<<endl;
}