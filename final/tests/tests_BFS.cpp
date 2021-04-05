// #define CATCH_CONFIG_MAIN

#include "../cs225/catch/catch.hpp"
#include "../graphs/udgraph.h"
#include "../traversals/BFS.h"

using namespace std;

TEST_CASE("testBFS", "[valgrind][weight=1]") {
    vector<int> expected = {-1,5,2,2,-1};
    for (int i=1; i<= 5; i++) {
        string testfile = "tests/testInputBFS/test";
        testfile+=to_string(i);
        testfile+=".csv";
        UdGraph test(testfile);
        string nodeA = "0", nodeB = "5";
        int distance = test.getShortestDistance(nodeA, nodeB);    
        REQUIRE(distance == expected[i-1]);
    }
}

