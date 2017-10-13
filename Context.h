#pragma once
#include "Drawer.h"
#include "CGraph.h"
#include "Place.h"
#include "InputFile.h"

using namespace visual;
using namespace DS;
using namespace std;

class Context
{
    Drawer mDrawer;
    CGraph<Place, double>* mGraph;

public:
    Context()
    {
        mGraph=new CGraph<Place, double>();
    }
    

    
    void loadGraph(string path)
    {
        InputFile ifManager;
        ifManager.readInput(path, mGraph);
        
        /*
        for(int i=0; i<200; i++)
        {
            Place oPlace(Utils::randdouble(0,WIDTH),Utils::randdouble(0,HEIGHT),i);
            mGraph->insertNode(oPlace);
        }
        for(int i=0; i<mGraph->nodes.size()/4; i++)
        {
            if(Utils::randint(0,1)==1)
            {
                int ni=Utils::randint(0,mGraph->nodes.size()-1);
                int nj=Utils::randint(0,mGraph->nodes.size()-1);
                mGraph->insertEdge(mGraph->nodes[ni], mGraph->nodes[nj],0,false);
            }
        }*/
    }
    void drawGraph()
    {
        if(mGraph)
        for(int q = 0; q < mGraph->nodes.size(); q++) {
            auto oEdges = mGraph->nodes[q]->edges;
            mDrawer.circ(mGraph->nodes[q]->data.x,mGraph->nodes[q]->data.y,5,new Color(255, 0, 0, 255));
            for(int p = 0; p < oEdges.size(); p++) {
                double x1=oEdges[p]->nodes[0]->data.x;
                double y1=oEdges[p]->nodes[0]->data.y;
                double x2=oEdges[p]->nodes[1]->data.x;
                double y2=oEdges[p]->nodes[1]->data.y;
                mDrawer.line(x1, y1, x2, y2, new Color(255, 0, 0, 255));
            }
        }
    }
};