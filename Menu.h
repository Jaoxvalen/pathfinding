#pragma once
#include <iostream>
#include <string>
#include <glob.h>
#include <stdexcept>


#define _MAIN 0
#define _LOADGRAPH 1
#define _LOADEDGRAPH 2
#define _LOADPRECALC 3
#define _LOADEDPRECALC 4
#define _FINDPATH 5


using namespace std;

class Menu
{
public:
    bool isPainted=false;
    Context* mContext;
    int status=_MAIN;
    string namePreSolver;
    Menu(Context* _mContext)
    {
        mContext=_mContext;
    }
    void main()
    {
        //MENU PRINCIPAL
        if(isPainted)
        {
            mContext->drawGraph();
        }
        if(status==_MAIN)
        {
            showMain();
        }
        else if(status==_LOADGRAPH)
        {
            showLoadGraphOptions();
        }
        else if(status==_LOADEDGRAPH)
        {
            showLoadedGraphOptions();
        }
        else if(status==_LOADPRECALC)
        {
            showLoadPrecalcOptions();
        }
        else if(status==_LOADEDPRECALC)
        {
            showLoadedPrecalcOptions();
        }
        else if(status==_FINDPATH)
        {
            findPath();
        }
    }
    string getDir()
    {
        string dir;
        cout<<"Ingrese la ruta: ";
        cin>>dir;
        return dir;
    }
    string getDir(string txt)
    {
        string dir;
        cout<<txt;
        cin>>dir;
        return dir;
    }
    
    void showMain()
    {
        string o="2";
        while(o!="1" && o!="2" && o!="3")
        {
            //system("clear");
            cout<<"Elija una opcion: "<<endl;
            cout<<"1.Cargar grafo"<<endl;
            cout<<"2.Cargar Precalculo"<<endl;
            cout<<"3.Salir"<<endl;
            cout<<"Opcion: "; 
            //cin>>o;
        }
        if(o=="1") 
        {
            status=_LOADGRAPH;
        }
        else if(o=="2")
        {
            status=_LOADPRECALC;
        }
        else if(o=="3")
        {
            exit(0);
        }
    }
    void showLoadGraphOptions()
    {
        string ruta=getDir();
        if(mContext->loadGraph(ruta))
        {
            cout<<"Se ha cargado el grafo"<<endl;
            status=_LOADEDGRAPH;
        }
        else
        {
            cout<<"La ruta no existe"<<endl;
            status=_MAIN;
        }
    }
    void showLoadedGraphOptions()
    {
        string o="1";
        
        while(o!="1" && o!="2" && o!="3" && o!="4")
        {
            //system("clear");
            cout<<"Elija una opcion: "<<endl;
            cout<<"1.Dibujar el grafo"<<endl;
            cout<<"2.Guardar precalculo"<<endl;
            cout<<"3.volver"<<endl;
            cout<<"Opcion: "; 
            //cin>>o;
        }
        if(o=="1") 
        {
            cout << "CARAJOOOOOOOOOOOOOOOO"<<endl; 
            isPainted=true;           
            mContext->drawGraph();
        }
        else if(o=="2")
        {
            mContext->preSolverGraph(getDir());
            status=_MAIN;
        }
        else if(o=="3")
        {
            status=_MAIN;
        }
    }
    void showLoadPrecalcOptions()
    {
        cout<<"Precalculos disponibles:"<<endl;
        string s = "../solutions/*";
        glob_t glob_result;
        glob(s.c_str(),GLOB_TILDE,NULL,&glob_result);
        if(glob_result.gl_pathc==0)
        {
            cout<<"No hay archivos de precalculo"<<endl;
            status=_MAIN;
            return;
        }
        for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
          cout << glob_result.gl_pathv[i] << endl;
        }

        string name="joao";//getDir("Elija el nombre: ");
        if(mContext->loadPresolver(name))
        {
            namePreSolver=name;
            status=_LOADEDPRECALC;
        }
        else
        {
            cout<<"El nombre no existe"<<endl;
            status=_MAIN;
        }
        
    }
    void showLoadedPrecalcOptions()
    {
        string o="4";
        while(o!="1" && o!="2" && o!="3" && o!="4")
        {
            //system("clear");
            cout<<"Elija una opcion: "<<endl;
            cout<<"1.Dibujar el grafo"<<endl;
            cout<<"2.Buscar rutas"<<endl;
            cout<<"3.volver"<<endl;
            cout<<"4.Richard"<<endl;
            cout<<"Opcion: "; 
            cin>>o;
        }
        if(o=="1") 
        {
            isPainted=true;
            mContext->drawGraph();
        }        
        else if(o=="2")
        {
            status=_FINDPATH;
        }
        else if(o=="3")
        {
            status=_MAIN;
        }
        else if(o=="4")
        {
            int i;
            cout<<"ingrese segmento: ";
            cin>>i;
            int cant=mContext->calcularContorno(i);
            cout<<cant<<endl;
        }
    }
    void findPath()
    {
        int from, to;
        string sFrom=getDir("Nodo de origen: ");
        try {
            from = stoi(sFrom);
        }
        catch(std::invalid_argument& e){
            cout<<"debe ingresar solo numeros"<<endl;
            return;
        }
        
        string sTo=getDir("Nodo de destino: ");
        try {
            to = stoi(sTo);
        }
        catch(std::invalid_argument& e){
            cout<<"debe ingresar solo numeros"<<endl;
            return;
        }
        mContext->findPath(from,to,namePreSolver);
        mContext->drawPath();
        
        status=_LOADEDPRECALC;
        
    }
};