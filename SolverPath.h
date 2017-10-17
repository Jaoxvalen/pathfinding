#pragma once
#include "CGraph.h"
#include "CEdge.h"
#include "CNode.h"
#include "Place.h"
#include "Utils.h"
#include <vector>
#include <map>
#include <queue>

using namespace std;
using namespace DS;

class SolverPath
{
public:
    typedef CGraph<Place, double >::Node Node;
    typedef pair<double, Node*> iPair;


    vector<Node*> aStar( CGraph<Place, double> *mGraph,Node* start, Node* end){
        
        map< Node*, double > distH,distW; 
        map< Node*, Node* > parents;
        
        vector<Node*> lsPath;
        for(int i=0;i<mGraph->nodes.size();i++){
            distH[ mGraph->nodes[i] ] = -1;
            distW[ mGraph->nodes[i] ] = 10000;
        }
        
        double xn = end->data.x;
        double yn = end->data.y;
        double xo = start->data.x;
        double yo = start->data.y;
        
        int q = start->id;        
        
        distW[start] = 0;
        distH[start] = sqrt(pow(xo-xn,2)+pow(yo-yn,2));        
        int dist = distW[start] + distH[start];
        
        priority_queue< iPair, vector<iPair>, greater<iPair> > pq;
    
        pq.push( make_pair(dist, start) );
                
        Node* fin;
        Node* ini;
        
        do{                            
            ini = pq.top().second;
            pq.pop();
            
            auto oEdges = mGraph->nodes[ini->id]->edges;  
            for(int i=0;i<oEdges.size();i++){               

                fin = oEdges[i]->nodes[1];
                
                double x=fin->data.x;
                double y=fin->data.y;
                
                if( distH[fin] == -1 ){
                    distH[fin] = sqrt(pow(x-xn,2)+pow(y-yn,2));
                }
                
                if( distW[fin] > distW[ini] + oEdges[i]->data ){
                    distW[fin] = distW[ini] + oEdges[i]->data;
                    pq.push( make_pair( distW[fin]+distH[fin],fin) );
                    parents[fin] = ini;                    
                }
                                            
            }
    
        }while( fin->id != end->id );
        
        Node* n = end;
        while(n != start){
            lsPath.push_back(n);
            n = parents[n];
        }
        lsPath.push_back(start);
        return lsPath;
        
    }
};