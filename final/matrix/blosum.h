#include<string>
#include<map>

using namespace std;


class Blosum {
    public:
        Blosum();
        Blosum(string filename);

        int getScore(const char& aaA, const char& aaB);

    private:
        string filename_ = "assets/blosum.csv";
        map<char, map<char, int>> matrix_;
        void init();
        int getNumber(const string& line, unsigned& idx);

};