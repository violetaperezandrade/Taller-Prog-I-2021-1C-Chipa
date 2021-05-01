#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate{
private:
    int xAxis, yAxis;

public:
    Coordinate();
    Coordinate(int x, int y);
    void addX(int xValue);
    void addY(int yValue);
    //double distance(Coordinate coord);
    ~Coordinate();

};

#endif //COORDINATE_H