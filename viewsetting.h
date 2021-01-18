#ifndef VIEWSETTING_H
#define VIEWSETTING_H

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include "menuposition.h"
#include "global.h"

class ViewSetting
{
    public:
        ViewSetting();

        void init();
        void draw();
        void up();
        void down();
        void enter();
        ActionDayOrNight action();

    private:
        ALLEGRO_FONT *fontTopic = NULL;
        ALLEGRO_FONT *fontText = NULL;
        float TOPIC_ALIGN = _TOPIC_ALIGN;
        float TEXT_ALIGN= _TEXT_ALIGN;
        float BLOCK_WIDTH = _BLOCK_WIDTH;
        //float BLOCK_HEIGHT = 0;
        int BLOCK_SCALAR = 0; // 0:NEWGAME, 1:SETTING, 2:QUIT
};

#endif // VIEWSETTING_H
