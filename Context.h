#pragma once
#include "Drawer.h"
#include "CGraph.h"
#include "Place.h"

using namespace visual;
using namespace DS;
using namespace std;

class Context
{
    Drawer mDrawer;
    CGraph<Place, double>* mGrahp;

public:
    void drawGraph()
    {
        for(int q = 0; q < mGrahp.nodes.size(); q++) {
            auto oEdges = nodes[q]->edges;
            mDrawer.circ(mGrahp.nodes[q]->data.x,mGrahp.nodes[q]->data.y,5,new Color(255, 0, 0, 255));
            for(int p = 0; p < oEdges.size(); p++) {
                
                //mDrawer.line(100, 100, 200, 200, new Color(255, 0, 0, 255));
            }
        }
    }
};