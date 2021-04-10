#include "score.h"
#include "util.hpp"
using std::cout;using std::endl;
Score::Score(Query* q, SequenceMapping* sm, Blosum* b):q_(q), sm_(sm), b_(b), sequence_(q->sequence()) {
    scores_ = vector<vector<int> >(q_->size(), vector<int>());  // for query element, record matched subject triple AA start index
    exactMatch();
    buildSeeds();
    popAll();
    expend();
    buildReport();
}

void Score::exactMatch() {
    const string& sequence_ = q_->sequence();
    for (unsigned i=0; i<q_->size()-2; ++i) {
        string tripleAA = sequence_.substr(i, 3);
        if (sm_->contains(tripleAA)) {
            const vector<int>& positions = sm_->getPos(tripleAA);
            for (int pos : positions) {
                scores_[i].push_back(pos);
            }
        } else {
            fuzzyMatch(tripleAA);
        }
    }
}

void Score::buildSeeds() {
    /*
        example:
            Query Sequence : M E E T T I N G  
 vector<vector<int>>scores_:[0,1,2,..i...6,7]
                vector<int>:[...j...]   // record the subject indecies of exact match
    */
    for (unsigned i=0; i<scores_.size()-2; i++) {
        for (unsigned j=0; j<scores_[i].size(); j++) {
            if (!add(i, j)) continue;

            Pattern pat (q_->title(), sm_->title());
            pat.score += tripleScore(sequence_.substr(i,3), sequence_.substr(i,3));
            pat.qs = i;
            pat.qe = i;
            pat.ss = scores_[i][j];
            pat.se = scores_[i][j];
            unsigned successor = 1;

            while (i+successor < scores_.size()-2) {
                int next = Util::binarySearch(scores_[i+successor], pat.se+1);  // expend matches by looking for consecutive index
                if (next == -1) break;
                if (!add(i+successor, next)) break;
                pat.qe = i+successor;
                pat.se = scores_[i+successor][next];
                pat.score += tripleScore(sequence_.substr(i,3), sequence_.substr(i,3));
                successor++;
            }

            string querySequence = q_->get(pat.qs, q_->size());
            string subjectSequence = sm_->get(pat.ss, q_->size());
            string commentSequence = buildComment(querySequence, subjectSequence, pat);

            pat.queryRight.push_back(querySequence);
            pat.subjectRight.push_back(subjectSequence);
            pat.commentRight.push_back(commentSequence);

            if (pq.size() == seedNumber && pq.top().score < pat.score) pq.pop();
            if (pq.size() < seedNumber) pq.push(pat);
            
        }
    }
}


void Score::fuzzyMatch(const string& input) {
    if (pq.size() == seedNumber) return;// return if seeds number already satisified
    string varient;
    for (unsigned i=0; i<input.size(); ++i) {
        varient = input;
        for (char c = 'A'; c <= 'Z'; c++) {
            if (!b_->validInput(c)) continue;
            varient[i] = c;
            if (!sm_->contains(varient)) continue;
            int fuzzyScore = tripleScore(input, varient);
            if (fuzzyScore < seedCut) continue;
            const vector<int>& positions = sm_->getPos(varient);
            for (int pos : positions) {
                scores_[i].push_back(pos);
            }
        }
    }
}

int Score::tripleScore(const string& triQAA, const string& triSAA) {
    int res = 0;
    for (unsigned i=0; i<3; i++) {
        res+=b_->getScore(triQAA[i], triSAA[i]);
    }
    return res;
}

bool Score::add(int i, int j) {
    if (added(i, j)) return false;
    if (!added(i)) {
        added_[i] = set<int>();
    }
    added_[i].insert(j);
    return true;
}

bool Score::added(int i) {
    return added_.find(i) != added_.end();
}

bool Score::added(int i, int j) {
    if (!added(i)) return false;
    return added_[i].find(j) != added_[i].end();
}

void Score::popAll() {
    while (!pq.empty()) {
        Pattern pat = pq.top(); pq.pop();
        seeds_.push_back(pat);
        // string pattern = sequence_.substr(pat.qs, pat.qe-pat.qs+1);
        // std::cout<<pattern<<std::endl;
        // std::cout<<"query start: "<<pat.qs<<std::endl;
        // std::cout<<"query end: "<<pat.qe<<std::endl;
        // std::cout<<"subject start: "<<pat.ss<<std::endl;
        // std::cout<<"subject end: "<<pat.se<<std::endl;
        // std::cout<<"Matching score: "<<pat.score<<std::endl;
    }
}


///////////

