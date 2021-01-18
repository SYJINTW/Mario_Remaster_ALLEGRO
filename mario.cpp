#include "mario.h"


void
Mario::initMarioRect()
{
    // Load Mario
    /*
    al_draw_bitmap(mario_image,0,0,1);
    imageHeight = al_get_bitmap_height(mario_image);
    imageWidth = al_get_bitmap_width(mario_image);
    */
    imageHeight = al_get_bitmap_height(imageVector[0]);
    imageWidth = al_get_bitmap_width(imageVector[0]);

    // 16px*16px mario -> 32*32px mario
    marioHeight = imageHeight;
    marioWidth = imageWidth;
    scaledHeight = imageHeight*2;
    scaledWidth = imageWidth*2;

    // Get Mario Rectangle (only get the stand mode, because all the picture are the same size)
    stand = new Rectangle(0, 0, marioWidth, marioHeight);
}

Mario::Mario(int _player_num)
{
    // load all the image of character
    for(int i = 0; i < 12; i++){
        imageVector.push_back(al_load_bitmap(imagename[i]));
    }
    player_num = _player_num;
    static int pos_num = 0;
    //mario_image = al_load_bitmap("res/images/mario-stand-16.png");
    ghost_image = al_load_bitmap("res/images/ghost-32.png");
    mario_sound = new SoundManager();
    initMarioRect();
    init(pos_num);
    if(++pos_num > 1)
        pos_num = 0;
}

void
Mario::init(int pos_num)
{
    currentFrame = stand;
    position = new Position(startPos[pos_num][0], startPos[pos_num][1]);
    box = new Rectangle(position->x, position->y, scaledWidth, scaledHeight);

    moveSpeed = 5;
    jumpSpeed = 10;
    gravity = 0.5;
    velocity = {0,0};
    inAir = false;
    topCollide = rightCollide = leftCollide = false;
    bottomCollide = 0;
    activeGravity = false;

    // for gaming
    last_born_pos = pos_num;
}


void
Mario::draw()
{
    al_draw_scaled_bitmap(imageVector[marioAction+6*player_num]
                        , currentFrame->left, currentFrame->top
                        , currentFrame->width, currentFrame->height
                        , box->left, box->top
                        , scaledWidth, scaledHeight
                        , rightOrLeftFlag);
}

void
Mario::draw_ghost(int player_num)
{
    if(ghost == true)
    {
        if(player_num == 1)
        {
            al_draw_bitmap(ghost_image
                        , PLAYER_1_HEART_X+PLAYER_1_HEART_RANGE, PLAYER_1_HEART_Y
                        , 0);
        }
        else if(player_num == 2)
        {
            al_draw_bitmap(ghost_image
                        , PLAYER_2_HEART_X-PLAYER_2_HEART_RANGE, PLAYER_2_HEART_Y
                        , 1);
        }
    }
}


