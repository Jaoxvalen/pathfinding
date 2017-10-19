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
    void saveGraph(string path,CGraph<Place,double>* graph)
    {
        ofstream outfile(path);
        outfile << "POINTS " <<graph->nodes.size()<<endl;
        for(int i=0; i<graph->nodes.size(); i++)
        {
            outfile<<graph->nodes[i]->data.x<<" "<<graph->nodes[i]->data.y<<endl;
        }
        outfile << "EDGES " <<graph->nEdges<<endl;
        for(int i=0; i<graph->edgesLog.size(); i++)
        {
            outfile<<graph->edgesLog[i].first<<" "<<graph->edgesLog[i].second<<endl;
        }
        outfile.close();
    }
    bool readInput(string path,CGraph<Place,double>* graph){
        ifstream in(path.c_str());
        if(!in.is_open()) return false;
        string s,line;
        double n;
        bool flag = false;
        
        Utils::getWord(in,line);
        if( line == "POINTS"){
            Utils::getWord(in,line);      
            int nNodes = stoi(line.c_str());
            
            for(int i=0;i< nNodes;i++){
                double x,y;
                Utils::getWord(in,line);
                x = stod(line.c_str());
                Utils::getWord(in,line);
                y = stod(line.c_str());
                Place oPlace(x,y);
                graph->insertNode(oPlace, i);
                
            }
            
        }
        Utils::getWord(in,line);
        if( line == "EDGES"){
            Utils::getWord(in,line);      
            int nEdges = stoi(line.c_str());            
            for(int i=0;i< nEdges;i++){
                int to,from;
                Utils::getWord(in,line);
                to = stoi(line.c_str());
                Utils::getWord(in,line);
                from = stoi(line.c_str());
                graph->insertEdge(graph->nodes[from],graph->nodes[to],0.0,true);
            }        
        }
        return true;
    }
};