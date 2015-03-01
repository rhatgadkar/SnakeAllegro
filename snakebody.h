#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "snake.h"

class Game;

class SnakeBody : public Snake
{
public:
  SnakeBody(int r, int c, Game* g, char dir, Snake* parent) : Snake(r, c, 'b', g, dir) { m_parent = parent; }
  virtual ~SnakeBody() {}
  virtual void doSomething();
  Snake* getParent() { return m_parent; }
private:
  Snake* m_parent;
};

#endif
