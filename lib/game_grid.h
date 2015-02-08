#ifndef GAME_GRID_H_INCLUDED
#define GAME_GRID_H_INCLUDED

#include <iostream>

#include "enum_names.h"
#include "global_states.h"

#define GRIDW 20
#define GRIDH 22

class GameGrid {
public:
    GameGrid(Display *display) {
        for (int i = 0; i < GRIDW; i++)
            for (int j = 0; j < GRIDH; j++)
                grid[i][j] = B_Empty;
        soundDestroyLine = al_load_sample("res/sound/destroyLine.wav");
        soundDestroy4Lines = al_load_sample("res/sound/destroyLine4.wav");
        this->display = display;
    }
    void resetGrid() {
        for (int i = 0; i < GRIDW; i++)
            for (int j = 0; j < GRIDH; j++)
                grid[i][j] = B_Empty;
    }
    int getCell(int x, int y) {
        if (ERROR_HUNT) {
            if (x >= GRIDW) {
                std::cout << "Error in GameGrid.getCell() : x >= GRIDW, x = " <<
                          x << std::endl;
                return -1;
            } else if (x < 0) {
                std::cout << "Error in GameGrid.getCell() : x < 0, x = " <<
                          x << std::endl;
                return -1;
            }
            if (y >= GRIDH) {
                std::cout << "Error in GameGrid.getCell() : y >= GRIDH, y = " <<
                          y << std::endl;
                return -1;
            } else if (y < 0) {
                std::cout << "Error in GameGrid.getCell() : y < 0, y = " <<
                          x << std::endl;
                return -1;
            }
        }
        return grid[x][y];
    }
    void setCell(int x, int y, int value) {
        if (ERROR_HUNT) {
            if (x >= GRIDW) {
                std::cout << "Error in GameGrid.setCell() : x >= GRIDW, x = " <<
                          x << std::endl;
                return;
            } else if (x < 0) {
                std::cout << "Error in GameGrid.setCell() : x < 0, x = " <<
                          x << std::endl;
                return;
            }
            if (y >= GRIDH) {
                std::cout << "Error in GameGrid.setCell() : y >= GRIDH, y = " <<
                          y << std::endl;
                return;
            } else if (y < 0) {
                std::cout << "Error in GameGrid.setCell() : y < 0, y = " <<
                          x << std::endl;
                return;
            }
        }
        grid[x][y] = value;
    }
    bool isLineFull(int line) {
        bool isFull = true;
        for (int i = 0; i < GRIDW; i++)
            if (grid[i][line] == B_Empty) isFull = false;
        return isFull;
    }
    void destroyLine(int line) {
        for (int i = line; i > 1; i--)
            for(int j = 0; j < GRIDW; j++)
                grid[j][i] = grid[j][i-1];
    }
    void destroyMultiLines(int quantity, int lineNumbers[4]) {
        if (quantity == 4)
             al_play_sample(soundDestroy4Lines, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        else
             al_play_sample(soundDestroyLine, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        for(int i = 0; i < quantity; i++)
            destroyLine(lineNumbers[i]);
    }
    void destroySoundSamples() {
        al_destroy_sample(soundDestroyLine);
        al_destroy_sample(soundDestroy4Lines);
    }
    void draw() {
        // Fall line
        for(int i = 0; i < GRIDH; i++)
            for(int j = 0; j < GRIDW; j++)
                if (getCell(j, i)==B_Acive)
                    al_draw_filled_rectangle(3+j+j*20, 0, 3+j+j*20+20,
                    display->getHeight(),
                    al_map_rgb(110, 110, 110));
        // Blocks
        for(int i = 0; i < GRIDH; i++) {
            for(int j = 0; j < GRIDW; j++) {
                if(getCell(j, i)==B_Acive || getCell(j, i)== B_Passive) {
                    al_draw_filled_rectangle(3+j+j*20, 76+i+(i-2)*20, 3+j+j*20+20, 76+i+(i-2)*20+20,
                    darkGray);
                }
            }
        }
    }
    ~GameGrid() {
        destroySoundSamples();
    }

private:
    int grid[20][22];
    Display *display;
    ALLEGRO_SAMPLE *soundDestroyLine;
    ALLEGRO_SAMPLE *soundDestroy4Lines;
    ALLEGRO_COLOR darkGray = al_map_rgb(50, 50, 50);
    ALLEGRO_COLOR lightGray = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR light = al_map_rgb(200, 200, 200);
};

#endif
