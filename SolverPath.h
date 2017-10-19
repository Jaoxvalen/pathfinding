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

    
    /*
    Node* searchMinimal(vector<Node*> &lsOpen,  map< Node*, double > &G,  map< Node*, double > &H, map< Node*, bool > isClose)
    {
        double dist=10e10;
        Node* ret=NULL;
        for(int i=0; i<lsOpen.size(); i++)
        {
            if(!isClose[lsOpen[i]])
            if(dist>G[lsOpen[i]]+H[lsOpen[i]])
            {
                dist=G[lsOpen[i]]+H[lsOpen[i]];
                ret=lsOpen[i];
            }
        }
        return ret;
    }
     */
    
    
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
    /*------------*/
    /*vector<Node*> aStarJaox1( CGraph<Place, double> *mGraph,Node* start, Node* end, double &distPath, bool &isPath)
    {
        vector<Node*> lsOpen;
        map< Node*, Node* > parents;
        map< Node*, double > G,H;
        map< Node*, bool > isOpen;
        map< Node*, bool > isClose;
        vector<Node*> lsPath;
        
        isPath=true;
        if(start->edges.size()==0 || end->edges.size()==0)
        {
            isPath=false;
            return lsPath;
        }
        
        
        for(int i=0; i<mGraph->nodes.size(); i++)
        {
            isOpen[mGraph->nodes[i]]=false;
            isClose[mGraph->nodes[i]]=false;
        }
        
        lsOpen.push_back(start);
        Node* actual=start;
        isClose[actual]=true;
        while(actual!=end && lsOpen.size()>0)
        {
            for(int i=0; i<actual->edges.size(); i++)
            {
                //si no esta cerrada
                if(!isClose[actual->edges[i]->nodes[1]])
                {
                    if(!isOpen[actual->edges[i]->nodes[1]])
                    {
                        isOpen[actual->edges[i]->nodes[1]]=true;
                        parents[actual->edges[i]->nodes[1]]=actual;
                        lsOpen.push_back(actual->edges[i]->nodes[1]);
                         //calculamos G+H
                        G[actual->edges[i]->nodes[1]]=distance(actual->edges[i]->nodes[1], actual);
                        H[actual->edges[i]->nodes[1]]=distance(actual->edges[i]->nodes[1], end);
                    }
                    else
                    {
                        //¿es posible mejorar la distancia?
                        double dist=distance(actual->edges[i]->nodes[1], actual);
                        if(dist<G[actual->edges[i]->nodes[1]])
                        {
                            G[actual->edges[i]->nodes[1]]=dist;
                            parents[actual->edges[i]->nodes[1]]=actual;
                        }
                    }
                }
            }
            //elegimos al mas cercano de la lista abierta
            actual=searchMinimal(lsOpen,G,H, isClose);
            isClose[actual]=true;
        }
        
        Node* n = end;
        while(n != start){
            lsPath.push_back(n);
            n = parents[n];
        }
        lsPath.push_back(start);
        
        distPath=G[end];
        
        return lsPath;
    }*/


    /*vector<Node*> aStar( CGraph<Place, double> *mGraph,Node* start, Node* end){
        
        map< Node*, double > distH,distW; 
        map< Node*, Node* > parents;
        map< Node*, bool > visit;
        vector<Node*> lsPath;
        
        for(int i=0;i<mGraph->nodes.size();i++){
            distH[ mGraph->nodes[i] ] = -1;
            distW[ mGraph->nodes[i] ] = 10000;
            visit[ mGraph->nodes[i] ] = false;
        }
        
        double xn = end->data.x;
        double yn = end->data.y;
        double xo = start->data.x;
        double yo = start->data.y;
        
        int q = start->id;        
        
        distW[start] = 0;
        distH[start] = sqrt(pow(xo-xn,2)+pow(yo-yn,2));        
        visit[start] = true;
        
        int dist = distW[start] + distH[start];
        
        priority_queue< iPair, vector<iPair>, greater<iPair> > pq;
    
        pq.push( make_pair(dist, start) );
                
        Node* fin;
        Node* ini;
        do{                            
            ini = pq.top().second;
            pq.pop();
            visit[ini] = true;
            
            auto oEdges = mGraph->nodes[ini->id]->edges;  
            for(int i=0;i<oEdges.size();i++){                               
                fin = oEdges[i]->nodes[1];
                
                double x=fin->data.x;
                double y=fin->data.y;
                
                if( distH[fin] == -1 ){
                    distH[fin] = sqrt(pow(x-xn,2)+pow(y-yn,2));
                }
                
                if( distW[fin] > distW[ini] + oEdges[i]->data && !visit[fin] ){
                    distW[fin] = distW[ini] + oEdges[i]->data;
                    pq.push( make_pair( distW[fin]+distH[fin],fin) );
                    parents[fin] = ini;                    
                }
                if(fin->id==end->id) break;
                                            
            }
    
        }while( fin->id != end->id );
        
        Node* n = end;
        while(n != start){
            lsPath.push_back(n);
            n = parents[n];
        }
        lsPath.push_back(start);
        return lsPath;
        
    }*/
};