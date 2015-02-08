#ifndef INPUT_HANDLER_H_INCLUDED
#define INPUT_HANDLER_H_INCLUDED

#include <iostream>
#include "enum_names.h"

using std::cout;
using std::endl;

class InputHandler {

public:
    InputHandler() {
        moveStopper = NULL;
    }
    void listenEvent(ALLEGRO_EVENT &events) {
        if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
            lastEvent = events;
            switch(events.keyboard.keycode) {
            case ALLEGRO_KEY_S:
                if(SOUND) SOUND = false;
                else SOUND = true;
                if(SHOW_INPUT)cout << "S : 1\n";
                break;
            case ALLEGRO_KEY_ENTER:
                keys[KEY_ENTER] = true;
                actual[KEY_ENTER] = true;
                if(SHOW_INPUT)cout << "ENTER : 1\n";
                break;
            case ALLEGRO_KEY_ESCAPE:
                keys[KEY_ESCAPE] = true;
                actual[KEY_ESCAPE] = true;
                if(SHOW_INPUT)cout << "ESC : 1\n";
                break;
            case ALLEGRO_KEY_LEFT:
                if (!locked[KEY_LEFT])
                    keys[KEY_LEFT] = true;
                actual[KEY_LEFT] = true;
                locked[KEY_LEFT] = true;
                if(moveStopper != NULL)
                    if(!moveStopper->isStarted())
                        moveStopper->start();
                if (SHOW_INPUT)cout << "LEFT : 1\n";
                break;
            case ALLEGRO_KEY_RIGHT:
                if (!locked[KEY_RIGHT])
                    keys[KEY_RIGHT] = true;
                actual[KEY_RIGHT] = true;
                locked[KEY_RIGHT] = true;
                if(moveStopper != NULL)
                    if(!moveStopper->isStarted())
                        moveStopper->start();
                if (SHOW_INPUT)cout << "RIGHT : 1\n";
                break;
            case ALLEGRO_KEY_UP:
                keys[KEY_UP] = true;
                actual[KEY_UP] = true;
                if(SHOW_INPUT)cout << "UP : 1\n";
                break;
            case ALLEGRO_KEY_DOWN:
                keys[KEY_DOWN] = true;
                actual[KEY_DOWN] = true;
                if(SHOW_INPUT)cout << "DOWN : 1\n";
                break;
            case ALLEGRO_KEY_Z:
                keys[KEY_ROTATION_CW] = true;
                actual[KEY_ROTATION_CW] = true;
                if(SHOW_INPUT)cout << "Z : 1\n";
                break;
            case ALLEGRO_KEY_X:
                keys[KEY_ROTATION_CCW] = true;
                actual[KEY_ROTATION_CCW] = true;
                if(SHOW_INPUT)cout << "X : 1\n";
                break;
            case ALLEGRO_KEY_SPACE:
                keys[KEY_SPACE] = true;
                actual[KEY_SPACE] = true;
                if(SHOW_INPUT)cout << "SPACE : 1\n";
                break;
            }
        } else if(events.type == ALLEGRO_EVENT_KEY_UP) {
            lastEvent = events;
            switch(events.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
                keys[KEY_ENTER] = false;
                actual[KEY_ENTER] = false;
                if(SHOW_INPUT)cout << "ENTER : 0\n";
                break;
            case ALLEGRO_KEY_ESCAPE:
                actual[KEY_ESCAPE] = false;
                keys[KEY_ESCAPE] = false;
                if(SHOW_INPUT)cout << "ESC : 0\n";
                break;
            case ALLEGRO_KEY_LEFT:
                actual[KEY_LEFT] = false;
                keys[KEY_LEFT] = false;
                locked[KEY_LEFT] = false;
                if (moveStopper != NULL)
                    if(moveStopper->isStarted())
                        moveStopper->stop();
                if(SHOW_INPUT)cout << "LEFT : 0\n";
                break;
            case ALLEGRO_KEY_RIGHT:
                actual[KEY_RIGHT] = false;
                keys[KEY_RIGHT] = false;
                locked[KEY_RIGHT] = false;
                if (moveStopper != NULL)
                    if(moveStopper->isStarted())
                        moveStopper->stop();
                if(SHOW_INPUT)cout << "RIGHT : 0\n";
                break;
            case ALLEGRO_KEY_UP:
                actual[KEY_UP] = false;
                keys[KEY_UP] = false;
                if(SHOW_INPUT)cout << "UP : 0\n";
                break;
            case ALLEGRO_KEY_DOWN:
                actual[KEY_DOWN] = false;
                keys[KEY_DOWN] = false;
                if(SHOW_INPUT)cout << "DOWN : 0\n";
                break;
            case ALLEGRO_KEY_Z:
                actual[KEY_ROTATION_CW] = false;
                keys[KEY_ROTATION_CW] = false;
                if(SHOW_INPUT)cout << "Z : 0\n";
                break;
            case ALLEGRO_KEY_X:
                actual[KEY_ROTATION_CCW] = false;
                keys[KEY_ROTATION_CCW] = false;
                if(SHOW_INPUT)cout << "X : 0\n";
                break;
            case ALLEGRO_KEY_SPACE:
                actual[KEY_SPACE] = false;
                keys[KEY_SPACE] = false;
                if(SHOW_INPUT)cout << "SPACE : 0\n";
                break;
            }
        }
    }
    bool getKey(int key) {
        return keys[key];
    }
    bool getActual(int key) {
        return actual[key];
    }
    void setKey(int key, bool value) {
        keys[key] = value;
    }
    void setEveryKey(bool value) {
        for (int i = 0; i < keysNumber; i++) 
            keys[i] = value;
    }
    void setActual(int key, bool value) {
        actual[key] = value;
    }
    void setLocked(int key, bool condition) {
        locked[key] = condition;
    }
    bool isLocked(int key) {
        return locked[key];
    }
    void loadTimer(Timer* timer) {
        moveStopper = timer;
    }

private:
    Timer *moveStopper;
    ALLEGRO_EVENT lastEvent;
    bool keys[keysNumber] = {0};
    bool locked[keysNumber] = {0};
    bool actual[keysNumber] = {0};
};


#endif
