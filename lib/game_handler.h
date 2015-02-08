#ifndef GAME_HANDLER_H_INCLUDED
#define GAME_HANDLER_H_INCLUDED


class GameHandler {

public:
    enum {STATE_NONE, STATE_MENU, STATE_GAME, STATE_PAUSE, STATE_EXIT, STATE_CREDITS,
          STATE_GAME_OVER};
    GameHandler() {
        state = 0;
        alive = true;
        redraw = true;
        onStreak = false;
    }
    void setState(int state) {
        this->state = state;
    }
    int getState() {
        return state;
    }
    void setCondition(bool condition) {
        alive = condition;
    }
    bool isAlive() {
        return alive;
    }
    bool getRedraw() {
        return redraw;
    }
    void setRedraw(bool state) {
        redraw = state;
    }
    bool isOnStrek() {return onStreak;}
    void setOnStreak(bool value) {onStreak = value;}
private:
    int state;
    bool alive;
    bool redraw;
    bool onStreak;
};


#endif
