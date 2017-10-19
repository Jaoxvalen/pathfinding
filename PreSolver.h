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
#include "CGraph.h"
#include <algorithm>
#include <sstream>

using namespace std;
using namespace DS;

class PreSolver
{
private:
    bool isLoad=false;
public:
    typedef CGraph<Place,double>::Node Node;
    CGraph<Place, double>* mGraph;
    vector<int> idCentroids;
    PreSolver()
    {
        mGraph=new CGraph<Place, double>();
    }
    
    bool loadPreCalculated(string file)
    {
        string sSegments=file;
        string sCentroids=file;
        
        ifstream in(sSegments.append("_segment.txt").c_str());
        if(!in.is_open()) return false;
        
        ifstream inCentroids(sCentroids.append("_centroids.txt").c_str());
        if(!inCentroids.is_open()) return false;
        
        string s,line;
        double n;
        //bool flag = false;
        
        //cargamos los centroids id
        Utils::getWord(inCentroids,line);
        int nCent=stoi(line.c_str());
        for(int i=0; i<nCent; i++)
        {
            Utils::getWord(inCentroids,line);
            n=stoi(line.c_str());
            idCentroids.push_back(n);
        }
        
        //cargamos el grafo
        Utils::getWord(in,line);
        if( line == "POINTS"){
            Utils::getWord(in,line);      
            int nNodes = stoi(line.c_str());
            
            for(int i=0;i< nNodes;i++){
                double x,y, idClus;
                Utils::getWord(in,line);
                x = stod(line.c_str());
                Utils::getWord(in,line);
                y = stod(line.c_str());
                Place oPlace(x,y);
                Utils::getWord(in,line);
                idClus = stoi(line.c_str());
                mGraph->insertNode(oPlace, i,idClus);
                
            }
            
        }
        Utils::getWord(in,line);
        if( line == "EDGES"){
            Utils::getWord(in,line);      
            int nEdges = stoi(line.c_str());            
            for(int i=0;i< nEdges;i++){
                int to,from;
                Utils::getWord(in,line);
                to = stoi(line.c_str());
                Utils::getWord(in,line);
                from = stoi(line.c_str());
                mGraph->insertEdge(mGraph->nodes[from],mGraph->nodes[to],0.0,true);
            }        
        }
        //cargamos los idCentroides
        
        
        isLoad=true;
    }
    
    vector<Node*> findSegments(int from, int to, string fileDir, bool &isPath)
    {
        isPath=true;
        vector<Node*> lsPathSegment;
        if(mGraph->nodes[from]->edges.size()==0 || mGraph->nodes[to]->edges.size()==0)
        {
            isPath=false;
            return lsPathSegment;
        }
        if(isLoad)
        {
            from=mGraph->nodes[from]->idCluster;
            to=mGraph->nodes[to]->idCluster;
            stringstream ss;
            ss << std::min(from,to)<<":"<< std::max(from,to);
            string sIndex = ss.str();
            
            ifstream f(fileDir.c_str());
            string s;
            string sComp;
            Utils::getFirstWordString(s,sComp);
            while (sComp!=sIndex)
            {
                getline(f, s);
                Utils::getFirstWordString(s,sComp);
            }
            
            Utils::getWordString(s,sIndex);
            while (s.size()>0)
            {
                Utils::getWordString(s,sIndex);
                if(sIndex=="") break;
                int index=stoi(sIndex.c_str());
                lsPathSegment.push_back(mGraph->nodes[index]);
            }
            
        }
        else
        {
            cout<<"Debe cargar data precalculada primero"<<endl;
        }
        return lsPathSegment;
    }
    
    void savePreCalculated(CGraph<Place,double>* oGraph, int k, string file)
    {
        
        if(k==-1) k=oGraph->nodes.size()/200;
        
        string sSeg=file;
        string sPath=file;
        string sCentroids=file;
        //segmentamos el grafo
        Segmentation oSegment;
        vector<vector<Node*> > lsSegments=oSegment.segmentGrapht(oGraph,k,1);
        //GUARDAMOS LOS CENTROIDES POR SEGMENTO
        ofstream fCentroids(sCentroids.append("_centroids.txt"));
        fCentroids<<k<<endl;
        for(int i=0; i<k; i++)
        {
            fCentroids<<lsSegments[i][0]->id<<endl;
        }
        fCentroids.close();
        
        //GUARDAMOS EL GRAFO SEGMENTADO
        ofstream fgraph(sSeg.append("_segment.txt"));
        fgraph << "POINTS " <<oGraph->nodes.size()<<endl;
        for(int i=0; i<oGraph->nodes.size(); i++)
        {
            int nIdCluster=oGraph->nodes[i]->idCluster;
            if(nIdCluster<0 || nIdCluster>=k) nIdCluster=-1;
            fgraph<<oGraph->nodes[i]->data.x<<" "<<oGraph->nodes[i]->data.y<<" "<<nIdCluster<<endl;
        }
        fgraph << "EDGES " <<oGraph->nEdges<<endl;
        for(int i=0; i<oGraph->edgesLog.size(); i++)
        {
            fgraph<<oGraph->edgesLog[i].first<<" "<<oGraph->edgesLog[i].second<<endl;
        }
        fgraph.close();
        
        
        //GUARDAMOS LOS PATHS ENTRE SEGMENTOS
        ofstream fpath(sPath.append("_path.txt"));
        
        //calculamos el path entre segmentos
        SolverPath oSolver;
        for(int i=0; i<k-1; i++)
        {
            for(int j=i+1;j<k;j++)
            {
                cout<<"path"<<i<<","<<j<<endl;
                double distN;
                bool isPath;
                vector<Node*> path = oSolver.aStarJaox(oGraph,lsSegments[i][0],lsSegments[j][0],distN, isPath);
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