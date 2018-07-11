#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <string>
#include "game.h"


const int kColumns = 40;
const int kRows = 40;
const int kFrameRate = 10;

extern int snake_direction;
extern int score;

bool game_over = false;

void DisplayCallback();
void ReshapeCallback(int w, int h);
void TimerCallback(int);
void KeyboardCallback(int, int, int);

void Init() {
	glClearColor(0.231, 0.58, 0.0, 1.0); //3B9400 Green
	InitGrid(kColumns, kRows);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//glutInitWindowPosition();
	glutInitWindowSize(500, 500);
	glutCreateWindow("SNAAAAAAAKE");
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutTimerFunc(0, TimerCallback, 0);
	glutSpecialFunc(KeyboardCallback);
	Init();
	glutMainLoop();

	return 0;
}


void DisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawBorder();
	DrawSnake();
	DrawFood();
	glutSwapBuffers();
	if (game_over == true) {
		std::string score_str = std::to_string(score);
		std::string str = "Your score was: " + score_str;
		MessageBox(NULL, str.c_str(), "GAME OVER", 0);
		exit(0);
	}
}

void ReshapeCallback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, kColumns, 0.0, kRows, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void TimerCallback(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / kFrameRate, TimerCallback, 0);
}

void KeyboardCallback(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP:
		if (snake_direction != kDown) {
			snake_direction = kUp;
		}
		break;
	case GLUT_KEY_DOWN:
		if (snake_direction != kUp) {
			snake_direction = kDown;
		}
		break;
	case GLUT_KEY_LEFT:
		if (snake_direction != kRight) {
			snake_direction = kLeft;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (snake_direction != kLeft) {
			snake_direction = kRight;
		}
		break;
	}
}