#pragma once
#include "CGraph.h"
#include "CEdge.h"
#include "CNode.h"
#include "Place.h"
#include "Utils.h"
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
using namespace DS;

class SolverPath
{
public:
    typedef CGraph<Place, double >::Node Node;
    typedef pair<double, Node*> iPair;

    double distance(Node* oNode1, Node* oNode2)
    {
         return sqrt(pow((oNode1->data.x - oNode2->data.x), 2) + pow((oNode1->data.y - oNode2->data.y), 2));
    }
    
    vector<Node*> aStarJaox( CGraph<Place, double> *mGraph,Node* start, Node* end, double &distPath, bool &isPath){
        
        vector<Node*> lsPath;
        unordered_map< Node*, double > distH,distW; 
        unordered_map< Node*, Node* > parents;
        unordered_map< Node*, bool > visit;
        
        isPath=true;
        if(start->edges.size()==0 || end->edges.size()==0)
        {
            isPath=false;
            return lsPath;
        }
        
        if(start==end)
        {
            lsPath.push_back(start);
            return lsPath;
        }
        
        for(int i=0;i<mGraph->nodes.size();i++){
            distH[ mGraph->nodes[i] ] = -1;
            distW[ mGraph->nodes[i] ] = 1000000;
            visit[ mGraph->nodes[i] ] = false;
        }
        
        double xn = end->data.x;
        double yn = end->data.y;
        double xo = start->data.x;
        double yo = start->data.y;
             
        
        distW[start] = 0;
        distH[start] = sqrt(pow(xo-xn,2)+pow(yo-yn,2));        
        visit[start] = true;
     
        
        int dist = distW[start] + distH[start];
        
        priority_queue< iPair, vector<iPair>, greater<iPair> > pq;
    
        pq.push( make_pair(dist, start) );
                
        Node* fin = start;
        Node* ini = start;
        
        bool flag = true;
        //do{                            
        while( flag )
        {
            ini = pq.top().second;
            pq.pop();            
            visit[ini] = true;
            
            
            auto oEdges = mGraph->nodes[ini->id]->edges;  
            
            for(int i=0;i<oEdges.size();i++){   
                fin = oEdges[i]->nodes[1];
                if( !visit[fin] ){                    
                    double x=fin->data.x;
                    double y=fin->data.y;
                    if( distH[fin] == -1 ){
                        distH[fin] = sqrt(pow(x-xn,2)+pow(y-yn,2));
                    }
                    if( distW[fin] > distW[ini] + oEdges[i]->data ){
                        distW[fin] = distW[ini] + oEdges[i]->data;
                        pq.push( make_pair(distH[fin]+ distW[fin] ,fin) );
                        parents[fin]=ini;   
                    }
                    
                    if( fin->id == end->id ){
                        flag = false;
                        //cout << "AAAAAA"<< endl;
                    }                
                }                           
            }

        }

        
        distPath= distW[end];
        Node* n = end;
        while(n != start){
            lsPath.push_back(n);
            n = parents[n];
        }
        lsPath.push_back(start);
    
        return lsPath;
        
    }

};