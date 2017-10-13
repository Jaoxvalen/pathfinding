
#pragma once
#include "CGraph.h"
#include "Utils.h"
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
        bool flag = false;
        
        Utils::getWord(in,line);
        if( line == "P"){
            Utils::getWord(in,line);      
            int nNodes = stoi(line.c_str());
            
            for(int i=0;i< nNodes;i++){
                double x,y;
                x = Utils::getWord(in,line);
                y = Utils::getWord(in,line);
                Place oPlace(x,y,i);
                graph.insertNode(oPlace);
                
            }
            
        }
        Utils::getWord(in,line);
        if( line == "Edges"){
            Utils::getWord(in,line);      
            int nEdges = stoi(line.c_str());            
            for(int i=0;i< nEdges;i++){
                int to,from;
                to = Utils::getWord(in,line);
                from = Utils::getWord(in,line);
                graph.insertEdge(graph.nodes[from],graph.nodes[to],false);
            }        
        }
    }
}