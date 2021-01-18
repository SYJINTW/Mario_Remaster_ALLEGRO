#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>

#include "global.h"

class InputManager
{
    private:
        ALLEGRO_KEYBOARD_STATE keyState;
    public:
        InputManager(){};

        void update()
        {
            al_get_keyboard_state(&keyState);
        }

        bool on_key_press(ALLEGRO_EVENT event, int keycode, GameState gameState)
        {}

        bool on_key_down(int keycode)
        {
            if(al_key_down(&keyState, keycode))
                return true;
            return false;
        }

};



#endif // INPUTMANAGER_H
