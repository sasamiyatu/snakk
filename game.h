#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <utility>

const int kUp = 8;
const int kDown = 2;
const int kLeft = 4;
const int kRight = 6;

const int kMaxSnakeLength = 60;

void InitGrid(int, int);
void DrawGrid();
void DrawBorder();
void DrawSnake();
void DrawFood();

class Grid {
public:
	Grid(int x_size, int y_size);
	void DrawGrid();
	std::pair<int, int> GetDimensions();
private:
	int width;
	int height;
	void Unit(int x, int y);
};

class Snake {
  public:
	  Snake() = delete;
	  Snake(Grid* grid);
	  void DrawSnake();
  private:
	  int x_pos;
	  int y_pos;
	  Grid* board;
	  int direction;
};

#endif