#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>

#include <allegro5/allegro.h>

#include "global.h"
#include "rectangle.h"
#include "position.h"
#include "wall.h"
#include "brick.h"
#include "block.h"

class Map
{
    public:
        //std::vector<std::string, std::vector<float, float, float>> mapLoader; // [object_type][start_x][start_y][end_x]
        Wall* wall;

        Brick* brickA;
        Brick* brickB;

        Block* blockC;
        Block* blockD;
        Block* blockE;

        Brick* brickG;
        Brick* brickH;

        Block* blockI;
        Block* blockJ;

        Map()
        {
            //mapLoader.push_back("WALL", 0, 1104, 200);
            wall = new Wall({0-32,SCREEN_WIDTH+32}, SCREEN_HEIGHT-80);
            brickA = new Brick({0-32,100}, 100);
            brickB = new Brick({SCREEN_WIDTH-132,SCREEN_WIDTH+32}, 100);
            blockC = new Block({SCREEN_WIDTH_CENTER-200,SCREEN_WIDTH_CENTER+200}, 170);
            blockD = new Block({80,SCREEN_WIDTH_CENTER-300}, 270);
            blockE = new Block({SCREEN_WIDTH_CENTER+250,SCREEN_WIDTH - 96}, 270);

            brickG = new Brick({900, 1380}, 375);
            brickH = new Brick({-32,350}, 390);
            blockI = new Block({450,600}, 465);
            blockJ = new Block({600,1100}, 550);
        }

        void init(int _dayOrNightFlag)
        {
            wall->init(_dayOrNightFlag);

            brickA->init(_dayOrNightFlag);
            brickB->init(_dayOrNightFlag);

            blockC->init(_dayOrNightFlag);
            blockD->init(_dayOrNightFlag);
            blockE->init(_dayOrNightFlag);

            brickG->init(_dayOrNightFlag);
            brickH->init(_dayOrNightFlag);

            blockI->init(_dayOrNightFlag);
            blockJ->init(_dayOrNightFlag);

        }

        void update(ALLEGRO_EVENT event);
        void draw()
        {
            wall->draw();

            brickA->draw();
            brickB->draw();

            blockC->draw();
            blockD->draw();
            blockE->draw();

            brickG->draw();
            brickH->draw();

            blockI->draw();
            blockJ->draw();
        }

};

#endif // MAP_H
