#ifndef DASHBOARD_H_INCLUDED
#define DASHBOARD_H_INCLUDED

//#include <string>

#include "Allegro/display.h"
#include "Allegro/font.h"
#include "score.h"
#include "speed_level.h"

class Dashboard {
public:
    Dashboard() {
        darkGray = al_map_rgb(50, 50, 50);
        lightGray = al_map_rgb(100, 100, 100);
        light = al_map_rgb(200, 200, 200);
        display = NULL;
        score = NULL;
    }
    void loadFont(string fontPath) {
        regularFont.loadTtfFont(fontPath, 15);
        miniFont.loadTtfFont(fontPath, 10);
    }
    void linkScore(Score *score) {this->score = score;}
    void linkDisplay(Display *display) {this->display = display;}
    void linkLevel(SpeedLevel *level) {this->level = level;}
    void draw() {
        // Background
        al_draw_filled_rectangle(0, 0, display->getWidth(), 77, lightGray);
        // Border
        al_draw_rectangle(4, 4, display->getWidth()-3, 75-3, darkGray, 1.0);
        // Current score
        al_draw_text(miniFont.getPointer(), darkGray, 10 ,8 ,0 ,"CURR SCORE:");
        al_draw_textf(regularFont.getPointer(), light, 10, miniFont.getAscent()+8, 0, "%d",
                      score->getScore());
        // Highest score
        al_draw_text(miniFont.getPointer(), darkGray, 10,
                     regularFont.getLineHeight()+miniFont.getLineHeight()+8, 0, "HIGH SCORE:");
        al_draw_textf(regularFont.getPointer(), light, 10,
                      regularFont.getAscent()*2+miniFont.getLineHeight()+8, 0, "%d",
                      score->getHighScore());
        // Next block
        al_draw_rectangle(display->getWidth()/2-25, 10, display->getWidth()/2+25, 50+15, darkGray, 1.0);
        // Exp
        al_draw_text(miniFont.getPointer(), darkGray, display->getWidth()-10, 8,
                     ALLEGRO_ALIGN_RIGHT, "EXP:");
        al_draw_rectangle(display->getWidth()-10-miniFont.getTextWidth("CURR SCHORE:"), miniFont.getLineHeight()+10,
                          display->getWidth()-10, miniFont.getLineHeight()+20, darkGray, 1.0);
        al_draw_filled_rectangle(display->getWidth()-10-miniFont.getTextWidth("CURR SCHORE:")+2,
                                 miniFont.getLineHeight()+10+2,
                                 display->getWidth()-10-miniFont.getTextWidth("CURR SCHORE:")+2+(int)(74.0*(float)level->getExp()/(float)level->getExpToLevel()),
                                 miniFont.getLineHeight()+20-3, light);
        // Level
        al_draw_text(miniFont.getPointer(), darkGray, display->getWidth()-10,
                     regularFont.getLineHeight()+miniFont.getLineHeight()+8,
                     ALLEGRO_ALIGN_RIGHT, "LEVEL:");
        al_draw_textf(regularFont.getPointer(), light, display->getWidth()-10,
                      regularFont.getAscent()*2+miniFont.getLineHeight()+8,
                      ALLEGRO_ALIGN_RIGHT, "%d", level->getLevel());



    }

private:
    Display *display;
    Score *score;
    SpeedLevel *level;
    ALLEGRO_COLOR lightGray;
    ALLEGRO_COLOR darkGray;
    ALLEGRO_COLOR light;
    Font regularFont;
    Font miniFont;
};

#endif
