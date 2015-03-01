#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "game.h"

class GameObject
{
public:
  GameObject(int r, int c, char id, Game* g)
  { m_row = r; m_col = c; m_id = id; m_game = g; if (id != 'h') g->setMap(r, c, id); }
  virtual ~GameObject() { m_game->setMap(m_row, m_col, '0'); }
  virtual void doSomething() = 0;
  Game* getGame() const { return m_game; }
  int getRow() const { return m_row; }
  void setRow(int r) { m_row = r; }
  int getCol() const { return m_col; }
  void setCol(int c) { m_col = c; }
  char getID() const { return m_id; }
private:
  Game* m_game;
  int m_row;
  int m_col;
  char m_id;
};

#endif