/*
                                    seqB
                        A  M  I  N  O  A  C  I  D
                      0-5-10-15-20-25-30-35-40-45
                   A -5
                   M-10
             seqA  I-15
                   N-20
                   O-25
*/
// return [query, subject], with '-' indicating gapping
// if the scoring is low, return an empty vector
void Score::expendSequence(const string& seqA, const string& seqB, int& flag, Pattern& pattern) {
    if (seqA.size() == 0 || seqB.size() == 0) {
        flag = 0;
        return;
    }
    //cout<<"seqA is: "<<seqA<<endl;cout<<"seqB is: "<<seqB<<endl;    // print
    vector<vector<int> > dp(seqA.size()+1, vector<int>(seqB.size()+1, 0));
    for (unsigned i=1; i<seqB.size()+1; i++) {
        dp[0][i] = dp[0][i-1] + gap;
    }
    for (unsigned i=1; i<seqA.size()+1; i++) {
        dp[i][0] = dp[i-1][0] + gap;
    }
    int maxScore = 0;
    unsigned x = 0, y = 0;
    for (unsigned i=1; i<seqA.size()+1; i++) {
        for (unsigned j=1; j<seqB.size()+1; j++) {
            //cout<<"from query: "<<seqA[i-1]<<" from subject: "<<seqB[j-1]<<endl;    // print
            int score = b_->getScore(seqA[i-1], seqB[j-1]);
            dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j], dp[i][j-1])+gap);
            if (dp[i][j] > maxScore) {
                maxScore = dp[i][j];
                y = i; x = j;
            }
        }
    }
    bool left = flag == 1;
    if (x != dp[0].size()-1 || y != dp.size()-1) flag = 0;

    if (maxScore < seedCut) {
        flag = 0;
        return;
    } 
    pattern.score += maxScore;
    // update range in pattern
    if (left) {
        pattern.qs -= y+1;
        pattern.ss -= x+1;
    } else {
        pattern.qe += y+1;
        pattern.se += x+1;
    }

    string seqAResult;
    string seqBResult;
    string comment;
    int curScore;

    while (x>0 && y>0) {
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

    comment = buildComment(seqAResult, seqBResult, pattern);

    if (!left) {
        Util::reverseString(seqAResult);Util::reverseString(seqBResult);
        pattern.queryRight.push_back(seqAResult);
        pattern.queryRight.push_back(seqBResult);
        pattern.commentRight.push_back(comment);
    } else {
        pattern.queryLeft.push_back(seqAResult);
        pattern.queryLeft.push_back(seqBResult);
        pattern.commentLeft.push_back(comment);
    }
    
    std::cout<<seqAResult<<endl;std::cout<<seqBResult<<endl;
    return;
}


void Score::expend() {
    
    while (!seeds_.empty()) {
        Pattern seed = seeds_[seeds_.size()-1]; seeds_.pop_back();
        int right = 2;
        int left = 1;

        while (right | left) {
            unsigned size = seed.size();
            if (right) {
                string queryRight = q_->get(seed.qe+1+2, size);
                string subjectRight = sm_->get(seed.se+1+2, size);
                //cout<<"QueryRight: "<<queryRight<<endl;             //print
                //cout<<"subjectRight: "<<subjectRight<<endl;         //print
                if (queryRight.empty() || subjectRight.empty()) {
                    right = 0;
                } else {
                    expendSequence(queryRight, subjectRight, right, seed);
                }
            }

            if (left) {
                string queryLeft;
                string subjectLeft;
                if (seed.ss >= size) {
                    subjectLeft = sm_->get(seed.ss-size, size);
                } else {
                    subjectLeft = sm_->get(0, seed.ss);
                }
                if (seed.qs >= size) {
                    queryLeft = q_->get(seed.qs-size, size);
                } else {
                    queryLeft = q_->get(0, seed.qs);
                }
                //cout<<"queryLeft: "<<queryLeft<<endl;           //print
                //cout<<"subjectLeft: "<<subjectLeft<<endl;       //print
                if (queryLeft.empty() || subjectLeft.empty()) {
                    left = 0;
                } else {
                    Util::reverseString(queryLeft);
                    Util::reverseString(subjectLeft);
                    expendSequence(queryLeft, subjectLeft, left, seed);
                }
            }
        }
        // after expending the seed, it should have the longest alignment
        processedSeeds_.push_back(seed);
        
    }
}

string Score::buildComment(const string& query, const string& subject, Pattern& pattern) {
    string comment;
        for (unsigned i=0; i<query.size(); ++i) {
        if (query[i] == subject[i]) {
            comment.push_back(subject[i]);
            pattern.identities += 1;pattern.positives += 1;
        } else if (query[i] == '-' || subject[i] == '-') {
            comment.push_back('-');
            pattern.gaps += 1;
        } else {
            comment.push_back('+');
            pattern.positives += 1;
        }
    }
    return comment;
}

void Score::buildReport() {
    for (Pattern p : processedSeeds_) {
        if (p.score < scoreCut) continue;
        p.report();
    }
}