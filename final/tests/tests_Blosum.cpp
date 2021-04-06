// #define CATCH_CONFIG_MAIN

#include "../cs225/catch/catch.hpp"
#include "../file_loader/fileloader.h"
#include "../matrix/blosum.h"
#include "../db/db.h"
#include "../db/sequencemapping.h"
#include <sstream>

using namespace std;

// Test if Blosum matrix gives expected result from given any two amino acids
TEST_CASE("test_blosum", "[valgrind][weight=1]") {
    vector<char> aa = {'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V','B','Z','X'};
    string blosum_test = "tests/test_data/blosum.txt";
    Fileloader fl (blosum_test);
    Blosum b;
    for (unsigned i=0; i<aa.size(); i++) {
        string res;
        for (unsigned j=0; j<aa.size(); j++) {
            stringstream ss;
            ss<<b.getScore(aa[i], aa[j]);
            res += ss.str() + ",";
        }
        REQUIRE(res == fl.readLine());
    }
}

