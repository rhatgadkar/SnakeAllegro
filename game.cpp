#include "game.h"
#include "food.h"
#include "snakehead.h"
#include "allegro5/allegro_primitives.h"
#include "wall.h"
#include <vector>
#include "gameobject.h"
#include "snakebody.h"
#include "globals.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

char* itoa(int value, char* result, int base);

Game::Game()
{
  m_score = 0;
  m_highScore = 0;

  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_set_path_filename(path, "pirulen.ttf");
  m_font = al_load_ttf_font(al_path_cstr(path, '/'), 28, 0);
  if (!m_font)
  {
    fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
    exit(0);
  }
  al_destroy_path(path);

  m_reset = false;

  // initialize map
  m_map = new char*[NUM_ROWS];
  for (int r = 0; r < NUM_ROWS; r++)
  {
    m_map[r] = new char[NUM_COLS];
    for (int c = 0; c < NUM_COLS; c++)
      m_map[r][c] = '0';
  }

  // set walls north and south
  for (int c = 0; c < NUM_COLS; c++)
    if (m_map[1][c] == '0')
      m_gameobjects.push_back(new Wall(1, c, this));
  for (int c = 0; c < NUM_COLS; c++)
    if (m_map[NUM_ROWS - 1][c] == '0')
     m_gameobjects.push_back(new Wall(NUM_ROWS - 1, c, this));

  // set walls west and east
  for (int r = 1; r < NUM_ROWS; r++)
    if (m_map[r][0] == '0')
      m_gameobjects.push_back(new Wall(r, 0, this));
  for (int r = 1; r < NUM_ROWS; r++)
    if (m_map[r][NUM_COLS - 1] == '0')
      m_gameobjects.push_back(new Wall(r, NUM_COLS - 1, this));

  m_key = new bool[4];
  m_key[0] = false; m_key[1] = false; m_key[2] = false; m_key[3] = false;

  m_gameobjects.push_back(new Food(10, 15, this));
  m_food = (Food*)m_gameobjects[m_gameobjects.size() - 1];
  m_gameobjects.push_back(new SnakeHead(10, 10, this, 'w'));
  m_head = (Snake*)m_gameobjects[m_gameobjects.size() - 1];
  m_tail = m_head;
}

Game::~Game()
{
  al_destroy_font(m_font);

  delete m_key;

  m_head = NULL;
  m_tail = NULL;

  for (size_t k = 0; k < m_gameobjects.size(); k++)
    delete m_gameobjects[k];
  m_gameobjects.clear();

  for (int r = 0; r < NUM_ROWS; r++)
    delete [] m_map[r];
}

void Game::reset()
{
  if (m_score > m_highScore)
    m_highScore = m_score;
  m_score = 0;

  m_reset = true;

  m_head = NULL;
  m_tail = NULL;

  for (size_t k = 0; k < m_gameobjects.size(); k++)
      delete m_gameobjects[k];
  m_gameobjects.clear();

  // set walls north and south
  for (int c = 0; c < NUM_COLS; c++)
    if (m_map[1][c] == '0')
      m_gameobjects.push_back(new Wall(1, c, this));
  for (int c = 0; c < NUM_COLS; c++)
    if (m_map[NUM_ROWS - 1][c] == '0')
     m_gameobjects.push_back(new Wall(NUM_ROWS - 1, c, this));

  // set walls west and east
  for (int r = 1; r < NUM_ROWS; r++)
    if (m_map[r][0] == '0')
      m_gameobjects.push_back(new Wall(r, 0, this));
  for (int r = 1; r < NUM_ROWS; r++)
    if (m_map[r][NUM_COLS - 1] == '0')
      m_gameobjects.push_back(new Wall(r, NUM_COLS - 1, this));

  m_gameobjects.push_back(new Food(10, 15, this));
  m_food = (Food*)m_gameobjects[m_gameobjects.size() - 1];
  m_gameobjects.push_back(new SnakeHead(10, 10, this, 'w'));
  m_head = (Snake*)m_gameobjects[m_gameobjects.size() - 1];
  m_tail = m_head;
}

void Game::getInput()
{
  for (size_t k = 0; k < m_gameobjects.size(); k++)
  {
    m_gameobjects[k]->doSomething();
    if (m_reset)
      return;
  }
}

void Game::draw() const
{
  al_clear_to_color(al_map_rgb(0, 0, 0));

  for (size_t k = 0; k < m_gameobjects.size(); k++)
  {
    char id = m_gameobjects[k]->getID();
    int row = m_gameobjects[k]->getRow();
    int col = m_gameobjects[k]->getCol();
    float x1 = col * TILE_WIDTH;
    float x2 = ((col + 1) * TILE_WIDTH) - 1;
    float y1 = row * TILE_HEIGHT;
    float y2 = ((row + 1) * TILE_HEIGHT) - 1;

    switch (id)
    {
      case 'f':
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 0));
        break;
      case 'w':
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0));
        break;
      case 'h':
      case 'b':
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
        break;
    }
  }

  char score[3];
  itoa(m_score, score, 10);
  al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 1.15, 0, ALLEGRO_ALIGN_RIGHT, "Score: ");
  al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH, 0, ALLEGRO_ALIGN_RIGHT, score);
  al_draw_text(m_font, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "HighScore: ");
  if (m_score == m_highScore)
    al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2.2, 0, ALLEGRO_ALIGN_LEFT, score);
  else
  {
    char highScore[3];
    itoa(m_highScore, highScore, 10);
    al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 0, ALLEGRO_ALIGN_LEFT, highScore);
  }

  al_flip_display();
}

void Game::drawGameOverScreen() const
{
  al_clear_to_color(al_map_rgb(0, 0, 0));

  char highScore[3];
  itoa(m_highScore, highScore, 10);
  al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 5, SCREEN_HEIGHT / 10, ALLEGRO_ALIGN_LEFT, "HighScore: ");
  al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 1.45, SCREEN_HEIGHT / 10, ALLEGRO_ALIGN_RIGHT, highScore);
  al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press Enter to retry");

  al_flip_display();
}

void Game::drawStartScreen() const
{
  al_clear_to_color(al_map_rgb(0, 0, 0));

  al_draw_text(m_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press Enter to start");

  al_flip_display();
}

/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.
	 */
	char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}
