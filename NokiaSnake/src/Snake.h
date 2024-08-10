#include <Arduino.h>
#include "Adafruit_PCD8544.h"

#define LEFT 3
#define RIGHT 2
#define UP 1
#define DOWN 0

#define GAME_OVER 0
#define CONTINUE 1

class Snake{
    public:
    Snake(int x, int y, int ppg, int delayms, int maxSnakeParts=0, uint8_t randomPin=A1);
    void Start();
    void Update();
    void SendToLCD(Adafruit_PCD8544 *lcd);
    String getString();
    void NextMove(int dir);
    private:
    int binarySearch(int * sortedArray, int target);
    int * sortLowToHigh(int * arrays);
    void addScore();
    void placeRandom(char c);
    void GameOverHandle();
    int CheckPos(int newPos);
    void Move(int newPos);
    int getNextPos(int increment, int pos);
    int getNextPos(int increment);
    int getDirInt(int Dir);
    String PlaySpace;
    const int newSnakeLen = 3;
    int manyMoves;
    int nextDir;
    long Score, lastScoring;
    uint8_t secondMaxToScore = 5;
    int xSpace, ySpace, ppg, delayms, snakePartNum, maxNumParts, state;
    uint8_t randomPin;

    int * snakeParts, sortedPartPos;
    int pointPos;
};