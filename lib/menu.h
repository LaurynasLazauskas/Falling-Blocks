#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "text.h"
#include "game_handler.h"

class Menu {

    /* This class handles the menu.
       It holds basic information i.e.
       title, menu options, etc.       */

    /* NOTES: Holds reference to
              GameHandler              */

public:
    enum {MENU_PLAY, MENU_CREDITS, MENU_EXIT, CHOICES_N};

    Menu(GameHandler *gameHandler, string title1, string title2, string opt1, string opt2,
         string opt3) {
        this->gameHandler = gameHandler;
        this->title1 = title1;
        this->title2 = title2;
        choices[MENU_PLAY] = opt1;
        choices[MENU_CREDITS] = opt2;
        choices[MENU_EXIT] = opt3;
        inMenu = true;
        current = 0;
        soundMenuNav = al_load_sample("res/sound/menuNav.wav");
        soundMenuSel = al_load_sample("res/sound/menuSelect.wav");
    }
    char const *getChoicesText(int choice) {
        return choices[choice].c_str();
    }
    char const *getTitleText1() {
        return title1.c_str();
    }
    char const *getTitleText2() {
        return title2.c_str();
    }
    bool isActive() {
        return inMenu;
    }
    void setActivity(bool activity) {
        inMenu = activity;
    }
    int getCurrent() {
        return current;
    }
    void up() {
        if (current - 1 >= 0) {
            current--;
            if (SOUND)
                al_play_sample(soundMenuNav, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
        gameHandler->setRedraw(true);
    }
    void down() {
        if (current + 1 < CHOICES_N) {
            current++;
            if (SOUND)
                al_play_sample(soundMenuNav, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
        gameHandler->setRedraw(true);
    }
    void enter() {
        al_play_sample(soundMenuSel, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

        switch(getCurrent()) {
        case MENU_PLAY:
            gameHandler->setState(GameHandler::STATE_GAME);
            setActivity(false);
            break;
        case MENU_CREDITS:
            gameHandler->setState(GameHandler::STATE_CREDITS);
            break;
        case MENU_EXIT:
            gameHandler->setState(GameHandler::STATE_EXIT);
            break;
        }
        gameHandler->setRedraw(true);
    }
    void destroySoundSamples() {
        al_destroy_sample(soundMenuNav);
        al_destroy_sample(soundMenuSel);
    }
    ~Menu() {

    }

private:
    GameHandler *gameHandler;
    ALLEGRO_SAMPLE *soundMenuNav;
    ALLEGRO_SAMPLE *soundMenuSel;
    string choices[CHOICES_N];
    string title1;
    string title2;
    int current;
    bool inMenu;
};


#endif
