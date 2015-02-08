#ifndef SPEED_LEVEL_H_INCLUDED
#define SPEED_LEVEL_H_INCLUDED

#include "Allegro/timer.h"

#define EXP_FOR_LAND 25
#define EXP_FOR_LINE 90

#define EXP_FOR_EACH_LEVEL 20

class SpeedLevel {
public:
    SpeedLevel() {
        exp = 0;
        level = 0;
        expToNextLevel = 100;
    }
    void linkTimer(Timer *timer) {this->timer = timer;}
    void reset() {
        exp = 0;
        level = 0;
        expToNextLevel = 100;
    }
    void addExp(int exp) {
        if (level < 25) {
            this->exp = this->exp + exp;
            if (this->exp >= expToNextLevel && level < 25) {
                this->exp = this->exp % expToNextLevel;
                level++;
                expToNextLevel += EXP_FOR_EACH_LEVEL;
            }
        }
        else this->exp = expToNextLevel;
        timer->changeSpeed(speeds[level]);
    }
    bool isMaxLevel() {return level>=25;}
    int getLevel() {return level;}
    int getExp() {return exp;}
    int getExpToLevel() {return expToNextLevel;}
private:
    double speeds[26] = {0.8, 0.72, 0.70, 0.65, 0.61, 0.55, 0.46, 0.36, 0.32, 0.28,
                  0.22, 0.18, 0.16, 0.15, 0.13, 0.12, 0.12, 0.11, 0.1, 0.1, 0.08,
                  0.07, 0.06, 0.05, 0.05, 0.04};
    Timer *timer;
    int level;
    int exp;
    int expToNextLevel;
};

#endif
