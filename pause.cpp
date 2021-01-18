#include "pause.h"

Pause::Pause()
{
    // Load font
    fontTopic = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 36, 0);
    fontText = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 24, 0);
}

void
Pause::init()
{
    BLOCK_SCALAR = 0;
}

void
Pause::draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(fontTopic, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TOPIC_ALIGN, ALLEGRO_ALIGN_CENTRE , "PAUSE");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*0), ALLEGRO_ALIGN_CENTRE , "RESUME");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*1), ALLEGRO_ALIGN_CENTRE , "NEW GAME");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*2), ALLEGRO_ALIGN_CENTRE , "MENU");

    al_draw_line(SCREEN_WIDTH_CENTER-BLOCK_WIDTH, TEXT_ALIGN+(70*BLOCK_SCALAR)+35,
                 SCREEN_WIDTH_CENTER+BLOCK_WIDTH, TEXT_ALIGN+(70*BLOCK_SCALAR)+35,
                 al_map_rgb(255, 255, 255),
                 3);
}

void
Pause::up()
{
    std::cout << "Pause: up\n";
    if(BLOCK_SCALAR > 0)
        BLOCK_SCALAR--;
}

void
Pause::down()
{
    std::cout << "Pause: down\n";
    if(BLOCK_SCALAR < 2)
        BLOCK_SCALAR++;
}

void
Pause::enter()
{
    std::cout << "Pause: enter\n";
}

ActionPause
Pause::action()
{
    if(BLOCK_SCALAR == 0) return P_RESUME;
    else if(BLOCK_SCALAR == 1) return P_NEWGAME;
    else if(BLOCK_SCALAR == 2) return P_MENU;
}
