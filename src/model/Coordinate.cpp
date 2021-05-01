#include "Coordinate.h"

Coordinate::Coordinate() : xAxis(0),yAxis(0){}

Coordinate::Coordinate(int x, int y){
    this->xAxis = x;
    this->yAxis = y;
}

void addX(int xValue){
    this->xAxis += xValue;
}

void addY(int yValue){
    this->yAxis += yValue;
}

