#include "Snake.h"
#include "Arduino.h"
#include <Adafruit_PCD8544.h>

Snake::Snake(int xSpace, int ySpace, int ppg, int delayms, int maxSnakeParts=0, uint8_t randomPin=A1){
  Snake::xSpace = xSpace;
  Snake::ySpace = ySpace;
  Snake::ppg = ppg;
  Snake::delayms = delayms;
  Snake::nextDir = 0;
  bool b = maxSnakeParts == 0;
  maxNumParts = (!b * maxSnakeParts) + ((int)b * ySpace * xSpace * 0.25);
  int parts[maxNumParts];
  snakeParts = parts;
  Snake::randomPin = randomPin;
  pinMode(randomPin, INPUT);
}

void Snake::Start(){
  Snake::PlaySpace = String();
  for(int i = 0; i < xSpace * ySpace; i++) Snake::PlaySpace += '.';
  //need random input for the randomSeed
  randomSeed(analogRead(randomPin));
  float rndm = (float)random(1000)/1000;
  Serial.print("rndm: ");
  Serial.println(rndm);
  int randInt = rndm * Snake::ySpace * Snake::xSpace;
  snakeParts[0] = randInt;
  nextDir = rndm*4;
  snakePartNum = 3;
  for(int i = 0; i < 2; i++){
    snakeParts[i+1] = -getNextPos(getDirInt(nextDir), snakeParts[i]);
  }
  state = CONTINUE;
  placeRandom('p');
}

int Snake::getDirInt(int Dir){
  //row: x, column: y
  switch(Dir){
    case LEFT:
      return -1;
    case RIGHT:
      return 1;
    case UP:
      return -Snake::xSpace;
    case DOWN:
      return Snake::xSpace;
  }
  return 0;
}

void Snake::NextMove(int dir){
  int oppositeDir[4] = {UP, DOWN, LEFT, RIGHT};
  bool b = oppositeDir[dir] == nextDir;
  nextDir = (!b * dir) + (b * nextDir);
}

void Snake::Update(){
  //for later
  if(state == GAME_OVER){
    //return;
  }
  int dir = getDirInt(nextDir);
  int newPos = getNextPos(dir);
  state = CheckPos(newPos);
  Move(newPos);
}

int Snake::binarySearch(int * sortedArray, int target){
  //return -1 if not found
}

/*
TODO: this need to be changed
*/
void Snake::placeRandom(char c){
  bool truen = true;
  while(truen){
    randomSeed(millis()*micros()*analogRead(randomPin));
    float rndm = (float)random(1000)/1000;
    int pos = rndm*xSpace*ySpace;
    if(PlaySpace.charAt(pos) == '.'){
      PlaySpace.setCharAt(pos, c);
      truen = false;
    }
  }
}

/*
TODO: give the code

might implement sorting algorithm for easier search
*/
int Snake::CheckPos(int newPos){
  //use char 'p' as food
  switch(PlaySpace.charAt(newPos)){
    case 's':
      PlaySpace = String();
      return GAME_OVER;
    case 'p':
      if(snakePartNum < maxNumParts){
        snakePartNum++;
        snakeParts[snakePartNum-1] = snakeParts[snakePartNum-2] + getNextPos(getDirInt(nextDir));
        placeRandom('p');
        addScore();
      }
      break;
  }

  //new code here
  if(newPos == pointPos){
    
  }
  int * sortedSnake = sortLowToHigh(snakeParts);
  int at = binarySearch(sortedSnake, newPos);
  switch(at){
    case -1:
      break;
    default:
      break;
  }

  return CONTINUE;
}

void Snake::addScore(){
  //Score += abs(snakePartNum*((double)constrain(millis() - lastScoring,0,secondMaxToScore*1000)/(secondMaxToScore*1000)));
  lastScoring = millis();
}

void Snake::GameOverHandle(){
  PlaySpace = String();
  state = GAME_OVER;
}

//TODO: give the code
String Snake::getString(){
  String res = PlaySpace;
  res += "Score: " + String(Score) + "\n";
  res.setCharAt(pointPos, 'p');
  for(int i = 0; i < snakePartNum; i++) res.setCharAt(snakeParts[i], 's');
  return res;
}

void Snake::SendToLCD(Adafruit_PCD8544 *lcd){
  for(int y = 0; y < ySpace; y++){
    for(int x = 0; x < xSpace; x++){
      int col = BLACK;
      if(Snake::PlaySpace.charAt(x+y) == '.') col = WHITE;
      lcd->writeFillRect(x*ppg, y*ppg, ppg, ppg, col);
    }
  }
  lcd->display();
}

int Snake::getNextPos(int increment){
  return Snake::getNextPos(increment, snakeParts[0]);
}

int Snake::getNextPos(int increment, int pos){
  int nPos = 0;
  switch(nextDir){
    //x Axis
    case LEFT:
    case RIGHT:
      nPos = pos%xSpace+increment;
      if(nPos >= xSpace){
        increment = -(xSpace-1);
      }
      else if(nPos < 0){
        increment = xSpace-1;
      }
      break;
    
    //y Axis
    case UP:
    case DOWN:
      nPos = pos+increment;
      if(nPos >= xSpace*ySpace){
        increment = -(xSpace*(ySpace-1));
      }
      else if(nPos < 0){
        increment = xSpace*(ySpace-1);
      }
      break;
  }
  return pos+increment;
}

//TODO: give the code (done)
void Snake::Move(int newPos){
  for(int i = 0; i < snakePartNum; i++){
    int posBfr = snakeParts[i];
    snakeParts[i] = newPos;
    newPos = posBfr;
  }
}