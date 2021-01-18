#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


#include "global.h"
#include "gamescreen.h"
#include "menu.h"
#include "soundmanager.h"
#include "inputmanager.h"
#include "settingpage.h"
#include "pause.h"
#include "viewsetting.h"

int main(int argc, char *argv[])
{
    const float FPS = 60.0f;
    int dayOrNight = 0; // Day:0, Night:1

    // ALLEGRO INIT
    if (!al_init())
    {
        al_show_native_message_box(NULL, "Error", "Error", "Cannot initialize Allegro", NULL, NULL);
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!display)
    {
        al_show_native_message_box(NULL, "Error", "Error", "Cannot create display", NULL, NULL);
        return -1;
    }

    // INSTALL AND INIT
    al_install_keyboard();
    al_init_image_addon();
    al_init_acodec_addon();
    al_install_audio();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    std::cout << "Install and Init Done.\n";

    // CREATE
    Menu menu;
    GameScreen game;
    SoundManager sound;
    InputManager input;
    SettingPage settingpage;
    Pause pause;
    ViewSetting viewsetting;


    ALLEGRO_FONT *font = al_load_font("Caviar_Dreams_Bold.ttf",24,0);
    ALLEGRO_TIMER *timer = al_create_timer(1.0f / FPS);
    ALLEGRO_TIMER *gameTimer = al_create_timer(1.0f);
    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();

    // REGISTER
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_timer_event_source(gameTimer));
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    std::cout << "Register Done.\n";

    // FLAG
    bool done = false;
    bool redraw = true;

    // SETTING
    GameState gameState = MENU;


    // START
    al_start_timer(timer);
    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;
        else if (event.type == ALLEGRO_EVENT_TIMER)
        {
            // Event for redrawing the display.
            if (event.timer.source == timer)
                // The redraw timer has ticked.
                redraw++;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (gameState == MENU)
            {
                std::cout << "Menu\n";
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP: menu.up(); break;
				case ALLEGRO_KEY_DOWN: menu.down(); break;
				case ALLEGRO_KEY_ENTER:
				    //menu.enter();
                    ActionMenu action = menu.action();
					switch (action) {
					case NEWGAME:
                        sound.playTheme();
						gameState = GAME;
						game.init(dayOrNight);
                        // Reset and Start game time counter
                        al_set_timer_count(gameTimer, 0);
                        al_start_timer(gameTimer);
						break;
                    case SETTING:
                        gameState = SETTINGPAGE;
                        settingpage.init();
						break;
                    case QUIT: done = true; break;
					}
				break;
				}
			}
            else if (gameState == SETTINGPAGE)
            {
                std::cout << "Setting Page\n";
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP: settingpage.up(); break;
				case ALLEGRO_KEY_DOWN: settingpage.down(); break;
				case ALLEGRO_KEY_ESCAPE:
                    gameState = MENU;
                    menu.init();
                    break;
				case ALLEGRO_KEY_ENTER:
                    ActionSetting action = settingpage.action();
					switch (action) {
					case S_VIEW:
					    std::cout << "View setting page\n";
                        gameState = VIEWSETTINGPAGE;
                        viewsetting.init();
					    break;
                    case S_SOUND:
                        std::cout << "Sound setting page\n";
                        break;
                    case S_CONTROL:
                        std::cout << "Control setting page\n";
                        break;
					}
                    break;
				}
			}
			else if (gameState == GAME)
            {
                std::cout << "Gaming\n";
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
                    gameState = PAUSE;
                    // Stop game time counter
                    al_stop_timer(gameTimer);
                    pause.init(); // init the pause page
                    break;
				}
			}
            else if (gameState == PAUSE)
            {
                std::cout << "Pause\n";
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP: pause.up(); break;
				case ALLEGRO_KEY_DOWN: pause.down(); break;
				case ALLEGRO_KEY_ENTER:
                    ActionPause action = pause.action();
					switch (action) {
					case P_RESUME:
                        gameState = GAME;
                        // Start game time counter, continue count
                        al_start_timer(gameTimer);
						break;
                    case P_NEWGAME:
                        sound.stopTheme();
                        sound.playTheme();
						gameState = GAME;
						game.init(dayOrNight);
                        // Reset and Start game time counter
                        al_set_timer_count(gameTimer, 0);
                        al_start_timer(gameTimer);
						break;
                    case P_MENU:
                        sound.stopTheme();
                        gameState = MENU;
                        menu.init();
						break;
					}
				break;
				}
			}
            else if (gameState == VIEWSETTINGPAGE)
            {
                std::cout << "View Setting Page\n";
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP: viewsetting.up(); break;
				case ALLEGRO_KEY_DOWN: viewsetting.down(); break;
				case ALLEGRO_KEY_ESCAPE:
                    gameState = SETTINGPAGE;
                    break;
				case ALLEGRO_KEY_ENTER:
                    ActionDayOrNight action = viewsetting.action();
					switch (action) {
					case V_DAY:
					    dayOrNight = 0;
					    break;
                    case V_NIGHT:
                        dayOrNight = 1;
                        break;
                    case V_EXIT:
                        gameState = SETTINGPAGE;
                        break;
					}
                    break;
				}
			}
            else if (gameState == GAMEOVER)
            {
                std::cout << "Game Over\n";
                game.gameOverPage();
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
                    gameState = MENU;
                    // Stop game time counter
                    al_stop_timer(gameTimer);
                    menu.init(); // init the pause page
                    break;
				}
			}
		}

        // run safe

        if (redraw && al_is_event_queue_empty(eventQueue))
        {
			if (gameState == MENU)
            {
				menu.draw();
			}
            else if(gameState == SETTINGPAGE)
            {
                settingpage.draw();
            }
			else if (gameState == GAME)
            {
                al_clear_to_color(al_map_rgb(DAY_NIGHT_RGB[dayOrNight][0], DAY_NIGHT_RGB[dayOrNight][1], DAY_NIGHT_RGB[dayOrNight][2]));
                game.checkCollide();
                game.update(event);
                game.draw(al_get_timer_count(gameTimer));
                redraw = 0;
                // check the game timer
                if(al_get_timer_count(gameTimer) == TIME_OF_GAME)
                {
                    std::cout << "Time's up\n";
                    al_stop_timer(gameTimer);
                    gameState = GAMEOVER;
                }
				//game.render();
			}
            else if (gameState == PAUSE)
            {
				pause.draw();
			}
            else if (gameState == VIEWSETTINGPAGE)
            {
                al_clear_to_color(al_map_rgb(DAY_NIGHT_RGB[dayOrNight][0], DAY_NIGHT_RGB[dayOrNight][1], DAY_NIGHT_RGB[dayOrNight][2]));
				viewsetting.draw();
			}
            else if (gameState == GAMEOVER)
            {}
			al_flip_display();
		}
    }

    // DESTROY
    al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(timer);
    al_destroy_timer(gameTimer);

    return 0;
}

