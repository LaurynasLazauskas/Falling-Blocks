#ifndef SIMPLE_ENCRYPTION_H_INCLUDED
#define SIMPLE_ENCRYPTION_H_INCLUDED

#include <fstream>

using std::ofstream;
using std::ifstream;

void save_highscore(int score) {
    ofstream file("res/data/hs.data");
    int testNumber = score;
    for (int i = 0; i < 5; i++)
        testNumber += i*(score/(i+1));
    file << testNumber;
    file << " ";
    file << score;
    file.close();
}

int load_highscore() {
    ifstream file("res/data/hs.data");
    int score;
    int readTestNumber;
    int testNumber;

    file >> readTestNumber;
    file >> score;

    file.close();

    testNumber = score;
    for (int i = 0; i < 5; i++)
        testNumber += i*(score/(i+1));
    if (testNumber == readTestNumber)
        return score;

    save_highscore(0);
    return 0;
}



#endif
