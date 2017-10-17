#pragma once
#include "CGraph.h"
#include "Place.h"
#include "Utils.h"
#include "SolverPath.h"
#include <vector>
#include <queue>

using namespace std;
using namespace DS;

class Segmentation
{
public:
    typedef CGraph<Place,double>::Node Node;
    vector<Node*> lsIsolateds;
    bool existingNode(vector<Node*> oNodes, Node* oNode)
    {
        for(int i=0; i<oNodes.size(); i++)
        {
            if(oNodes[i]==oNode)
            {
                return true;
            }
        }
        return false;
    }
    double distancePath(vector<Node*> oPath)
    {
        if(oPath.size()==0) return -1;
        double nResult=0;
        for(int i=1; i<oPath.size(); i++)
        {
            nResult+=distance(oPath[i-1],oPath[i]);
        }
        return nResult;
    }
    double distance(Node* oNode1, Node* oNode2)
    {
         return sqrt(pow((oNode1->data.x - oNode2->data.x), 2) + pow((oNode1->data.y - oNode2->data.y), 2));
    }
    
    vector<vector<Node*> > segmentGrapht(CGraph<Place,double>* oGraph, int k, double nDelta)
    {
        //aplicamos kMeans
        vector<vector<Node* > > segments=kmeans(oGraph,k,nDelta);
        //buscamos los no conexos en su segmento
        for(int s=0; s<k;s++)
        {
            searchConexion(segments[s][0],s,segments[s]);
        }
        //aplicamos Astar a los aislados contra los otros centroides y asignamos al más cercano
        SolverPath oSolver;
        for(int i=0; i<lsIsolateds.size();i++)
        {
            double dist=-1;
            int kIndex=-1;
            for(int s=0; s<k;s++)
            {
                if(s!=lsIsolateds[i]->idCluster)
                {
                    vector<Node*> path=oSolver.aStar(oGraph,segments[s][0],lsIsolateds[i]);
                    double distN=distancePath(path);
                    if(dist>distN || dist==-1)
                    {
                        dist=distN;
                        kIndex=s;
                    }
                }
            }
            lsIsolateds[i]->idCluster=kIndex;
        }
        return segments;
    }
    void searchConexion(Node* origin, int nSegment, vector<Node*> lsSegments)
    {
        
        vector<Node*> conex;
        queue<Node*> prio;
        prio.push(origin);
        while(prio.size()>0)
        {
            //agarramos el ultimo
            Node* actual=prio.front();
            //agragamos los adyacentes no visitados
            int nCount=0;
            for(int i=0; i<actual->edges.size(); i++)
            {
                if  (   
                        (actual->edges.size()>0)&&
                        (actual->edges[i]->nodes[1]->idCluster==nSegment) && 
                        !(actual->edges[i]->nodes[1]->isVisit)
                    )
                {
                    prio.push(actual->edges[i]->nodes[1]);
                    actual->edges[i]->nodes[1]->isVisit=true;
                    nCount++;
                }
            }
            if(nCount==0)
            {
                conex.push_back(actual);
                prio.pop();
            }
        }
        //los que tienen isVisit "false" son los que sobran y deben ser reasignados a otro segmento
        for(int i=0; i<lsSegments.size();i++)
        {
            if(!lsSegments[i]->isVisit && lsSegments[i]->edges.size()>0)
            {
                lsIsolateds.push_back(lsSegments[i]);
            }
        }
    }
    
    vector<vector<Node* > > kmeans(CGraph<Place,double>* oGraph, int k, double nDelta)
    {
        //seleccionar k nodos aleatorios
        vector<Node*> oClusters;
        int nRandom=Utils::randint(0,oGraph->nodes.size()-1);
        Node* oselectedNode=oGraph->nodes[nRandom];
        while(oClusters.size()<k)
        {
            if(!existingNode(oClusters,oselectedNode))
            {
                oClusters.push_back(oselectedNode);
            }
            nRandom=Utils::randint(0,oGraph->nodes.size()-1);
            oselectedNode=oGraph->nodes[nRandom];
        }
        int nNodes=oGraph->nodes.size();
        //asignamos el nodo al cluster mas cercano en distancia
        vector<vector<Node* > >lsClusterAsig(k);
        int nConvergeNum=k;
        while(nConvergeNum>0)
        {
            nConvergeNum=k;
            for(int i=0; i<k; i++)
            {
                lsClusterAsig[i].clear();
            }
            for(int n=0; n<nNodes; n++)
            {
                double nDistance;
                double nDistanceOld=distance(oGraph->nodes[n],oClusters[0]);
                int nIndexCluster=0;
                for(int c=1; c<k; c++)
                {
                    nDistance=distance(oGraph->nodes[n],oClusters[c]);
                    if(nDistance<nDistanceOld)
                    {
                        nDistanceOld=nDistance;
                        nIndexCluster=c;
                    }
                }
                lsClusterAsig[nIndexCluster].push_back(oGraph->nodes[n]);
                oGraph->nodes[n]->idCluster=nIndexCluster;
            }
            //recalculamos los cluster con las medias de los nuevos grupos formados
            for(int c=0; c<k; c++)
            {
                Place oPlaceMedia(0.0,0.0);
                for(int ca=0; ca<lsClusterAsig[c].size();ca++)
                {
                    Node* oNodeEval=lsClusterAsig[c][ca];
                    oPlaceMedia.x+=lsClusterAsig[c][ca]->data.x;
                    oPlaceMedia.y+=lsClusterAsig[c][ca]->data.y;
                }
                oPlaceMedia.x=oPlaceMedia.x/lsClusterAsig[c].size();
                oPlaceMedia.y=oPlaceMedia.y/lsClusterAsig[c].size();
                Node* oClusterNew=new Node(oPlaceMedia,-1);
                //calculamos la convergencia para detener el algoritmo
                if(distance(oClusterNew,oClusters[c])<nDelta)
                {
                    nConvergeNum--;
                }
                //asignamos el nuevo cluster media
                oClusters[c]=oClusterNew;
            }
        }
        return lsClusterAsig;
    }
};