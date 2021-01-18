#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <string>
#include <vector>


#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>

#include "soundmanager.h"
#include "global.h"
#include "rectangle.h"
#include "position.h"
#include "inputmanager.h"

#include "wall.h"
#include "brick.h"
#include "block.h"

class Mario
{
    private:
        SoundManager *mario_sound;
        ALLEGRO_BITMAP *mario_image;
        ALLEGRO_BITMAP *ghost_image;

        std::vector<ALLEGRO_BITMAP *> imageVector;

        // for height width position
        int imageHeight;
        int imageWidth;
        float scaledHeight;
        float scaledWidth;
        float marioHeight;
        float marioWidth;
        Rectangle *stand; //, *walk[3], *run, *hang[2], *crouchOrDie;
        Rectangle *currentFrame;
        Rectangle *box;
        Position *position;

        // for moving detail
        float moveSpeed;
        float jumpSpeed;
        float gravity;
        std::pair<float, float> velocity;
        bool inAir;
        bool topCollide, bottomCollide, rightCollide, leftCollide;
        bool activeGravity;


        // for display
        int rightOrLeftFlag = 0; // right = 0, left = 1
        int marioAction = 0; //0:stand 1:jump 2-4:run 5:fall
        int actionFrame = 0;
        int player_num = 0;;

        // for input
        InputManager input;
        ALLEGRO_KEYBOARD_STATE keyState;

        // for recognize type
        ObjectType objectType = MARIO;

        // for brick
        bool limitJumpFlag = false;
        float limitJumpSpeed;


    public:
        enum Direction {Up, Down, Left, Right};
        Direction dir;

        // for game
        int life;
        int last_born_pos;
        bool ghost;

        Mario(int player_num);

        void init(int pos_num);
        void initMarioRect();
        void draw(); // show mario
        void draw_ghost(int player_num); // show who is the ghost
        void update(ALLEGRO_EVENT event, InputManager input, int player_num); // react by keyboard intput
        bool haveCollideWithWall(Wall *obj);
        bool haveCollideWithBrick(Brick *obj);
        bool haveCollideWithBlock(Block *obj);
        bool haveCollideWithMario(Mario *obj);
        void reborn(int pos_num);
        void initGhost(bool ghostOrNot);
        void catchMario(Mario *target);
        int isGhost();
};




#endif // MARIO_H
