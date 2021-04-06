#pragma once

#include<string>
#include <fstream>
#include <istream>
#include <iostream>

using namespace std;

class Fileloader {
    public:
        Fileloader();
        Fileloader(const string& filename);
        virtual ~Fileloader();
        virtual string readLine();
        virtual void readAll();
        virtual bool hasNext();
        
    private:
        string filename_;
        ifstream file_;
        size_t totalByte_;
        virtual size_t getByte();
        void load();
};