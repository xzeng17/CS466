#pragma once

#include <vector>
using std::vector;

struct Util {
    int static binarySearch(const vector<int>&v, int t) {
        if (v.size() < 1) return -1;
        int l = 0, r = (int)v.size()-1;
        while (r >= l) {
            int m = l+(r-l)/2;
            if (v[m] == t) return m;
            if (v[m] < t) {
                l = m+1;
            } else {
                r = m-1;
            }
        }
        return -1;
    }

    int static smallestLargerEqual(const vector<int>&v, int t) {
        if (v.size() < 1) return -1;
        if (t>v[v.size()-1]) return -1;

        int l=0, r=(int)v.size()-1;
        while (r>=l) {
            int m = l+(r-l)/2;
            if (v[m] == t) return m;
            if (v[m] < t) {
                l = m+1;
            } else {
                r = m-1;
            }
        }
        return l < (int) v.size() ? l : -1;
    }

    int static largestSmallerEqual(const vector<int>&v, int t) {
        if (v.size() < 1) return -1;
        if (t<v[0]) return -1;

        int l=0, r=(int)v.size()-1;
        while (r>=l) {
            int m = l+(r-l)/2;
            if (v[m] == t) return m;
            if (v[m] < t) {
                l = m+1;
            } else {
                r = m-1;
            }
        }
        return r;
    }
};