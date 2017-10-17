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
        ofstream outfile(file);
        //segmentamos el grafo
        Segmentation oSegment;
        vector<vector<Node*> > lsSegments=oSegment.segmentGrapht(oGraph,10,1);
        //calculamos el path entre segmentos
        /*SolverPath oSolver;
        for(int i=0; i<k-1; i++)
        {
            for(int j=i+1;j<k;j++)
            {
                vector<Node*> path = oSolver.aStar(oGraph,lsSegments[i][0],lsSegments[j][0]);
                outfile<<i<<":"<<j<<" ";
                for(int p=0; p<path.size(); p++)
                {
                    outfile<<path[p]->id<<" ";
                }
                outfile<<endl;
            }
        }
        */
    }
};