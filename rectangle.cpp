#include "rectangle.h"

#include "iostream"

Rectangle::Rectangle(float x, float y, float w, float h)
{
    // (x,y) 是圖片的右上角
    left = x;
    top = y;
    right = x + w;
    bottom = y + h;
    width = w;
    height = h;
}

void
Rectangle::update(float x, float y)
{
    left = x;
    top = y;
    right = left + width;
    bottom = top + height;
}

void
Rectangle::updateWithTop(float _top) {
    top = _top;
    bottom = _top + height;
}

void
Rectangle::updateWithBottom(float _bottom) {
    bottom = _bottom;
    top = _bottom - height;
}

void
Rectangle::updateWithLeft(float _left) {
    left = _left;
    right = _left + width;
}

void
Rectangle::updateWithRight(float _right) {
    right = _right;
    left = _right - width;
}

int
Rectangle::intersect(Rectangle *target)
{
    // 利用二進位的方式去儲存每一個邊界是否有交集
    // 8|4|2|1|0
    // R|L|B|T|None

    int intersectEdge = Rectangle::None;
    if (!(this->right < target->left || this->top > target->bottom
        || this->left > target->right || this->bottom < target->top))
    {
        // 8: Right
        if (this->right >= target->left && this->left <= target->left)
            intersectEdge |= Rectangle::Right;
        // 4: Left
        if (this->left <= target->right && this->right >= target->right)
            intersectEdge |= Rectangle::Left;
        // 2: Bottom
        if (this->bottom >= target->top && this->top <= target->top)
            intersectEdge |= Rectangle::Bottom;
        // 1: Top
        if (this->top <= target->bottom && this->bottom >= target->bottom)
            intersectEdge |= Rectangle::Top;
    }

    /*
    // for debug
    if(intersectEdge)
        std::cout << "intersect number:" << intersectEdge <<"\n";
    */

    return intersectEdge;
}

