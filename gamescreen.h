#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "global.h"
#include "soundmanager.h"
#include "mario.h"
#include "inputmanager.h"
#include "map.h"
#include "brick.h"

class GameScreen
{
    private:
        SoundManager *sound;
        InputManager input;
        Mario *player1;
        Mario *player2;
        Map* map;
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *gameover_player1;
        ALLEGRO_BITMAP *gameover_player2;
        ALLEGRO_BITMAP *gameover_unknown;


    public:
        GameScreen(); // constructor

        void init(int _dayOrNightFlag);
        void draw(int now);
        void draw_clock(int now);
        void update(ALLEGRO_EVENT event);
        void checkCollide();
        void gameOverPage();
};

#endif // GAMESCREEN_H
