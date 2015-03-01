#include "snakehead.h"
#include "game.h"
#include "food.h"
#include "snakebody.h"
#include "gameobject.h"
#include "globals.h"
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "globals.h"

void inFood(Game* game, int row, int col);
void moveHead(Game* game, int row, int col, char dir, SnakeHead* head);

void SnakeHead::doSomething()
{
  if (!update())
    return;

  Game* game = getGame();
  int row = getRow();
  int col = getCol();
  char mapVal = game->getMap(row, col);
  char dir = getDir();

  setPrevDir(dir);

  if (mapVal == 'f')
    inFood(game, row, col);
  if (mapVal == 'w' || mapVal == 'b')
  {
    game->reset();
    return;
  }

  moveHead(game, row, col, dir, this);
}

void inFood(Game* game, int row, int col)
{
  game->incrScore();
  // add new tail
  Snake* tail = game->getTail();
  char tailDir = tail->getDir();
  int tailRow = tail->getRow();
  int tailCol = tail->getCol();

  int newSnakeRow, newSnakeCol;
  char newSnakeDir = tailDir;
  switch (tailDir)
  {
  case 'n':
    newSnakeRow = tailRow + 1;
    newSnakeCol = tailCol;
    break;
  case 's':
    newSnakeRow = tailRow - 1;
    newSnakeCol = tailCol;
    break;
  case 'e':
    newSnakeRow = tailRow;
    newSnakeCol = tailCol - 1;
    break;
  case 'w':
    newSnakeRow = tailRow;
    newSnakeCol = tailCol + 1;
    break;
  }

  SnakeBody* newSnake = new SnakeBody(newSnakeRow, newSnakeCol, game, newSnakeDir, tail);
  game->addNewGameObject(newSnake);
  game->setTail(newSnake);

  // set new food location
  Food* food = game->getFood();
  int foodRow = food->getRow();
  int foodCol = food->getCol();

  int newFoodRow, newFoodCol;

  srand(time(NULL));
  do
  {
    newFoodRow = rand() % (NUM_ROWS - 1) + 1;
    newFoodCol = rand() % (NUM_COLS - 1) + 1;
  } while ((newFoodRow == row && newFoodCol == col) || (game->getMap(newFoodRow, newFoodCol) != '0'));

  game->setMap(foodRow, foodCol, '0');
  food->setRow(newFoodRow);
  food->setCol(newFoodCol);
  game->setMap(newFoodRow, newFoodCol, 'f');
}

void moveHead(Game* game, int row, int col, char dir, SnakeHead* head)
{
  char newDir = dir;
  int newRow = row;
  int newCol = col;

  switch (dir)
  {
  case 'w':
    if (game->getKey(KEY_UP) && !game->getKey(KEY_DOWN) && !game->getKey(KEY_RIGHT) && !game->getKey(KEY_LEFT))
      newDir = 'n';
    else if (game->getKey(KEY_DOWN) && !game->getKey(KEY_UP) && !game->getKey(KEY_RIGHT) && !game->getKey(KEY_LEFT))
      newDir = 's';
    break;
  case 'e':
    if (game->getKey(KEY_UP) && !game->getKey(KEY_DOWN) && !game->getKey(KEY_RIGHT) && !game->getKey(KEY_LEFT))
      newDir = 'n';
    else if (game->getKey(KEY_DOWN) && !game->getKey(KEY_UP) && !game->getKey(KEY_RIGHT) && !game->getKey(KEY_LEFT))
      newDir = 's';
    break;
  case 'n':
    if (game->getKey(KEY_LEFT) && !game->getKey(KEY_RIGHT) && !game->getKey(KEY_UP) && !game->getKey(KEY_DOWN))
      newDir = 'w';
    else if (game->getKey(KEY_RIGHT) && !game->getKey(KEY_LEFT) && !game->getKey(KEY_UP) && !game->getKey(KEY_DOWN))
      newDir = 'e';
    break;
  case 's':
    if (game->getKey(KEY_LEFT) && !game->getKey(KEY_RIGHT) && !game->getKey(KEY_UP) && !game->getKey(KEY_DOWN))
      newDir = 'w';
    else if (game->getKey(KEY_RIGHT) && !game->getKey(KEY_LEFT) && !game->getKey(KEY_UP) && !game->getKey(KEY_DOWN))
      newDir = 'e';
    break;
  }
  head->setDir(newDir);

  switch (newDir)
  {
    case 'n':
      head->setRow(--newRow);
      break;
    case 's':
      head->setRow(++newRow);
      break;
    case 'w':
      head->setCol(--newCol);
      break;
    case 'e':
      head->setCol(++newCol);
      break;
  }
}
