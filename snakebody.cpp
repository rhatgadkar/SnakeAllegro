#include "snakebody.h"
#include "snake.h"
#include "game.h"
#include "gameobject.h"

void SnakeBody::doSomething()
{
  if (!update())
    return;

  Game* game = getGame();
  Snake* parent = getParent();
  int row = getRow();
  int col = getCol();

  game->setMap(row, col, '0');

  setPrevDir(getDir());

  char newCurrDir = parent->getPrevDir();
  setDir(newCurrDir);

  switch (newCurrDir)
  {
  case 'n':
    setRow(--row);
    break;
  case 's':
    setRow(++row);
    break;
  case 'e':
    setCol(++col);
    break;
  default: // case'w':
    setCol(--col);
    break;  
  }

  game->setMap(row, col, 'b');
}
