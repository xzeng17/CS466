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

void Pattern::report() {
    if (queryLeft.size() != commentLeft.size() && commentLeft.size() != subjectLeft.size()){ 
        // cout<<"!!! Bad format !!!"<<endl;
        return; // include a simple check;
    }
    cout<<"<--------------------------Report---------------------------->"<<endl;
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
    // cout<<"queryRes"<<queryRes<<endl;        // debug
    // cout<<"commentRes"<<commentRes<<endl;    // debug
    // cout<<"subjectRes"<<subjectRes<<endl;    // debug
    for (unsigned i=0; i<queryRight.size(); i++) {
        //cout<<queryRight.size()<<commentRight.size()<<subjectRight.size()<<endl;  // debug
        queryRes+=queryRight[i];
        commentRes+=commentRight[i];
        subjectRes+=subjectRight[i];
    }
    cout<<queryRes<<"  Query: "<<qs<<"-"<<qe+2<<endl;   
    cout<<commentRes<<endl;
    cout<<subjectRes<<"  Subject: "<<ss<<"-"<<se+2<<endl;
    cout<<"<----------------------------End------------------------------>"<<endl;
}