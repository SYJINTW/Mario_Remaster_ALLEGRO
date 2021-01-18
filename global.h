#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <vector>
#include <string>

const float FPS = 60.0f;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH_CENTER = SCREEN_WIDTH/2;
const int SCREEN_HEIGHT_CENTER = SCREEN_HEIGHT/2;

// for Menu
const float _TOPIC_ALIGN = SCREEN_HEIGHT/4;
const float _TEXT_ALIGN= SCREEN_HEIGHT*3/8;
const float _BLOCK_WIDTH = 80;

enum GameState { MENU, SETTINGPAGE, VIEW, GAME, PAUSE, GAMEOVER, VIEWSETTINGPAGE, SOUNDSETTINGPAGE, CONTROLSETTINGPAGE };
enum ActionMenu { NEWGAME, SETTING, QUIT };
enum ActionPause { P_RESUME, P_NEWGAME, P_MENU };
enum ActionSetting { S_VIEW, S_SOUND, S_CONTROL };
enum ActionDayOrNight { V_DAY, V_NIGHT, V_EXIT };
enum ObjectType { MARIO, WALL, BRICK, BLOCK};

enum MarioMove { STAND, JUMP, RUN_1, RUN_2, RUN_3, FALL};

const float startPos[2][2] = {{64, 0}, {SCREEN_WIDTH - 96, 0}};

const std::vector<char*> THEME_LIST = {"res/sounds/themes/overworld.wav"};

const int DAY_NIGHT_RGB[2][3] = {{107, 140, 255}, {34, 46, 80}};

// for game
const int PLAYER_1_HEART_X = 50;
const int PLAYER_1_HEART_Y = 50;
const int PLAYER_1_HEART_RANGE = 50;
const int PLAYER_2_HEART_X = SCREEN_WIDTH-50-32;
const int PLAYER_2_HEART_Y = 50;
const int PLAYER_2_HEART_RANGE = 50;
const int PLAYER_START_LIFE = 3;
// clock
const int TIME_OF_GAME = 60;
const int CLOCK_X = SCREEN_WIDTH_CENTER;
const int CLOCK_Y = 70;
const int CLOCK_R = 30; // radius
const int CLOCK_THICK = 3;

char* const imagename[12] = { // mario:0-5
                        "res/images/mario-stand-16.png"
                        ,"res/images/mario-jump-16.png"
                        ,"res/images/mario-run1-16.png"
                        ,"res/images/mario-run2-16.png"
                        ,"res/images/mario-run3-16.png"
                        ,"res/images/mario-fall-16.png"
                        // eeyore:6-11
                        ,"res/images/eeyore-stand-16.png"
                        ,"res/images/eeyore-jump-16.png"
                        ,"res/images/eeyore-run1-16.png"
                        ,"res/images/eeyore-run2-16.png"
                        ,"res/images/eeyore-run3-16.png"
                        ,"res/images/eeyore-fall-16.png"
                    };


#endif // INPUTMANAGER_H
