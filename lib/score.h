#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#define POINTS_FOR_FULL_LINE      100
#define POINTS_FOR_PLACED_BLOCK   5
#define POINTS_FOR_4_FULL_LINES   120
#define POINTS_BONUS              20


class Score {
public:
    Score() {
        savedHighScore = load_highscore();
        highScore = savedHighScore;
        score = 0;
    }
    void saveHighScore() {
        save_highscore(highScore);
        savedHighScore = highScore;
    }
    int getScore() {
        return score;
    }
    void setScore(int score) {
        this->score = score;
    }
    void addScore(int score) {
        this->score = this->score + score;
    }
    int getHighScore() {
        return highScore;
    }
    bool isRecord() {
        if(score > highScore) {
            highScore = score;
            return true;
        }
        else
            return false;
    }
    void ifRecordSave() {
        if (highScore > savedHighScore)
            saveHighScore();
    }
    void loadHighScore() {
        highScore = load_highscore();
    }
    void resetScore() {
        score = 0;
    }
private:
    int savedHighScore;
    int highScore;
    int score;
};


#endif
