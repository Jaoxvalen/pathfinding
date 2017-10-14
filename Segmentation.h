#pragma once
#include "CGraph.h"
#include "Place.h"
#include "Utils.h"
#include <vector>

using namespace std;
using namespace DS;

class Segmentation
{
public:
    typedef CGraph<Place,double>::Node Node;
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
    double distance(Node* oNode1, Node* oNode2)
    {
         return sqrt(pow((oNode1->data.x - oNode2->data.x), 2) + pow((oNode1->data.y - oNode2->data.y), 2));
    }
    void kmeans(CGraph<Place,double>* oGraph, int k, double nDelta)
    {
        //seleccionar k nodos aleatorios
        vector<Node*> oClusters;
        int nRandom=Utils::randint(0,oGraph->nodes.size());
        Node* oselectedNode=oGraph->nodes[nRandom];
        while(!existingNode(oClusters,oselectedNode) && oClusters.size()<k)
        {
            oClusters.push_back(oselectedNode);
            nRandom=Utils::randint(0,oGraph->nodes.size());
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
                oGraph->nodes[n]->data.idCluster=nIndexCluster;
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
                Node* oClusterNew=new Node(oPlaceMedia);
                //calculamos la convergencia para detener el algoritmo
                if(distance(oClusterNew,oClusters[c])<nDelta)
                {
                    nConvergeNum--;
                }
                //asignamos el nuevo cluster media
                oClusters[c]=oClusterNew;
            }
        }
        
    }
};