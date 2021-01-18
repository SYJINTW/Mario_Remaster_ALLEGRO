#ifndef MENUPOSITION_H
#define MENUPOSITION_H

#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "global.h"

class MenuPosition
{
    public:
        MenuPosition(int posx, int posy, int _space)
        {
            x = posx;
            y = posy;
            space = _space;
            next_x = x;
            next_y = y;
            current = 0;
        }

        ActionMenu getCurrentAction()
        {
		//    return positions[current]->action;
	    }

    private:
        int x, y;
        int space;
        int next_x, next_y;
        int current;
        std::vector<MenuPosition*> positions;
};

#endif // MENUPOSITION_H
