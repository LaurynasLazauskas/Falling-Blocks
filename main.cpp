/* ****************************************** *
                FALLING BLOCKS
                --------------
          @author Laurynas Lazauskas
                --------------
        Project is powered by Allegro5
 * ****************************************** */

// C++ LIBS
#include <string>
#include <iostream>
// ALLEGRO LIBS
#define ALLEGRO_STATICLINK
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
// ALLGERO LIBS WRAPPED IN CLASSES
#include "lib/Allegro/display.h"
#include "lib/Allegro/event_queue.h"
#include "lib/Allegro/timer.h"
#include "lib/Allegro/font.h"
// OTHER LIBS
#include "lib/simple_encryption.h"
#include "lib/text.h"
#include "lib/global_states.h"
#include "lib/enum_names.h"
#include "lib/block_basket.h"
#include "lib/game_grid.h"
#include "lib/block.h"
#include "lib/game_handler.h"
#include "lib/input_handler.h"
#include "lib/score.h"
#include "lib/menu.h"
#include "lib/speed_level.h"
#include "lib/dashboard.h"
#include "lib/dashboard/small_blocks_visuals.h"
#include "lib/constants.h"

using std::cout;
using std::endl;
using std::string;

void initializeAllegro() {
    // Initiating Allegro
    if (!al_init()) {
        if(ERROR_HUNT) std::cout << "Error al_init() failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Initiating addons
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
}

int main(int argc, char **argv) {

    // Initialization
    initializeAllegro();

    // Display
    Display display(GAME_DISPLAY_WIDTH,GAME_DISPLAY_HEIGHT);
    display.checkInit();
    display.setTitle("Falling Blocks v0.1.0");

    // Game classes
    InputHandler input;
    GameHandler gameHandler;
    Score score;
    SpeedLevel level;
    Menu menu(&gameHandler, "Falling", "Blocks", "Play", "Credits", "Exit");

    // Loading resources;
    Font titleFont;
    Font regularFont;
    Font miniFont;
    titleFont.loadTtfFont("res/font/title-font.ttf", 50);
    regularFont.loadTtfFont("res/font/regular-font.ttf", 15);
    miniFont.loadTtfFont("res/font/regular-font.ttf", 10);
    ALLEGRO_SAMPLE *highScoreSound = al_load_sample("res/sound/highScore.wav");
    ALLEGRO_SAMPLE *landSound = al_load_sample("res/sound/land.wav");
    ALLEGRO_SAMPLE *gameOverSound = al_load_sample("res/sound/gameOver.wav");

    al_reserve_samples(7);

    // Selecting colors
    ALLEGRO_COLOR darkGray = al_map_rgb(50, 50, 50);
    ALLEGRO_COLOR lightGray = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR light = al_map_rgb(200, 200, 200);


    // Event Queue
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    // Initial game state
    gameHandler.setState(GameHandler::STATE_MENU);

    // GAME LOOP
    while(gameHandler.getState() != GameHandler::STATE_EXIT) {
        ALLEGRO_EVENT event;

        // STATE_MENU
        if (gameHandler.getState() == GameHandler::STATE_MENU) {
            EventQueue eventQueue;
            eventQueue.registerSource(al_get_keyboard_event_source());

            gameHandler.setRedraw(true);

            while (gameHandler.getState() == GameHandler::STATE_MENU) { // WHILE LOOP
                // DRAW
                if (gameHandler.getRedraw()) {
                    al_clear_to_color(lightGray);
                    // Title
                    al_draw_text(titleFont.getPointer(), darkGray, 90, 100,
                    ALLEGRO_ALIGN_LEFT, menu.getTitleText1());
                    al_draw_text(titleFont.getPointer(), darkGray, 90, 150,
                    ALLEGRO_ALIGN_LEFT, menu.getTitleText2());
                    // Menu items
                    al_draw_text(regularFont.getPointer(), light, 90, 250,
                    ALLEGRO_ALIGN_LEFT, menu.getChoicesText(Menu::MENU_PLAY));
                    al_draw_text(regularFont.getPointer(), light, 90, 270,
                    ALLEGRO_ALIGN_LEFT, menu.getChoicesText(Menu::MENU_CREDITS));
                    al_draw_text(regularFont.getPointer(), light, 90, 290,
                    ALLEGRO_ALIGN_LEFT, menu.getChoicesText(Menu::MENU_EXIT));
                    al_draw_text(regularFont.getPointer(), light, 80, 250+20*menu.getCurrent(),
                    ALLEGRO_ALIGN_LEFT, ">");
                    // Footer
                    al_draw_text(regularFont.getPointer(), al_map_rgb(80, 80, 80),
                    display.getWidth()/2, display.getHeight()-30,
                    ALLEGRO_ALIGN_CENTRE, "Laurynas Lazauskas, 2014");

                    al_flip_display();
                }

                eventQueue.wait(&event);

                // INPUT
                input.listenEvent(event);
                if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if(input.getKey(KEY_DOWN)) {
                        menu.down();
                        input.setKey(KEY_DOWN, false);
                    }
                    if(input.getKey(KEY_UP)) {
                        menu.up();
                        input.setKey(KEY_UP, false);
                    }
                    if(input.getKey(KEY_ENTER) || input.getKey(KEY_SPACE)) {
                        menu.enter();
                        input.setKey(KEY_ENTER, false);
                        input.setKey(KEY_SPACE, false);
                    }
                }
            }
        }

        // STATE_CREDITS
        if (gameHandler.getState() == GameHandler::STATE_CREDITS) {
            int index = 500;
            Text credits("res/text/credits.txt");
            Timer creditsScrollTimer(0.02);
            EventQueue eventQueue;
            eventQueue.registerSource(creditsScrollTimer.getEventSource());
            eventQueue.registerSource(al_get_keyboard_event_source());

            creditsScrollTimer.start();

            while(gameHandler.getState() == GameHandler::STATE_CREDITS) { // WHILE LOOP
                eventQueue.wait(&event);

                // INPUT
                input.listenEvent(event);
                if(input.getKey(KEY_ENTER) || input.getKey(KEY_SPACE) ||
                input.getKey(KEY_ESCAPE)) {
                    gameHandler.setState(GameHandler::STATE_MENU);
                    input.setEveryKey(false);
                }
                // DRAW
                if (event.timer.source == creditsScrollTimer.pointer()) {
                    index--;
                    al_clear_to_color(lightGray);
                    for (int i = 0; i < credits.getSize(); i++) {
                        al_draw_text(regularFont.getPointer(), light,
                        display.getWidth()/2, index+i*15,
                        ALLEGRO_ALIGN_CENTRE, credits.get(i));
                    }
                    al_flip_display();
                    if(index < -260) gameHandler.setState(GameHandler::STATE_MENU);
                }
            }
            creditsScrollTimer.stop();
        }

        // STATE_GAME
        if (gameHandler.getState() == GameHandler::STATE_GAME) {
            // Timers
            Timer fallTimer(0.8);
            Timer moveStopper(0.15);
            Timer moveSpeedTimer(0.05);
            Timer beforeLandTimer(0.4);

            input.loadTimer(&moveStopper);
            level.linkTimer(&fallTimer);

            EventQueue eventQueue;
            eventQueue.registerSource(fallTimer.getEventSource());
            eventQueue.registerSource(moveStopper.getEventSource());
            eventQueue.registerSource(moveSpeedTimer.getEventSource());
            eventQueue.registerSource(beforeLandTimer.getEventSource());
            eventQueue.registerSource(al_get_keyboard_event_source());

            // Grid / Block / Score
            GameGrid grid(&display);

            BlocksBasket blocksBasket;

            Block block(&grid);
            block.setType(blocksBasket.get());
            block.spawn();

            score.resetScore();
            level.reset();

            // GameHandler states
            gameHandler.setOnStreak(false);
            gameHandler.setRedraw(true);

            // Dashboard init
            Dashboard dashboard;
            dashboard.linkDisplay(&display);
            dashboard.linkScore(&score);
            dashboard.loadFont("res/font/regular-font.ttf");
            dashboard.linkLevel(&level);

            fallTimer.start();
            moveSpeedTimer.start();

            while(gameHandler.getState() == GameHandler::STATE_GAME) { // WHILE LOOP

                // DRAW
                if (gameHandler.getRedraw()) {
                    al_set_target_bitmap(al_get_backbuffer(display.getPointer()));
                    al_clear_to_color(lightGray);

                    grid.draw();
                    dashboard.draw();
                    SmallBlockVisual::draw(display.getWidth()/2-25, 10, blocksBasket.peak());

                    al_flip_display();
                    gameHandler.setRedraw(false);
                }

                eventQueue.wait(&event);

                // INPUT
                input.listenEvent(event);

                    // ROTATE
                if(input.getKey(KEY_ROTATION_CCW)) {
                    block.rotateBlock(ROTATE_CCW);
                    input.setKey(KEY_ROTATION_CCW, false);
                    gameHandler.setRedraw(true);
                } else if(input.getKey(KEY_ROTATION_CW)) {
                    block.rotateBlock(ROTATE_CW);
                    input.setKey(KEY_ROTATION_CW, false);
                    gameHandler.setRedraw(true);
                    // Exit
                } else if(input.getKey(KEY_ESCAPE)) {
                    gameHandler.setState(GameHandler::STATE_EXIT);
                }

                    // MOVE STOPPER
                if (event.timer.source == moveStopper.pointer()) {
                    moveStopper.stop();
                    input.setLocked(KEY_LEFT, false);
                    input.setLocked(KEY_RIGHT, false);
                }

                    // MOVE
                if (event.timer.source == moveSpeedTimer.pointer()) {
                    if (input.getKey(KEY_LEFT) ||
                        (!input.isLocked(KEY_LEFT) && input.getActual(KEY_LEFT))) {
                        block.moveBlock(LEFT);
                        input.setKey(KEY_LEFT, false);
                        gameHandler.setRedraw(true);
                    } else if(input.getKey(KEY_RIGHT) ||
                        (!input.isLocked(KEY_RIGHT) && input.getActual(KEY_RIGHT))) {
                        block.moveBlock(RIGHT);
                        input.setKey(KEY_RIGHT, false);
                        gameHandler.setRedraw(true);
                    }
                    if (input.getKey(KEY_DOWN)) {
                        if(block.peakFall())
                           block.fall();
                        gameHandler.setRedraw(true);
                    }
                }
                if (input.getKey(KEY_SPACE)) {
                    while(block.fall());
                    block.setAboutToLand(true);

                    gameHandler.setRedraw(true);
                    input.setKey(KEY_SPACE, false);
                }
                // FALL
                if (event.timer.source == fallTimer.pointer() &&
                    !beforeLandTimer.isStarted()) {
                    block.fall();
                    gameHandler.setRedraw(true);
                }

                // CHECK IF LANDED
                if (!block.peakFall() && !block.isAboutToLand() &&
                    !beforeLandTimer.isStarted()) {
                    beforeLandTimer.start();
                }
                if (event.timer.source == beforeLandTimer.pointer()) {
                    block.setAboutToLand(true);
                    beforeLandTimer.stop();
                }
                if (!block.peakFall() && block.isAboutToLand()) {
                    if (block.getStartY() < 2) {
                        gameHandler.setState(GameHandler::STATE_GAME_OVER);
                        input.setKey(KEY_SPACE, false);
                    }
                    al_play_sample(landSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    block.fall();
                    level.addExp(EXP_FOR_LAND);
                    score.addScore(POINTS_FOR_PLACED_BLOCK);
                    // DELETE FULL LINES
                    int fullLines[4];
                    int fullLinesQuantity = 0;
                    for (int i = 0; i < GRIDH; i++) {
                        if (grid.isLineFull(i)) {
                            fullLines[fullLinesQuantity] = i;
                            fullLinesQuantity++;
                        }
                    }
                    if (fullLinesQuantity != 0) {

                        if (fullLinesQuantity > 1)
                            score.addScore(fullLinesQuantity*POINTS_BONUS);
                        score.addScore(fullLinesQuantity*POINTS_FOR_FULL_LINE);
                        level.addExp(fullLinesQuantity*EXP_FOR_LINE);
                        if (fullLinesQuantity == 4)
                            score.addScore(POINTS_FOR_4_FULL_LINES);
                        grid.destroyMultiLines(fullLinesQuantity, fullLines);
                    }
                    block.setType(blocksBasket.get());
                    block.spawn();
                    if (score.getScore() > 50 && score.isRecord() && !gameHandler.isOnStrek()) {
                        al_play_sample(highScoreSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        gameHandler.setOnStreak(true);
                    }
                }
                else if (block.peakFall() && block.isAboutToLand()) {
                    block.setAboutToLand(false);
                }

            }
            // FIN_STATE_GAME
            if (fallTimer.isStarted())
                fallTimer.stop();
            if (moveSpeedTimer.isStarted())
                moveSpeedTimer.stop();
        }

        // STATE_GAME_OVER
        if (gameHandler.getState() == GameHandler::STATE_GAME_OVER) {
            al_play_sample(gameOverSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            EventQueue eventQueue;
            eventQueue.registerSource(al_get_keyboard_event_source());

            score.ifRecordSave();
            gameHandler.setRedraw(true);

            int yesNo = 0;
            input.setEveryKey(false);

            while (gameHandler.getState() == GameHandler::STATE_GAME_OVER) {
                if (gameHandler.getRedraw()) {
                    al_clear_to_color(lightGray);
                    al_draw_text(regularFont.getPointer(), darkGray, display.getWidth()/2,
                                 display.getHeight()/2, ALLEGRO_ALIGN_CENTRE,
                                 "Game Over! Play again?");
                    al_draw_textf(regularFont.getPointer(), darkGray, display.getWidth()/2,
                                 display.getHeight()/2+20, ALLEGRO_ALIGN_CENTRE,
                                 "Your score: %d", score.getScore());
                    al_draw_text(regularFont.getPointer(), light, display.getWidth()/2-40,
                                 display.getHeight()/2+40, ALLEGRO_ALIGN_CENTRE,
                                 "Yes");
                    al_draw_text(regularFont.getPointer(), light, display.getWidth()/2+40,
                                 display.getHeight()/2+40, ALLEGRO_ALIGN_CENTRE,
                                 "No");
                    al_draw_text(regularFont.getPointer(), light, display.getWidth()/2-60+yesNo*80,
                                 display.getHeight()/2+40, ALLEGRO_ALIGN_CENTRE,
                                 ">");
                    gameHandler.setRedraw(false);
                    al_flip_display();
                }
                eventQueue.wait(&event);

                if (event.type == ALLEGRO_EVENT_KEY_DOWN || 
                    event.type == ALLEGRO_EVENT_KEY_UP) {
                    input.listenEvent(event);
                    if (input.getKey(KEY_RIGHT)) {
                        input.setKey(KEY_RIGHT, false);
                        if(yesNo==0) yesNo = 1;
                        gameHandler.setRedraw(true);
                    }
                    else if (input.getKey(KEY_LEFT)) {
                        input.setKey(KEY_LEFT, false);
                        if(yesNo==1) yesNo = 0;
                        gameHandler.setRedraw(true);
                    }
                    if (input.getKey(KEY_ENTER) ||
                        input.getKey(KEY_SPACE)){
                            input.setKey(KEY_ENTER, false);
                            input.setKey(KEY_SPACE, false);
                            if (yesNo == 1) gameHandler.setState(GameHandler::STATE_MENU);
                            else gameHandler.setState(GameHandler::STATE_GAME);
                    }
                }
            }
        }
    }

    menu.destroySoundSamples();
    al_destroy_sample(highScoreSound);
    al_uninstall_audio();
    return 0;
}
