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
											  std::make_pair(20, 21),
	                                          std::make_pair(20, 22), 
	                                          std::make_pair(20, 23),
	                                          std::make_pair(20, 24)};

void Unit(int, int);

void InitGrid(int x, int y) {
	grid.first = x;
	grid.second = y;
}

void DrawGrid() {
	for (int x = 0; x < grid.first; ++x) {
		for (int y = 0; y < grid.second; ++y) {
			Unit(x, y);
		}
	}
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

void Unit(int x, int y) {
	
	if (x == 0 || y == 0 || x == grid.first-1 || y == grid.second-1) {
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
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
		printf("game over\n");
		return;
	}
	for (std::deque<std::pair<int, int>>::iterator it = snake_body.begin() + 1; it != snake_body.end(); ++it) {
		if (snake_body.front().first == it->first && snake_body.front().second == it->second) {
			game_over = true;
			printf("game over\n");
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


Snake::Snake(Grid * grid)
{
	x_pos = (grid->GetDimensions()).first;
	y_pos = (grid->GetDimensions()).second;
	board = grid;
	direction = kRight;
}

void Snake::DrawSnake()
{
	if (direction == kUp) {
		++y_pos;
	}
	else if (direction == kDown) {
		--y_pos;
	}
	else if (direction == kLeft) {
		--x_pos;
	}
	else if (direction == kRight) {
		++x_pos;
	}
	glRectd(x_pos, y_pos, x_pos + 1, y_pos + 1);

}

Grid::Grid(int x_size, int y_size)
{
	width = x_size;
	height = y_size;
}

void Grid::DrawGrid()
{
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			this->Unit(x, y);
		}
	}
}

std::pair<int, int> Grid::GetDimensions()
{
	return std::make_pair(width, height);
}


void Grid::Unit(int x, int y)
{
	if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();

}
