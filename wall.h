#ifndef WALL_H
#define WALL_H

#include "gameobject.h"

class Game;

class Wall : public GameObject
{
public:
  Wall(int r, int c, Game* g) : GameObject(r, c, 'w', g) {}
  virtual ~Wall() {}
  virtual void doSomething() {}
};

#endif
