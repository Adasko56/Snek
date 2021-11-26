#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX1, fruitY1, fruitX2, fruitY2, fruitX3, fruitY3, fruitX4, fruitY4, fruitX5, fruitY5, score, smok;
int tailX[400], tailY[400];
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
void Setup() {
	srand(time(NULL));
	gameOver = false;
	dir = STOP;
	cout << "whatever";
	x = width / 2;
	y = height / 2;
Fruit1:
	fruitX1 = rand() % width;
	fruitY1 = rand() % height;
	if (fruitX1 == x && fruitY1 == y)
		goto Fruit1;
Fruit2:
	fruitX2 = rand() % width;
	fruitY2 = rand() % height;
	if ((fruitX2 == x && fruitY2 == y) || (fruitX2 == fruitX1 && fruitY2 == fruitY1))
		goto Fruit2;
Fruit3:
	fruitX3 = rand() % width;
	fruitY3 = rand() % height;
	if ((fruitX3 == x && fruitY3 == y) || (fruitX3 == fruitX1 && fruitY3 == fruitY1) || (fruitX3 == fruitX2 && fruitY3 == fruitY2))
		goto Fruit3;
Fruit4:
	fruitX4 = rand() % width;
	fruitY4 = rand() % height;
	if ((fruitX4 == x && fruitY4 == y) || (fruitX4 == fruitX1 && fruitY4 == fruitY1) || (fruitX4 == fruitX2 && fruitY4 == fruitY2) || (fruitX4 == fruitX3 && fruitY4 == fruitY3))
		goto Fruit4;
Fruit5:
	fruitX5 = rand() % width;
	fruitY5 = rand() % height;
	if ((fruitX5 == x && fruitY4 == y) || (fruitX5 == fruitX5 && fruitY5 == fruitY1) || (fruitX5 == fruitX2 && fruitY5 == fruitY2) || (fruitX5 == fruitX3 && fruitY5 == fruitY3) || (fruitX5 == fruitX4 && fruitY5 == fruitY4))
		goto Fruit5;
	score = 0;
}

void Draw() {
	system("cls");
	cout << setw(2);
	for (int i = 0; i < width + 2; i++)
		cout << "#" << setw(2);
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#" << setw(2);
			if (i == y && j == x)
				cout << "@" << setw(2);
			else if (i == fruitY1 && j == fruitX1)
				cout << "O" << setw(2);
			else if (i == fruitY2 && j == fruitX2)
				cout << "O" << setw(2);
			else if (i == fruitY3 && j == fruitX3)
				cout << "O" << setw(2);
			else if (i == fruitY4 && j == fruitX4)
				cout << "O" << setw(2);
			else if (i == fruitY5 && j == fruitX5)
				cout << "O" << setw(2);
			else {
				bool print = false;
				for (int k = 0; k < score; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o" << setw(2);
						print = true;
					}
				}
				if (!print)
					cout << " " << setw(2);
			}
			if (j == width - 1)
				cout << "#" << setw(2);
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#" << setw(2);
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) {
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
	if (x > width - 1 || x < 0 || y < 0 || y > height - 1)
		gameOver = true;
	for (int i = 0; i < score; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX1 && y == fruitY1) {
		score++;
	loop1:	//sprawdza czy jablko nie pojawia sie w wezu
		fruitX1 = rand() % width;
		fruitY1 = rand() % height;
		int i = 0;
		while (i <= score) {
			if ((fruitX1 == x && fruitY1 == y) || (fruitX1 == tailX[i] && fruitY1 == tailY[i]))
				goto loop1;
			else
				i++;
		}
	}
	if (x == fruitX2 && y == fruitY2) {
		score++;
	loop2:	//sprawdza czy jablko nie pojawia sie w wezu
		fruitX2 = rand() % width;
		fruitY2 = rand() % height;
		int i = 0;
		while (i <= score) {
			if ((fruitX2 == x && fruitY2 == y) || (fruitX2 == tailX[i] && fruitY2 == tailY[i]))
				goto loop2;
			else
				i++;
		}
	}

	if (x == fruitX3 && y == fruitY3) {
		score++;
	loop3:	//sprawdza czy jablko nie pojawia sie w wezu
		fruitX3 = rand() % width;
		fruitY3 = rand() % height;
		int i = 0;
		while (i <= score) {
			if ((fruitX3 == x && fruitY3 == y) || (fruitX3 == tailX[i] && fruitY3 == tailY[i]))
				goto loop3;
			else
				i++;
		}
	}
	if (x == fruitX4 && y == fruitY4) {
		score++;
	loop4:	//sprawdza czy jablko nie pojawia sie w wezu
		fruitX4 = rand() % width;
		fruitY4 = rand() % height;
		int i = 0;
		while (i <= score) {
			if ((fruitX4 == x && fruitY4 == y) || (fruitX4 == tailX[i] && fruitY4 == tailY[i]))
				goto loop4;
			else
				i++;
		}
	}
	if (x == fruitX5 && y == fruitY5) {
		score++;
	loop5:	//sprawdza czy jablko nie pojawia sie w wezu
		fruitX5 = rand() % width;
		fruitY5 = rand() % height;
		int i = 0;
		while (i <= score) {
			if ((fruitX5 == x && fruitY5 == y) || (fruitX5 == tailX[i] && fruitY5 == tailY[i]))
				goto loop5;
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
