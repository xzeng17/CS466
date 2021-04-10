// #define CATCH_CONFIG_MAIN

#include "../cs225/catch/catch.hpp"
#include "../file_loader/fileloader.h"
#include "../matrix/blosum.h"
#include "../db/db.h"
#include "../db/sequencemapping.h"
#include <sstream>

using namespace std;

// Test DB function, test if generated Triple AA has all combinations
TEST_CASE("test_tripleDB", "[valgrind][weight=1]") {
    string testname = "tests/test_data/fasta_tripleAA.txt";

    Database db (testname);
    REQUIRE(db.size() == 1);

    Fileloader fl (testname);
    string title = fl.readLine();
    string concSeq;
    while (fl.hasNext()) {
        concSeq += fl.readLine();
    }

    //db.printMap(title);

    for (unsigned i=0; i<concSeq.size()-2; i++) {
        string tripleAA = concSeq.substr(i, 3);
        //cout<<tripleAA<<endl;
        REQUIRE(db.contains(title, tripleAA));
    }
}

