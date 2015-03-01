#ifndef FOOD_H
#define FOOD_H

#include "gameobject.h"

class Game;

class Food : public GameObject
{
public:
  Food(int r, int c, Game* g) : GameObject(r, c, 'f', g) {}
  virtual ~Food() {}
  virtual void doSomething() {}
};

#endif
