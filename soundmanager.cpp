#include "soundmanager.h"

SoundManager::SoundManager()
{
    al_reserve_samples(4);

    theme = al_load_sample(THEME_LIST[0]);
    jump = al_load_sample("res/sounds/sounds/jump-small.wav");
    die = al_load_sample("res/sounds/sounds/die.wav");
}

void
SoundManager::playTheme()
{
    al_play_sample(theme, sound_gain, 0, 1, ALLEGRO_PLAYMODE_LOOP, &themeID);
    std::cout << "Play Theme\n";
}

void
SoundManager::stopTheme()
{
    al_stop_sample(&themeID);
    std::cout << "Stop Theme\n";
}

void
SoundManager::playJump()
{
    al_play_sample(jump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void
SoundManager::playPlayerDie()
{
    al_play_sample(die, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void
SoundManager::soundGainControl(int i)
{
    // 1: voicc up
    // 0: no change
    // -1: voice down
    if(i == 1)
    {
        if(sound_gain != 2.0)
            sound_gain += 0.5;
    }
    else if(i == -1)
    {
        if(sound_gain != 0)
            sound_gain -= 0.5;
    }
}
