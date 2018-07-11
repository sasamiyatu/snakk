#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <utility>

const int kUp = 8;
const int kDown = 2;
const int kLeft = 4;
const int kRight = 6;

const int kMaxSnakeLength = 60;

void InitGrid(int, int);
void DrawBorder();
void DrawSnake();
void DrawFood();


#endif