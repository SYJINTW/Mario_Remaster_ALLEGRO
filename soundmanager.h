#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "global.h"

class SoundManager
{
    private:
        ALLEGRO_SAMPLE *theme, *jump, *die;
        ALLEGRO_SAMPLE_ID themeID;

    public:
        SoundManager();
        void playTheme();
        void stopTheme();
        void playJump();
        void playPlayerDie();
        void soundGainControl(int i);

        // for setting
        float sound_gain = 1.0;
        int theme_num = 0;
};



#endif // SOUNDMANAGER_H
