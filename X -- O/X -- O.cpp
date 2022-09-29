#include <iostream>
#include <Windows.h>
#include <conio.h>

char table[3][3], playerchar;
bool gameOver;
using namespace std;
int x, y;
enum direction {STOP = 0 , TOP , RIGHT , LEFT , DOWN, LOCK};
direction dir;


/*void lookleft()
{
	int i = x, j = y-1;
	for (; i >= 0; i--) {
		for (; j >= 0; j--) {
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
		}
		j = 2;
	}
	for (i = 2; i >= 0; i--) {
		for (j = 2; j >= 0; j--) {
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
		}
	}
}
void lookright() {
	int i = x, j = y+1;
	for (; i < 3; i++) {
		for( ;j < 3; j++)
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
		j = 0;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
	}
}
void lookdown() {
	int i = x + 1, j = y;
	for (; j < 3; j++) {
		for (; i < 3; i++) {
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
	    }
		i = 0;
	}
	for (j = 0; i < 3; i++) {
		for (i = 0; j < 3; j++)
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
	}


}
void lookup() {
	int i = x - 1, j = y;
	for (; j >= 0; j--) {
		for (; i >= 0; i--) {
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
		}
		i = 2;
	}
	for (j = 2; j >= 0; j--) {
		for (i = 2; i >= 0; i--) {
			if (table[i][j] == '*') {
				x = i;
				y = j;
				return;
			}
		}
	}
}*/

void IncrementIndex(int& index1, int& index2, int incr)
{
	if (index1 == 2 && incr == 1)
	{
		index2 = (index2 + 1) % 3;
		index1 = 0;
	}
	else if (index1 == 0 && incr == -1)
	{
		index1 = 2;
		index2--;
		if (index2 < 0) index2 = 2;
	}
	else index1 += incr;
}

void GetEmptySpot(bool horizontal, int incr)
{
	if (horizontal)
		IncrementIndex(x, y, incr);
	else
		IncrementIndex(y, x, incr);

	if (table[x][y] == '*') return;
	else GetEmptySpot(horizontal, incr);
}

bool checkGameStatus_full() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (table[i][j] == '*')
				return false;

	return true;
}
bool checkGameStaus_diag() {
	if ((table[1][1] == table[0][0] && table[1][1] == table[2][2]) && (table[0][0] == 'X' || table[0][0] == 'O'))
		return true;
	return false;
}
bool checkGameStatus_subdiag() {
	if ((table[0][2] == table[1][1] && table[1][1] == table[2][0]) && (table[1][1] == 'X' || table[1][1] == 'O'))
		return true;
	return false;
}
bool checkGameStatus_row() {
	for(int i = 0 ; i < 3 ; i++)
		if ((table[0][i] == table[1][i] && table[1][i] == table[2][i]) && (table[1][i] == 'X' || table[1][i] == 'O'))
			return true;
	return false;
}
bool checkGameStatus_column() {
	for (int i = 0; i < 3; i++)
		if ((table[i][0] == table[i][1] && table[i][1] == table[i][2]) && (table[i][1] == 'X' || table[i][1] == 'O'))
			return true;
	return false;
}
void checkGameStatus() {
	if (checkGameStaus_diag() || checkGameStatus_subdiag() || checkGameStatus_row() || checkGameStatus_column()) {
		gameOver = true;
		cout << "player " << playerchar << " has won" << endl;
	}
	else
		if (checkGameStatus_full()) {
		 gameOver = true;
		 cout << "DRAW" << endl;
	  }

}


void  lock_char() {
	if (playerchar == 'O')
		playerchar = 'X';
	else
		playerchar = 'O';

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (table[i][j] == '*') {
				table[i][j] = playerchar;
				x = i;
				y = j;
				dir = STOP;
				return;
			}

}

void mouvement() {
	switch (dir)
	{
	case LEFT:
		//lookleft();
		GetEmptySpot(false, -1);
		break;
	case RIGHT:
		//lookright();
		GetEmptySpot(false, 1);
		break;
	case TOP:
		//lookup();
		GetEmptySpot(true, -1);
		break;
	case DOWN:
		//lookdown();
		GetEmptySpot(true, 1);
		break;
	default:
		break;
	}
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void setup() {
	
	system("cls");
	cout << "press x to choose a position // use z q s d to move" << endl << endl;
	srand(time(NULL));
	x = 1, y = 1;
	gameOver = false;
	playerchar = 'X';
	for (int i = 0; i < 3; i++)
      for(int j = 0 ; j < 3 ; j++)
		table[i][j] = '*';
	table[x][y] = 'X';
	dir = STOP;
    hidecursor();
}

void draw() 
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,2 });
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << table[i][j] << "    ";
		cout << endl << endl;
	}
}

void input() {
	
	if (_kbhit())
	{
			switch (_getch())
			{
			case 'q':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'z':
				dir = TOP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				dir = LOCK;
				break;
			}
		
	}
}

void logic() {
	int prevX = x;
	int prevY = y;
	
	if (dir != STOP) {
		table[prevX][prevY] = '*';
		mouvement();
		table[x][y] = playerchar;
	}
	 if (dir == LOCK) {
	  table[prevX][prevY] = playerchar;
	  checkGameStatus();
	  lock_char();
	 }
	dir = STOP;
}

int main()
{   
	
	do
	{
		setup();
		while (!gameOver) {
			draw();
			input();
			logic();
		}
		cout << "press p to leave , anything else to replay " << endl;
	}while (_getch() != 'p');
}

