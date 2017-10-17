#pragma once
#include "CGraph.h"
#include "CEdge.h"
#include "CNode.h"
#include "Place.h"
#include "Utils.h"
#include "SolverPath.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;
using namespace DS;

class PreSolver
{
public:
    typedef CGraph<Place,double>::Node Node;
    void calculatePathSegments(CGraph<Place,double>* oGraph, int k, string file)
    {
        
        ofstream fpath(file.append("_path.txt"));
        //segmentamos el grafo
        Segmentation oSegment;
        vector<vector<Node*> > lsSegments=oSegment.segmentGrapht(oGraph,k,1);
        //calculamos el path entre segmentos
        SolverPath oSolver;
        for(int i=0; i<k-1; i++)
        {
            for(int j=i+1;j<k;j++)
            {
                double distN;
                vector<Node*> path = oSolver.aStarJaox(oGraph,lsSegments[i][0],lsSegments[j][0],distN);
                fpath<<i<<":"<<j<<" ";
                for(int p=0; p<path.size(); p++)
                {
                    fpath<<path[p]->id<<" ";
                }
                fpath<<endl;
            }
        }
        fpath.close();
    }
};