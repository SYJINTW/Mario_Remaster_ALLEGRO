#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>

#include <allegro5/allegro.h>

#include "global.h"
#include "rectangle.h"

class Block
{
public:
    //ALLEGRO_BITMAP *image;
    ALLEGRO_BITMAP * imageArr[2];

    int dayOrNightFlag;

    // for height width
    int imageHeight;
    int imageWidth;
    float scaledHeight;
    float scaledWidth;
    float height;
    float width;
    Rectangle *box;

    // position
    std::pair<float, float> xRange;
    float y;

    // for recognize type
    ObjectType objectType = BLOCK;


    Block(std::pair<int, int> _xRange, int _y)
    {
        xRange = _xRange;
        y = _y;
        imageArr[0] = al_load_bitmap("res/images/block.png");
        imageArr[1] = al_load_bitmap("res/images/gray-block.png");
        imageHeight = al_get_bitmap_height(imageArr[0]);
        imageWidth = al_get_bitmap_width(imageArr[0]);
        scaledHeight = imageHeight * 2;
        scaledWidth = imageWidth * 2;
        height = y;
        width = xRange.second - xRange.first;
        box = new Rectangle(xRange.first, y, width, height);
    };

    void init(int _dayOrNightFlag)
    {
        dayOrNightFlag = _dayOrNightFlag;
    }


    void draw()
    {
        for (int i = box->left; i < box->right; i += scaledWidth)
            al_draw_scaled_bitmap(imageArr[dayOrNightFlag], 0, 0, imageWidth, imageHeight, i, box->top, scaledWidth, scaledHeight, 0);
    }
};

#endif // BRICK_H
