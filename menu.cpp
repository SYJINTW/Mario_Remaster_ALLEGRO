#include "menu.h"

Menu::Menu()
{
    // Load font
    fontTopic = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 36, 0);
    fontText = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 24, 0);
}

void
Menu::init()
{
    BLOCK_SCALAR = 0;
}

void
Menu::draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(fontTopic, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TOPIC_ALIGN, ALLEGRO_ALIGN_CENTRE , "MENU");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*0), ALLEGRO_ALIGN_CENTRE , "NEW GAME");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*1), ALLEGRO_ALIGN_CENTRE , "SETTING");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*2), ALLEGRO_ALIGN_CENTRE , "QUIT");

    al_draw_line(SCREEN_WIDTH_CENTER-BLOCK_WIDTH, TEXT_ALIGN+(70*BLOCK_SCALAR)+35,
                 SCREEN_WIDTH_CENTER+BLOCK_WIDTH, TEXT_ALIGN+(70*BLOCK_SCALAR)+35,
                 al_map_rgb(255, 255, 255),
                 3);
}

void
Menu::up()
{
    std::cout << "Menu: up\n";
    if(BLOCK_SCALAR > 0)
        BLOCK_SCALAR--;
}

void
Menu::down()
{
    std::cout << "Menu: down\n";
    if(BLOCK_SCALAR < 2)
        BLOCK_SCALAR++;
}

void
Menu::enter()
{
    std::cout << "Menu: enter\n";
}

ActionMenu
Menu::action()
{
    if(BLOCK_SCALAR == 0) return NEWGAME;
    else if(BLOCK_SCALAR == 1) return SETTING;
    else if(BLOCK_SCALAR == 2) return QUIT;
}
