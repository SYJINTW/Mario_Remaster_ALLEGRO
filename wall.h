#ifndef WALL_H
#define WALL_H

#include <iostream>

#include <allegro5/allegro.h>

#include "global.h"
#include "rectangle.h"

class Wall
{
public:
    //ALLEGRO_BITMAP *wall_image;
    ALLEGRO_BITMAP * imageArr[2];

    int dayOrNightFlag;

    // for height width
    int imageHeight;
    int imageWidth;
    float scaledHeight;
    float scaledWidth;
    float wallHeight;
    float wallWidth;
    Rectangle *box;

    // position
    std::pair<float, float> xRange;
    float y;

    // for recognize type
    ObjectType objectType = WALL;


    Wall(std::pair<int, int> _xRange, int _y)
    {
        xRange = _xRange;
        y = _y;
        imageArr[0] = al_load_bitmap("res/images/wall.png");
        imageArr[1] = al_load_bitmap("res/images/gray-wall.png");
        imageHeight = al_get_bitmap_height(imageArr[0]);
        imageWidth = al_get_bitmap_width(imageArr[0]);
        scaledHeight = imageHeight * 2;
        scaledWidth = imageWidth * 2;
        wallHeight = y;
        wallWidth = xRange.second - xRange.first;
        box = new Rectangle(xRange.first, y, wallWidth, wallHeight);
    };

    void init(int _dayOrNightFlag)
    {  
        dayOrNightFlag = _dayOrNightFlag;
    }

    void draw()
    {
        for (int i = box->left; i < box->right; i += scaledWidth)
            for (int j = y; j < y + wallHeight; j += scaledHeight)
                al_draw_scaled_bitmap(imageArr[dayOrNightFlag], 0, 0, imageWidth, imageHeight, i, j, scaledWidth, scaledHeight, 0);
    }
};

#endif // WALL_H
