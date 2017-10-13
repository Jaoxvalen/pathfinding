#pragma once
class Place{
    public:
    double x,y;
    int id,idSection;
    Place(double _x,double _y){
        x = _x;
        y = _y;        
    }  
    Place(double _x,double _y, int _id){
        x = _x;
        y = _y;
        id = _id;
    }    
}