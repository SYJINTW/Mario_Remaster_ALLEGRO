#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    float left, right, top, bottom;
    float width, height;

    Rectangle(float x, float y, float w, float h);
    enum Edge {Top = 1, Bottom = 2, Left = 4, Right = 8, None = 0};
    void update(float x, float y); //update with (x,y)
    void updateWithTop(float _top); //update with pos of top
    void updateWithBottom(float _bottom); //update with pos of bottom
    void updateWithLeft(float _left); //update with pos of left
    void updateWithRight(float _right); //update with pos of right
    int intersect(Rectangle *target); // check if the object is intersect with target
};

#endif // RECTANGLE_H

