#pragma once
#include "CGraph.h"
#include "Utils.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace DS;
using namespace std;

class InputFile{
    public:
    void readInput(string path,CGraph<Place,double>* graph){
        ifstream in(path.c_str());
        string s,line;
        double n;
        bool flag = false;
        
        Utils::getWord(in,line);
        if( line == "P"){
            Utils::getWord(in,line);      
            int nNodes = stoi(line.c_str());
            
            for(int i=0;i< nNodes;i++){
                double x,y;
                Utils::getWord(in,line);
                x = stod(line.c_str());
                Utils::getWord(in,line);
                y = stod(line.c_str());
                Place oPlace(x,y,i);
                graph->insertNode(oPlace);
                
            }
            
        }
        Utils::getWord(in,line);
        if( line == "Edges"){
            Utils::getWord(in,line);      
            int nEdges = stoi(line.c_str());            
            for(int i=0;i< nEdges;i++){
                int to,from;
                Utils::getWord(in,line);
                to = stoi(line.c_str());
                Utils::getWord(in,line);
                from = stoi(line.c_str());
                graph->insertEdge(graph->nodes[from],graph->nodes[to],0.0,false);
            }        
        }
    }
};