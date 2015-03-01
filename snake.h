#ifndef SNAKE_H
#define SNAKE_H

#include "gameobject.h"

class Game;

class Snake : public GameObject
{
public:
  Snake(int r, int c, char id, Game* g, char dir) : GameObject(r, c, id, g) { m_dir = dir; m_updateCount = 7; }
  virtual ~Snake() {}
  virtual void doSomething() = 0;
  char getDir() const { return m_dir; }
  void setDir(char dir) { m_dir = dir; }
  char getPrevDir() const { return m_prevDir; }
  void setPrevDir(char prevDir) { m_prevDir = prevDir; }
  bool update()
  {
    if (m_updateCount == 7)
    {
      m_updateCount = 0;
      return true;
    }
    m_updateCount++;
    return false;
  }
private:
  char m_dir;
  char m_prevDir;
  int m_updateCount;
};

#endif
