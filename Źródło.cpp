#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX1, fruitY1, fruitX2, fruitY2, fruitX3, fruitY3, fruitX4, fruitY4, fruitX5, fruitY5, score;
int tailX[400], tailY[400];
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;
void Setup() {
	srand(time(NULL));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX1 = rand() % width;
	fruitY1 = rand() % height;
	fruitX2 = rand() % width;
	fruitY2 = rand() % height;
	fruitX3 = rand() % width;
	fruitY3 = rand() % height;
	fruitX4 = rand() % width;
	fruitY4 = rand() % height;
	fruitX5 = rand() % width;
	fruitY5 = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "@";
			else if (i == fruitY1 && j == fruitX1)
				cout << "O";
				else if (i == fruitY2 && j == fruitX2)
				cout << "O";
				else if (i == fruitY3 && j == fruitX3)
				cout << "O";
				else if (i == fruitY4 && j == fruitX4)
				cout << "O";
				else if (i == fruitY5 && j == fruitX5)
				cout << "O";
			else {
				bool print = false;
				for (int k = 0; k < score; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()){
		switch (_getch()) {
		case 'a':
			if (dir == RIGHT)
				break;
			dir = LEFT;
			break;
		case 'd':
			if (dir == LEFT)
				break;
			dir = RIGHT;
			break;
		case 'w':
			if (dir == DOWN)
				break;
			dir = UP;
			break;
		case 's':
			if (dir == UP)
				break;
			dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < score; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width-1 || x < 0 || y < 0 || y > height-1)
		gameOver = true;
	for (int i = 0; i < score; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX1 && y == fruitY1) {
		score++;
		loop:	//sprawdza czy jablko nie pojawia sie w wezu
			fruitX1 = rand() % width;
			fruitY1 = rand() % height;
			int i = 0;
			while (i <= score) {	
				if ((fruitX1 == x && fruitY1 == y) || (fruitX1 == tailX[i] && fruitY1 == tailY[i]))
					goto loop;
				else
					i++;
			}
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(20); // spowalnia gre, uniezaleznia czas gry od mocy obliczeniowej procesora
	}
	system("pause");
	return 0;
}
