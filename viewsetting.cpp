#include "viewsetting.h"

ViewSetting::ViewSetting()
{
    // Load font
    fontTopic = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 36, 0);
    fontText = al_load_font("res/fonts/Caviar_Dreams_Bold.ttf", 24, 0);
}

void
ViewSetting::init()
{
    BLOCK_SCALAR = 0;
}

void
ViewSetting::draw()
{
    al_draw_text(fontTopic, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TOPIC_ALIGN, ALLEGRO_ALIGN_CENTRE , "VIEW");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*0), ALLEGRO_ALIGN_CENTRE , "DAY");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*1), ALLEGRO_ALIGN_CENTRE , "NIGHT");
    al_draw_text(fontText, al_map_rgb(255, 255, 255), SCREEN_WIDTH_CENTER, TEXT_ALIGN+(70*2), ALLEGRO_ALIGN_CENTRE , "EXIT");

    al_draw_line(SCREEN_WIDTH_CENTER-BLOCK_WIDTH, TEXT_ALIGN+(70*BLOCK_SCALAR)+35,
                 SCREEN_WIDTH_CENTER+BLOCK_WIDTH, TEXT_ALIGN+(70*BLOCK_SCALAR)+35,
                 al_map_rgb(255, 255, 255),
                 3);
}

void
ViewSetting::up()
{
    std::cout << "Setting: up\n";
    if(BLOCK_SCALAR > 0)
        BLOCK_SCALAR--;
}

void
ViewSetting::down()
{
    std::cout << "Setting: down\n";
    if(BLOCK_SCALAR < 2)
        BLOCK_SCALAR++;
}

void
ViewSetting::enter()
{
    std::cout << "Pause: enter\n";
}

ActionDayOrNight
ViewSetting::action()
{
    if(BLOCK_SCALAR == 0) return V_DAY;
    else if(BLOCK_SCALAR == 1) return V_NIGHT;
    else if(BLOCK_SCALAR == 2) return V_EXIT;
}
