class PacmanState {
private:
    int score;
    // bool gameover;
    int x;
    int y;

    // position by ghosts
    int x_red;
    int y_red;

    int x_orange;
    int y_orange;

    int x_blue;
    int y_blue;

    int x_pink;
    int y_pink;

    int power_up_weight;
    int power_ups_left;

public:
    PacmanGame() {
        score = 0;
        lives = 3;
        level = 1;
        gameover = false;
        x = 0;
        y = 0;
    }
    void changeX(int new_x) {
        x = new_x;
    }
    void changeY(int new_y) {
        y = new_y;
    }
    void increaseScore(int points) {
        score += points;
    }

    void decreaseLives() {
        lives--;
        if (lives == 0) {
            gameover = true;
        }
    }

    void nextLevel() {
        level++;
    }

    void gameOver() {
        gameover = true;
    }

    bool isGameOver() {
        return gameover;
    }

    int getScore() {
        return score;
    }

    int getLives() {
        return lives;
    }

    int getLevel() {
        return level;
    }
};
