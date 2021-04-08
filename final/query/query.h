#pragma once
#include <string>
#include <vector>

using namespace std;


class Query {

    public:
        Query(const string& filename);
        unsigned size() const;
        const string& sequence() const;
        const string& title() const;
        const vector<char> aa = {'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V','B','Z','X'};
        string get(unsigned start, unsigned size);

    private:
        string title_;
        unsigned length_ = 0;
        string sequence_;
        
};