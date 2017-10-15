#pragma once
#include "Drawer.h"
#include "CGraph.h"
#include "Place.h"
#include "InputFile.h"
#include "Segmentation.h"

#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace visual;
using namespace DS;
using namespace std;

class Context
{
    Drawer mDrawer;
    CGraph<Place, double>* mGraph;
    int kSegments;

public:


    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef CGAL::Triangulation_vertex_base_with_info_2< CGraph<Place,double>::Node*, K> Vb;
    typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
    typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;
    typedef K::Point_2 PointCGAL;
    Delaunay dt;

    Context()
    {
        mGraph=new CGraph<Place, double>();
    }
        
    void loadGraph(string path)
    {
        InputFile ifManager;
        ifManager.readInput(path, mGraph);
    }
    void generatedGraph(string path, int numberOfNodes)
    {
        
        Utils::initialize_randomness(-1);
        int x, y;
        vector<pair<PointCGAL, CGraph<Place, double>::Node*> > pointsToTriangule;
        for(int i = 0; i < numberOfNodes; i++) {
            Place data;
            data.x = Utils::randint(0, WIDTH);
            data.y = Utils::randint(0, HEIGHT);
            CGraph<Place, double>::Node* oNode;
            oNode = mGraph->insertNode(data);
            oNode->data.id = i;
            
            
            pointsToTriangule.push_back(make_pair(PointCGAL(data.x, data.y), oNode));
        }
        // delaunay triangulation
        dt.insert(pointsToTriangule.begin(), pointsToTriangule.end());

        // insertamos los vertices
        for(Delaunay::Finite_edges_iterator it = dt.finite_edges_begin(); it != dt.finite_edges_end(); ++it) {
            CGraph<Place, double>::Node* nodo1 = it->first->vertex((it->second + 1) % 3)->info();
            CGraph<Place, double>::Node* nodo2 = it->first->vertex((it->second + 2) % 3)->info();
            double distance =
                sqrt(pow((nodo1->data.x - nodo2->data.x), 2) + pow((nodo1->data.y - nodo2->data.y), 2));
            mGraph->insertEdge(nodo1, nodo2, distance, true);
        }
        InputFile ifManager;
        ifManager.saveGraph(path, mGraph);
        
    }
    
    void SegmentGraph(int k)
    {
        kSegments=k;
        Segmentation oSegmentationManager;
        oSegmentationManager.kmeans(mGraph,k,1);
    }
    
    void drawGraph()
    {
        if(mGraph)
        for(int q = 0; q < mGraph->nodes.size(); q++) {
            auto oEdges = mGraph->nodes[q]->edges;
            
            for(int p = 0; p < oEdges.size(); p++) {
                double x1=oEdges[p]->nodes[0]->data.x;
                double y1=oEdges[p]->nodes[0]->data.y;
                double x2=oEdges[p]->nodes[1]->data.x;
                double y2=oEdges[p]->nodes[1]->data.y;
                mDrawer.line(x1, y1, x2, y2, new Color(1.0, 1.0, 1.0, 1.0));
            }
            
            
            /*int nIdCluster=mGraph->nodes[q]->data.idCluster;
            vector<Color*> tColor={
                {new Color(1.0, 0.0, 0.0, 1.0)},
                {new Color(0.0, 1.0, 0.0, 1.0)},
                {new Color(0.0, 0.0, 1.0, 1.0)},
                {new Color(1.0, 1.0, 0.0, 1.0)},
                {new Color(0.0, 1.0, 1.0, 1.0)},
                {new Color(1.0, 0.0, 1.0, 1.0)},
                {new Color(0.53, 0.12, 0.47, 1.0)},
                {new Color(1.0, 0.43, 0.78, 1.0)},
                {new Color(0.89, 0.47, 0.20, 1.0)},
                {new Color(0.52, 0.39, 0.39, 1.0)}
            };*/
            
            mDrawer.circFill(mGraph->nodes[q]->data.x,mGraph->nodes[q]->data.y,2,new Color(1.0,0.0,0.0,1.0));
            
            
        }
    }
};