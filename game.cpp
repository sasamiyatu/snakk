#include <GL\glew.h>
#include <GL\freeglut.h>
#include "game.h"
#include <utility>
#include <ctime>
#include <deque>

std::pair<int, int> grid;
std::pair<int, int> food_location;
int snake_length = 5;
int score = 0;
int snake_direction = kRight;
extern bool game_over;
bool food = true;

std::deque<std::pair<int, int>> snake_body = {std::make_pair(20, 20), 
											  std::make_pair(19, 20),
	                                          std::make_pair(18, 20), 
	                                          std::make_pair(17, 20),
	                                          std::make_pair(16, 20)};

void Unit(int, int);

void InitGrid(int x, int y) {
	grid.first = x;
	grid.second = y;
}


void DrawBorder() {
	glColor3f(1.0, 0.0, 0.0);
	for (int x = 0; x < grid.first; ++x) {
		glRectd(x, 0, x + 1, 1);
		glRectd(x, 39, x + 1, 40);
	}
	for (int y = 0; y < grid.second; ++y) {
		glRectd(0, y, 1, y + 1);
		glRectd(39, y, 40, y + 1);
	}
}


void DrawSnake() {
	if (snake_direction == kUp) {
		snake_body.push_front(std::make_pair(snake_body.front().first, snake_body.front().second + 1));
		snake_body.pop_back();
	} else if (snake_direction == kDown) {
		snake_body.push_front(std::make_pair(snake_body.front().first, snake_body.front().second - 1));
		snake_body.pop_back();
	}
	else if (snake_direction == kLeft) {
		snake_body.push_front(std::make_pair(snake_body.front().first - 1, snake_body.front().second));
		snake_body.pop_back();
	}
	else if (snake_direction == kRight) {
		snake_body.push_front(std::make_pair(snake_body.front().first + 1, snake_body.front().second));
		snake_body.pop_back();
	}
	glColor3f(0.0, 0.0, 0.0);
	for (std::deque<std::pair<int, int>>::iterator it = snake_body.begin(); it != snake_body.end(); ++it) {
		glRectd(it->first, it->second, it->first + 1, it->second + 1);
	}
	if (snake_body.front().first == 0 || snake_body.front().first == grid.first - 1 || 
		snake_body.front().second == 0 || snake_body.front().second == grid.second - 1) {
		game_over = true;
		return;
	}
	for (std::deque<std::pair<int, int>>::iterator it = snake_body.begin() + 1; it != snake_body.end(); ++it) {
		if (snake_body.front().first == it->first && snake_body.front().second == it->second) {
			game_over = true;
			return;
		}
	}
	if (snake_body.front().first == food_location.first && snake_body.front().second == food_location.second) {
		if (snake_length < kMaxSnakeLength) {
			++snake_length;
			snake_body.push_back(snake_body.back());
		}
		++score;
		food = true;
	}
}

void DrawFood()
{
	if (food == true) {
		int max_x = grid.first - 2;
		int max_y = grid.second - 2;
		int min_pos = 1;
		srand(time(NULL));
		food_location.first = min_pos + rand() % (max_x - min_pos);
		food_location.second = min_pos + rand() % (max_y - min_pos);
		food = false;
	}
	glColor3f(0, 0, 1.0);
	glRectf(food_location.first, food_location.second, food_location.first + 1, food_location.second + 1);
}




