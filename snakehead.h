#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "snake.h"

class Game;

class SnakeHead : public Snake
{
public:
  SnakeHead(int r, int c, Game* g, char dir) : Snake(r, c, 'h', g, dir) {}
  virtual ~SnakeHead() {}
  virtual void doSomething();
private:
 // void inFood(Game* game, int row, int col);
 // void moveHead(Game* game, int row, int col, char dir);
};

#endif
