#ifndef GAME_H
#define GAME_H

#include <vector>
#include <allegro5/allegro_font.h>

class GameObject;
class Snake;
class Food;
class SnakeHead;
class SnakeBody;
class Wall;

class Game
{
public:
  Game();
  ~Game();
  void addNewGameObject(GameObject* gameobject) { m_gameobjects.push_back(gameobject); }
  void draw() const;
  void getInput();
  char getMap(int r, int c) const { return m_map[r][c]; }
  void setMap(int r, int c, char val) { m_map[r][c] = val; }
  Snake* getHead() const { return m_head; }
  Snake* getTail() const { return m_tail; }
  void setTail(Snake* newTail) { m_tail = newTail; }
  Food* getFood() const { return m_food; }
  void drawGameOverScreen() const;
  void drawStartScreen() const;
  bool isReset() const { return m_reset; }
  void setReset(bool val) { m_reset = val; }
  void reset();
  bool getKey(int pos) const { return m_key[pos]; }
  void setKey(int pos, bool val) { m_key[pos] = val; }
  void incrScore() { if (++m_score > m_highScore) m_highScore++; }
private:
  char** m_map;
  std::vector<GameObject*> m_gameobjects;
  Snake* m_head;
  Snake* m_tail;
  Food* m_food;
  bool* m_key;
  bool m_reset;
  ALLEGRO_FONT* m_font;
  int m_score;
  int m_highScore;
};

#endif
