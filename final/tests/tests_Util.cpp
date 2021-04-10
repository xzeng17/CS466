
#include "../cs225/catch/catch.hpp"
#include "../query/util.hpp"

#include <iostream>

vector<int> v = {1,2,4,5,7,10,12};
//               0 1 2 3 4  5  6

TEST_CASE("BinarySearch", "[valgrind][weight=1]") {
    int res;
    res = Util::binarySearch(v, -2); REQUIRE(res == -1);
    res = Util::binarySearch(v, 0); REQUIRE(res == -1);
    res = Util::binarySearch(v, 2); REQUIRE(res == 1);
    res = Util::binarySearch(v, 5); REQUIRE(res == 3);
    res = Util::binarySearch(v, 8); REQUIRE(res == -1);
    res = Util::binarySearch(v, 12); REQUIRE(res == 6);
    res = Util::binarySearch(v, 11); REQUIRE(res == -1);
    res = Util::binarySearch(v, 13); REQUIRE(res == -1);
}

TEST_CASE("largestSmallerEqual", "[valgrind][weight=1]") {
    int res;
    res = Util::largestSmallerEqual(v, -2); REQUIRE(res == -1);
    res = Util::largestSmallerEqual(v, 0); REQUIRE(res == -1);
    res = Util::largestSmallerEqual(v, 2); REQUIRE(res == 1);
    res = Util::largestSmallerEqual(v, 5); REQUIRE(res == 3);
    res = Util::largestSmallerEqual(v, 8); REQUIRE(res == 4);
    res = Util::largestSmallerEqual(v, 12); REQUIRE(res == 6);
    res = Util::largestSmallerEqual(v, 11); REQUIRE(res == 5);
    res = Util::largestSmallerEqual(v, 13); REQUIRE(res == 6);
}

TEST_CASE("smallestLargerEqual", "[valgrind][weight=1]") {
    int res;    // vector<int> v = {1,2,4,5,7,10,12};
                           //       0 1 2 3 4  5  6
    res = Util::smallestLargerEqual(v, -2); REQUIRE(res == 0);
    res = Util::smallestLargerEqual(v, 0); REQUIRE(res == 0);
    res = Util::smallestLargerEqual(v, 2); REQUIRE(res == 1);
    res = Util::smallestLargerEqual(v, 5); REQUIRE(res == 3);
    res = Util::smallestLargerEqual(v, 8); REQUIRE(res == 5);
    res = Util::smallestLargerEqual(v, 12); REQUIRE(res == 6);
    res = Util::smallestLargerEqual(v, 11); REQUIRE(res == 6);
    res = Util::smallestLargerEqual(v, 13); REQUIRE(res == -1);
}

TEST_CASE("reverse string", "[valgrind][weight=1]") {
    vector<string> tests   = {"ABCDEFG", "", "A", "AB", "ABC", "Hello World!"};
    vector<string> answers = {"GFEDCBA", "", "A", "BA", "CBA", "!dlroW olleH"};

    for (unsigned i=0; i<tests.size(); ++i) {
        string test = tests[i];
        Util::reverseString(test);
        REQUIRE(test == answers[i]);
    }
}