#include <iostream>

#include "gamescreen.h"

GameScreen::GameScreen()
{
    font = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 36, 0);
    gameover_player1 = al_load_bitmap("res/images/player1.png");
    gameover_player2 = al_load_bitmap("res/images/player2.png");
    gameover_unknown = al_load_bitmap("res/images/unknown.png");
    map = new Map();
    player1 = new Mario(0);
    player2 = new Mario(1);
}

void
GameScreen::init(int _dayOrNightFlag)
{
    //std::cout << "Init New Game.\n";
    //font = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 36, 0);
    map->init(_dayOrNightFlag);
    player1->init(0);
    player2->init(1);
    player1->initGhost(true);
    player2->initGhost(false);
}

void
GameScreen::draw(int now)
{
    map->draw();
    player1->draw();
    player2->draw();

    // draw life
    player1->draw_ghost(1);
    player2->draw_ghost(2);

    draw_clock(now);
}

void
GameScreen::draw_clock(int now)
{
    al_draw_circle(CLOCK_X, CLOCK_Y, CLOCK_R, al_map_rgb(0, 0, 0), CLOCK_THICK);
    al_draw_arc( CLOCK_X, CLOCK_Y, CLOCK_R-5
                ,-1.6 , 6.3*now/TIME_OF_GAME
                ,al_map_rgb(0, 255, 0)
                ,CLOCK_THICK+3);
}

void
GameScreen::update(ALLEGRO_EVENT event)
{
    player1->update(event, input, 1);
    player2->update(event, input, 2);

}

void
GameScreen::checkCollide()
{
    // check player1
    player1->haveCollideWithWall(map->wall);
    player1->haveCollideWithBrick(map->brickA);
    player1->haveCollideWithBrick(map->brickB);
    player1->haveCollideWithBlock(map->blockC);
    player1->haveCollideWithBlock(map->blockD);
    player1->haveCollideWithBlock(map->blockE);
    player1->haveCollideWithBrick(map->brickG);
    player1->haveCollideWithBrick(map->brickH);
    player1->haveCollideWithBlock(map->blockI);
    player1->haveCollideWithBlock(map->blockJ);
    player1->haveCollideWithMario(player2);
    // check player2
    player2->haveCollideWithWall(map->wall);
    player2->haveCollideWithBrick(map->brickA);
    player2->haveCollideWithBrick(map->brickB);
    player2->haveCollideWithBlock(map->blockC);
    player2->haveCollideWithBlock(map->blockD);
    player2->haveCollideWithBlock(map->blockE);
    player2->haveCollideWithBrick(map->brickG);
    player2->haveCollideWithBrick(map->brickH);
    player2->haveCollideWithBlock(map->blockI);
    player2->haveCollideWithBlock(map->blockJ);
    player2->haveCollideWithMario(player1);

}

void
GameScreen::gameOverPage()
{
    if(player1 > player2)
    {
        al_draw_bitmap(gameover_player2, 0 , 0, 0);
    }
    else if(player1 < player2)
    {
        al_draw_bitmap(gameover_player1, 0 , 0, 0);
    }
    else
    {
        al_clear_to_color(al_map_rgb(0, 20, 20));
    }
}