void
Mario::update(ALLEGRO_EVENT event, InputManager input, int player_num)
{
    input.update();
    if(player_num == 1)
    {
        if(input.on_key_down(ALLEGRO_KEY_UP) || input.on_key_down(ALLEGRO_KEY_DOWN)
        || input.on_key_down(ALLEGRO_KEY_LEFT) || input.on_key_down(ALLEGRO_KEY_RIGHT))
        {
            // MOVE UP
            if(input.on_key_down(ALLEGRO_KEY_UP))
            {
                if(!inAir)
                {
                    dir = Up;
                    velocity.second = -jumpSpeed;
                    inAir = true;
                    activeGravity = true;
                    marioAction = 2; // jump
                    mario_sound->playJump();
                }
            }
            // MOVE LEFT
            if(input.on_key_down(ALLEGRO_KEY_LEFT))
            {
                dir = Left;
                rightOrLeftFlag = 1;
                velocity.first = -moveSpeed;
                if(!inAir)
                {
                    if(actionFrame < 9) actionFrame++;
                    else actionFrame = 0;
                    marioAction = actionFrame/3 + 2; // run
                }
                if(leftCollide)
                    velocity.first = 0;

            }
            // MOVE RIGHT
            if(input.on_key_down(ALLEGRO_KEY_RIGHT))
            {
                dir = Right;
                rightOrLeftFlag = 0;
                velocity.first = moveSpeed;
                if(!inAir)
                {
                    if(actionFrame < 9) actionFrame++;
                    else actionFrame = 0;
                    marioAction = actionFrame/3 + 2; // run
                }
                if(rightCollide)
                    velocity.first = 0;

                // screen bound
                if(position->x >= SCREEN_WIDTH-32)
                    velocity.first = 0;
            }
            // MOVE DOWN
            if(input.on_key_down(ALLEGRO_KEY_DOWN))
            {
                dir = Down;
                marioAction = 5; // fall
                // if inAir drop faster
                if(inAir)
                    velocity.second = jumpSpeed;
                if(topCollide)
                    velocity.second = 0;
            }
        }
        else
        {
            velocity.first = 0;
            marioAction = 0; // stand
        }

        // 加上加速度，上升速度下降，並且自動下降
        if(!bottomCollide)
        {
            activeGravity = true;
            velocity.second += gravity;
        }

        if(topCollide){
            velocity.second = 0;
        }

        // screen boundary
        if(position->x <= 0)
        {
            if(dir == Left || dir == Down)
            {
                velocity.first = 0;
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(0, position->y);
            }
            else
            {
                // change position
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(position->x, position->y);
            }
        }
        else if(position->x >= SCREEN_WIDTH-32)
        {
            if(dir == Right || dir == Down)
            {
                velocity.first = 0;
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(SCREEN_WIDTH-32, position->y);
            }
            else
            {
                // change position
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(position->x, position->y);
            }
        }
        else
        {
            // change position
            position->x += velocity.first;
            position->y += velocity.second;
            box->update(position->x, position->y);
        }

        topCollide = bottomCollide = leftCollide = rightCollide = false;
    }

    else if(player_num == 2)
        {
        if(input.on_key_down(ALLEGRO_KEY_W) || input.on_key_down(ALLEGRO_KEY_S)
        || input.on_key_down(ALLEGRO_KEY_A) || input.on_key_down(ALLEGRO_KEY_D))
        {
            // MOVE UP
            if(input.on_key_down(ALLEGRO_KEY_W))
            {
                if(!inAir)
                {
                    dir = Up;
                    velocity.second = -jumpSpeed;
                    inAir = true;
                    activeGravity = true;
                    marioAction = 2; // jump
                    mario_sound->playJump();
                }
            }
            // MOVE LEFT
            if(input.on_key_down(ALLEGRO_KEY_A))
            {
                dir = Left;
                rightOrLeftFlag = 1;
                velocity.first = -moveSpeed;
                if(!inAir)
                {
                    if(actionFrame < 9) actionFrame++;
                    else actionFrame = 0;
                    marioAction = actionFrame/3 + 2; // run
                }
                if(leftCollide)
                    velocity.first = 0;
            }
            // MOVE RIGHT
            if(input.on_key_down(ALLEGRO_KEY_D))
            {
                dir = Right;
                rightOrLeftFlag = 0;
                velocity.first = moveSpeed;
                if(!inAir)
                {
                    if(actionFrame < 9) actionFrame++;
                    else actionFrame = 0;
                    marioAction = actionFrame/3 + 2; // run
                }
                if(rightCollide)
                    velocity.first = 0;

                // screen bound
                if(position->x >= SCREEN_WIDTH-32)
                    velocity.first = 0;
            }
            // MOVE DOWN
            if(input.on_key_down(ALLEGRO_KEY_S))
            {
                dir = Down;
                marioAction = 5; // fall
                // if inAir drop faster
                if(inAir)
                    velocity.second = jumpSpeed;
                if(topCollide)
                    velocity.second = 0;
            }
        }
        else
        {
            velocity.first = 0;
            marioAction = 0; // stand
        }

        // 加上加速度，上升速度下降，並且自動下降
        if(!bottomCollide)
        {
            activeGravity = true;
            velocity.second += gravity;
        }

        if(topCollide){
            velocity.second = 0;
        }

        // screen boundary
        if(position->x <= 0)
        {
            if(dir == Left || dir == Down)
            {
                velocity.first = 0;
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(0, position->y);
            }
            else
            {
                // change position
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(position->x, position->y);
            }
        }
        else if(position->x >= SCREEN_WIDTH-32)
        {
            if(dir == Right || dir == Down)
            {
                velocity.first = 0;
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(SCREEN_WIDTH-32, position->y);
            }
            else
            {
                // change position
                position->x += velocity.first;
                position->y += velocity.second;
                box->update(position->x, position->y);
            }
        }
        else
        {
            // change position
            position->x += velocity.first;
            position->y += velocity.second;
            box->update(position->x, position->y);
        }

        topCollide = bottomCollide = leftCollide = rightCollide = false;
    }
}

