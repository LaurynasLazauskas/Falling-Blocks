#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <iostream>

#include "game_grid.h"

#define LEFT -1
#define RIGHT 1

using std::cout;
using std::endl;

class Block {

public:
    Block(GameGrid *gameGrid) {
        grid = gameGrid;
        blockType = B_None;
        aboutToLand = false;
    }
    void setType(int type) {
        blockType = type;
    }
    void setCords(int x, int y, int index) {
        if (ERROR_HUNT) {
            if (index > 3 || index < 0) {
                std::cout << "Error in Block.setCords() : wrong index, index = " <<
                          index << std::endl;
                return;
            }
            if (x >= GRIDW) {
                std::cout << "Error in Block.setCords() : x >= GRIDW, x = " <<
                          x << std::endl;
                return;
            } else if (x < 0) {
                std::cout << "Error in Block.setCords() : x < 0, x = " <<
                          x << std::endl;
                return;
            }
            if (y >= GRIDH) {
                std::cout << "Error in Block.setCords() : y >= GRIDH, y = " <<
                          y << std::endl;
                return;
            } else if (y < 0) {
                std::cout << "Error in Block.setCords() : y < 0, y = " <<
                          x << std::endl;
                return;
            }
        }
        cords[0][index] = x;
        cords[1][index] = y;
    }
    int getType() {
        return blockType;
    }
    int getX(int index) {
        if (index > 3) {
            std::cout << "Error in Block.getX()" << std::endl;
            return -1;
        }
        return cords[0][index];
    }
    int getY(int index) {
        if (index > 3) {
            std::cout << "Error in Block.getY()" << std::endl;
            return -1;
        }
        return cords[1][index];
    }
    int getStartX() {
        return startingX;
    }
    int getStartY() {
        return startingY;
    }
    void setStartX(int x) {
        startingX = x;
    }
    void setStartY(int y) {
        startingY = y;
    }
    void spawn() {
        if (ERROR_HUNT) {
            if (blockType == B_None) {
                std::cout << "Error in Block.spawn() : blockType = B_None" << std::endl;
                return;
            }
            if (grid == NULL) {
                std::cout << "Error in Block.spawn() : grid = NULL" << std::endl;
                return;
            }
        }
        startingX = 8;
        startingY = 0;
        switch (blockType) {
        case B_I:
            grid->setCell(8, 1, B_Acive);
            grid->setCell(9, 1, B_Acive);
            grid->setCell(10, 1, B_Acive);
            grid->setCell(11, 1, B_Acive);
            setCords(8, 1, 0);
            setCords(9, 1, 1);
            setCords(10, 1, 2);
            setCords(11, 1, 3);
            break;
        case B_O:
            grid->setCell(9, 0, B_Acive);
            grid->setCell(10, 0, B_Acive);
            grid->setCell(9, 1, B_Acive);
            grid->setCell(10, 1, B_Acive);
            setCords(9, 0, 0);
            setCords(10, 0, 1);
            setCords(9, 1, 2);
            setCords(10, 1, 3);
            break;
        case B_J:
            grid->setCell(8, 0, B_Acive);
            grid->setCell(8, 1, B_Acive);
            grid->setCell(9, 1, B_Acive);
            grid->setCell(10, 1, B_Acive);
            setCords(8, 0, 0);
            setCords(8, 1, 1);
            setCords(9, 1, 2);
            setCords(10, 1, 3);
            break;
        case B_L:
            grid->setCell(10, 0, B_Acive);
            grid->setCell(8, 1, B_Acive);
            grid->setCell(9, 1, B_Acive);
            grid->setCell(10, 1, B_Acive);
            setCords(10, 0, 0);
            setCords(8, 1, 1);
            setCords(9, 1, 2);
            setCords(10, 1, 3);
            break;
        case B_T:
            grid->setCell(9, 0, B_Acive);
            grid->setCell(8, 1, B_Acive);
            grid->setCell(9, 1, B_Acive);
            grid->setCell(10, 1, B_Acive);
            setCords(9, 0, 0);
            setCords(8, 1, 1);
            setCords(9, 1, 2);
            setCords(10, 1, 3);
            break;
        case B_S:
            grid->setCell(9, 0, B_Acive);
            grid->setCell(10, 0, B_Acive);
            grid->setCell(8, 1, B_Acive);
            grid->setCell(9, 1, B_Acive);
            setCords(9, 0, 0);
            setCords(10, 0, 1);
            setCords(8, 1, 2);
            setCords(9, 1, 3);
            break;
        case B_Z:
            grid->setCell(8, 0, B_Acive);
            grid->setCell(9, 0, B_Acive);
            grid->setCell(9, 1, B_Acive);
            grid->setCell(10, 1, B_Acive);
            setCords(8, 0, 0);
            setCords(9, 0, 1);
            setCords(9, 1, 2);
            setCords(10, 1, 3);
            break;
        }
    }
    bool fall() {
        bool fell = true;
        for (int i = 0; i < 4; i++) {
            if (cords[1][i]+1 >= GRIDH ||
                    grid->getCell(cords[0][i], cords[1][i]+1) == B_Passive) {
                fell = false;
                break;
            }
        }
        if (fell) {
            for (int i = 0; i < 4; i++)
                grid->setCell(cords[0][i], cords[1][i], B_Empty);
            for (int i = 0; i < 4; i++) {
                setCords(getX(i), getY(i)+1, i);
                grid->setCell(cords[0][i], cords[1][i], B_Acive);
            }
            setStartY(startingY+1);
        } else
            for (int i = 0; i < 4; i++)
                grid->setCell(cords[0][i], cords[1][i], B_Passive);
        return fell;
    }
    bool peakFall() {
        bool fell = true;
        for (int i = 0; i < 4; i++) {
            if (cords[1][i]+1 >= GRIDH ||
                    grid->getCell(cords[0][i], cords[1][i]+1) == B_Passive) {
                fell = false;
                break;
            }
        }
        return fell;
    }
    bool moveBlock(int side) {
        bool moved = true;

        for (int i = 0; i < 4; i++) {
            if (grid->getCell(getX(i)+side, getY(i)) == B_Passive ||
                    getX(i)+side >= GRIDW || getX(i)+side < 0) {
                moved = false;
                break;
            }
        }
        if (moved) {
            for (int i = 0; i < 4; i++)
                grid->setCell(cords[0][i], cords[1][i], B_Empty);
            for (int i = 0; i < 4; i++) {
                setCords(getX(i)+side, getY(i), i);
                grid->setCell(cords[0][i], cords[1][i], B_Acive);
            }
            setStartX(startingX+side);
        }
        return moved;
    }
    bool rotateBlock(int direction) {
        bool rotated = true;
        Block testBlock(grid);
        int attempt = 0;
        int modifier = 0;
        int testI = 0;  // Test Block's coordinates index

        switch (blockType) {
        case B_O:
            break;
        case B_I:
            do {
                rotated = true;
                switch(attempt) {
                case 0:
                    modifier = 0;
                    break;
                case 1:
                    modifier = 1;
                    break;
                case 2:
                    modifier = -1;
                    break;
                case 3:
                    modifier = 2;
                    break;
                case 4:
                    modifier = -2;
                    break;
                }
                // Rotating testBlock
                for (int i = 0; i < 16; i++) {
                    if (checkRange(startingX+(i%4), CORD_X) &&
                            checkRange(startingY+(i/4), CORD_Y) &&
                            grid->getCell(startingX+(i%4), startingY+(i/4)) == B_Acive) {
                        if (direction == ROTATE_CW) {
                            if (!checkRange(startingX+(i/4)+modifier, CORD_X)) {
                                rotated = false;
                                break;
                            }
                            testBlock.setCords(startingX+(i/4)+modifier,
                                               startingY+3-(i%4), testI);
                            testI++;
                        } else if (direction == ROTATE_CCW) {
                            if (!checkRange(startingX+3-(i/4)+modifier, CORD_X)) {
                                rotated = false;
                                break;
                            }
                            testBlock.setCords(startingX+3-(i/4)+modifier,
                                               startingY+(i%4), testI);
                            testI++;
                        }
                    }
                }
                if (rotated)
                    for (int i = 0; i < 4; i++)
                        if (!checkRange(testBlock.getY(i), CORD_Y) ||
                                !checkRange(testBlock.getX(i), CORD_X) ||
                                grid->getCell(testBlock.getX(i), testBlock.getY(i)) == B_Passive)
                            rotated = false;
                testI = 0;
                attempt++;
            } while (rotated == false && attempt <= 4);
            if (rotated) {
                for (int i = 0; i < 4; i++)
                    grid->setCell(getX(i), getY(i), B_Empty);
                for (int i = 0; i < 4; i++) {
                    setCords(testBlock.getX(i), testBlock.getY(i), i);
                    grid->setCell(getX(i), getY(i), B_Acive);
                }
                startingX += modifier;
            }
            break;
        default:
            do {
                rotated = true;
                switch(attempt) {
                case 0:
                    modifier = 0;
                    break;
                case 1:
                    modifier = 1;
                    break;
                case 2:
                    modifier = -1;
                    break;
                case 3:
                    modifier = 2;
                    break;
                case 4:
                    modifier = -2;
                    break;
                }
                // Rotating testBlock
                for (int i = 0; i < 9; i++) {
                    if (checkRange(startingX+(i%3), CORD_X) &&
                            checkRange(startingY+(i/3), CORD_Y) &&
                            grid->getCell(startingX+(i%3), startingY+(i/3)) == B_Acive) {
                        if (direction == ROTATE_CW) {
                            if (!checkRange(startingX+(i/3)+modifier, CORD_X)) {
                                rotated = false;
                                break;
                            }
                            testBlock.setCords(startingX+(i/3)+modifier,
                                               startingY+2-(i%3), testI);
                            testI++;
                        } else if (direction == ROTATE_CCW) {
                            if (!checkRange(startingX+2-(i/3)+modifier, CORD_X)) {
                                rotated = false;
                                break;
                            }
                            testBlock.setCords(startingX+2-(i/3)+modifier,
                                               startingY+(i%3), testI);
                            testI++;
                        }
                    }
                }
                if (rotated)
                    for (int i = 0; i < 4; i++)
                        if (!checkRange(testBlock.getY(i), CORD_Y) ||
                                !checkRange(testBlock.getX(i), CORD_X) ||
                                grid->getCell(testBlock.getX(i), testBlock.getY(i)) == B_Passive)
                            rotated = false;
                testI = 0;
                attempt++;
            } while (rotated == false && attempt <= 4);
            if (rotated) {
                for (int i = 0; i < 4; i++)
                    grid->setCell(getX(i), getY(i), B_Empty);
                for (int i = 0; i < 4; i++) {
                    setCords(testBlock.getX(i), testBlock.getY(i), i);
                    grid->setCell(getX(i), getY(i), B_Acive);
                }
                startingX += modifier;
            }
            break;
        }
        return rotated;
    }
    bool isAboutToLand() {
        return aboutToLand;
    }
    void setAboutToLand(bool value) {
        aboutToLand = value;
    }
private:

    bool checkRange(int cord, int cordType) {
        bool successful = true;
        switch(cordType) {
        case CORD_X:
            if(cord < 0 || cord >= GRIDW) successful = false;
            break;
        case CORD_Y:
            if(cord < 0 || cord >= GRIDH) successful = false;
            break;
        }
        return successful;
    }

    bool aboutToLand;
    GameGrid *grid;
    int blockType;
    int startingX, startingY;
    int cords[2][4]; // 0 = X, 1 = Y; 4 little blocks
};


#endif
