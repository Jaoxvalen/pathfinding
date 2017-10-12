#pragma once
#include "CGraph.h"
#include <string>
#include <fstream>

using namespace DS;

class InputFile{
    public:
    void readInput(string path,CGraph<Place,float> graph){
        ifstream in;
        in.open(path);
        string s,line;
        double n;
        while(getline(in,line)){
            
        }
    }
}