bool
Mario::haveCollideWithWall(Wall *obj)
{
    int collideID = this->box->intersect(obj->box);
    if(collideID)
    {
        // Top
        /*
        if(collideID & 1)
        {
            std::cout<< "collide top\n";
            topCollide = true;
            velocity.second = 0;
            box->updateWithTop(obj->box->bottom);
        }
        */
        // Bottom
        if(collideID & 2)
        {
            //std::cout<< "collide bottom\n";
            bottomCollide = true;
            velocity.second = 0;
            inAir = false;
            activeGravity = false;
            position->y = obj->box->top - imageHeight*2;
            box->updateWithBottom(obj->box->top);
        }
        // Left
        /*
        if(collideID & 4)
        {
            std::cout<< "collide left\n";
            leftCollide = true;
            velocity.first = 0;
            box->updateWithLeft(obj->box->right+obj->imageWidth);
        }
        */
        // Right
        /*
        if(collideID & 8)
        {
            std::cout<< "collide right\n";
            rightCollide = true;
            velocity.first = 0;
            box->updateWithRight(obj->box->left);
        }
        */
    }
    return false;
}


bool
Mario::haveCollideWithBrick(Brick *obj)
{
    int collideID = this->box->intersect(obj->box);
    if(collideID)
    {
        // Top
        if(collideID & 1)
        {
            //std::cout<< "collide top\n";
            topCollide = true;
            velocity.second = 0;
            box->updateWithTop(obj->box->bottom);
        }
        // Bottom
        if(collideID & 2)
        {
            //std::cout<< "collide bottom\n";
            bottomCollide = true;
            velocity.second = 0;
            inAir = false;
            activeGravity = false;
            position->y = obj->box->top - imageHeight*2;
            box->updateWithBottom(obj->box->top);
        }
        /*
        // Left
        if(collideID & 4)
        {
            std::cout<< "collide left\n";
            leftCollide = true;
            velocity.first = 0;
            box->updateWithLeft(obj->box->right+obj->imageWidth);
        }
        // Right
        if(collideID & 8)
        {
            std::cout<< "collide right\n";
            rightCollide = true;
            velocity.first = 0;
            box->updateWithRight(obj->box->left);
        }
        */

    }
    return false;
}

bool
Mario::haveCollideWithBlock(Block *obj)
{
    int collideID = this->box->intersect(obj->box);
    if(collideID)
    {
        // Top
        if(collideID & 1)
        {
            //std::cout<< "collide top\n";
            topCollide = true;
            velocity.second = 0;
            box->updateWithTop(obj->box->bottom);
        }
        // Bottom
        else if(collideID & 2)
        {
            //std::cout<< "collide bottom\n";
            bottomCollide = true;
            velocity.second = 0;
            inAir = false;
            activeGravity = false;
            position->y = obj->box->top - imageHeight*2;
            box->updateWithBottom(obj->box->top);
        }
        // Left
        /*
        else if(collideID == 4)
        {
            std::cout<< "collide left\n";
            leftCollide = true;
            velocity.first = 0;
            box->updateWithLeft(obj->box->right+obj->imageWidth);
        }
        // Right
        else if(collideID == 8)
        {
            std::cout<< "collide right\n";
            rightCollide = true;
            velocity.first = 0;
            box->updateWithRight(obj->box->left);
        }
        */

    }
    return false;
}

bool
Mario::haveCollideWithMario(Mario *obj)
{
    int collideID = this->box->intersect(obj->box);
    if(collideID)
        catchMario(obj);
    return false;
}

void
Mario::reborn(int pos_num)
{
    currentFrame = stand;
    position = new Position(startPos[pos_num][0], startPos[pos_num][1]);
    box = new Rectangle(position->x, position->y, scaledWidth, scaledHeight);
}


// for gaming
void
Mario::initGhost(bool ghostOrNot)
{
    ghost = ghostOrNot;
}

void
Mario::catchMario(Mario* target)
{
    // Is ghost, then catch others
    if(ghost == true && target->ghost == false)
    {
        std::cout << "Catch\n";
        //ghost = false;
        ghost = true;
        //target->ghost = true;
        target->ghost = false;
        target->reborn(target->last_born_pos);
        mario_sound->playPlayerDie();
    }
    // Not ghost, be caught
    else if(ghost == false && target->ghost == true)
    {
        std::cout << "Be Caught\n";
        ghost = true;
        target->ghost = false;
        reborn(last_born_pos);
        mario_sound->playPlayerDie();
    }
    // Error
    else
    {
        std::cout << "Something got wrong\n";
        reborn(last_born_pos);
        target->reborn(target->last_born_pos);
    }
}

int
Mario::isGhost()
{
    if(ghost) return 1;
    else return 0;
}

/*
    al_draw_line(position->x+16, (position->y)-64
                ,position->x+16, (position->y)+32
                ,al_map_rgb(0, 100, 0)
                ,3);
*/
