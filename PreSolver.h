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
    
    PreSolver()
    {
        mGraph=new CGraph<Place, double>();
    }
    
    void loadPreCalculated(string file)
    {
        ifstream in(file.c_str());
        string s,line;
        double n;
        bool flag = false;
        
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
        isLoad=true;
    }
    
    vector<Node*> findSegments(int from, int to, string fileDir)
    {
        vector<Node*> lsPathSegment;
        if(isLoad)
        {
            from=mGraph->nodes[from]->idCluster;
            to=mGraph->nodes[to]->idCluster;
            stringstream ss;
            ss << min(from,to)<<":"<< max(from,to);
            string sIndex = ss.str();
            
            ifstream f(fileDir.c_str());
            string s;
            while (s.substr(0,sIndex.size())!=sIndex)
            {
                getline(f, s);
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
        //segmentamos el grafo
        Segmentation oSegment;
        vector<vector<Node*> > lsSegments=oSegment.segmentGrapht(oGraph,k,1);
        
        
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
                vector<Node*> path = oSolver.aStarJaox(oGraph,lsSegments[i][0],lsSegments[j][0],distN);
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