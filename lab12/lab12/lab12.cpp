#include "IlinkovskiArseniy_Caesar's_cipher.h"
#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <cmath>


const int SCR_WIDTH = 80;
const int SCR_HEIGHT = 25;
const int CELL_WIDTH = 8;
const int CELL_HEIGHT = 5;
const int FLD_WIDTH = 4;
const int FLD_HEIGHT = 4;

typedef char TScreenMap[SCR_HEIGHT][SCR_WIDTH];
void SetCurPos(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


class TScreen {
	void SetEnd() {
		scr[SCR_HEIGHT - 1][SCR_WIDTH - 1] = '\0';
	}
public:
	TScreenMap scr;
	TScreen() {
		clear();
	}
	void clear() {
		memset(scr, ' ', sizeof(scr));
	}
	void show() {
		SetCurPos(0, 0);
		SetEnd();
		cout << scr[0];
	}
};


class TCell {
public:
	int value; 
	POINT pos;
	TCell() { Init(0, 0, 0); }
	void Init(int x, int y, int val) { value = val; pos = { x, y }; }
	void Put(TScreenMap scr);
};


class TGame {
	TScreen screen;
	TCell cell[FLD_HEIGHT][FLD_WIDTH];
	bool MoveValInArray(TCell* valArr[], int cnt);
	void Move(int dx, int dy);
	void GetNewRandNum();
	int GetFreeCellCnt();
	bool CheckEndGame();
public:
	TGame() { Init(); }
	void Init();
	void Work();
	void Show();
};

bool TGame::CheckEndGame() {
	if (GetFreeCellCnt() > 0) {
		return false;
	}
	for (int i = 0; i < FLD_WIDTH; i++) {
		for (int j = 0; j < FLD_HEIGHT; j++) {
			if ((j < FLD_HEIGHT - 1 && cell[j][i].value == cell[j + 1][i].value) ||
				(i < FLD_WIDTH - 1 && cell[j][i].value == cell[j][i + 1].value))
				return false;
		}
	}return true;
}
void TGame::GetNewRandNum() {
	if (GetFreeCellCnt() == 0) return;
	int cnt = 1;
	while (cnt > 0) {
		int x = rand() % FLD_WIDTH;
		int y = rand() % FLD_HEIGHT;
		if (cell[y][x].value == 0) {
			cell[y][x].value = (rand() % 10 == 0) ? 4 : 2, cnt--;
		}
	}
}
int  TGame::GetFreeCellCnt() {
	int cnt = 0;
	for (int i = 0; i < FLD_WIDTH * FLD_HEIGHT; i++) {
		if (cell[0][i].value == 0) {
			cnt++;
		}
	}
	return cnt;
}
bool KeyDownOnce(char c) {
	if (GetKeyState(c) < 0) {
		while (GetKeyState(c) < 0);
		return true;
	}
	return false;
}

void TGame::Work() {
	if (KeyDownOnce('W')) Move(0, -1);
	if (KeyDownOnce('S')) Move(0, 1);
	if (KeyDownOnce('A')) Move(-1, 0);
	if (KeyDownOnce('D')) Move(1, 0);
}
void TGame::Move(int dx, int dy) {
	bool moved = false;
	if (dx != 0) {
		for (int j = 0; j < FLD_HEIGHT; j++) {
			TCell* valArr[FLD_WIDTH];
			for (int i = 0; i < FLD_WIDTH; i++) {
				int x = (dx < 0) ? i : FLD_WIDTH - i -1;
				valArr[i] = &cell[j][x];
			}
			if (MoveValInArray(valArr, FLD_WIDTH)) moved = true;
		}
	}
	if (dy != 0) {
		for (int i = 0; i < FLD_HEIGHT; i++) {
			TCell* valArr[FLD_HEIGHT];
			for (int j = 0; j < FLD_HEIGHT; j++) {
				int y = (dy < 0) ? j : FLD_WIDTH - j - 1;
				valArr[j] = &cell[y][i];
			}
			if (MoveValInArray(valArr, FLD_HEIGHT)) moved = true;
		}
	}
	if (CheckEndGame()) {
		Init();
	}
	else {
		if (moved) {

			GetNewRandNum();
		}
	}
}
bool TGame::MoveValInArray(TCell* valArr[], int cnt) {
	bool moved = false;
	int lastX = 0;
	for (int i = 1; i < cnt; i++) {
		if (valArr[i]->value != 0) {
			if (valArr[lastX]->value == 0) {
				moved = true;
				valArr[lastX]->value = valArr[i]->value;
				valArr[i]->value = 0;
			}
			else {
				if (valArr[lastX]->value == valArr[i]->value) {
					moved = true;
					valArr[lastX]->value += valArr[i]->value;
					valArr[i]->value = 0;
					lastX++;
				}
				else {
					if (valArr[lastX]->value != valArr[i]->value) {
						lastX++;
						if (lastX != i) {
							moved = true;
							valArr[lastX]->value = valArr[i]->value;
							valArr[i]->value = 0;
						}
					}
				}

			}
		}
	}
	return moved;
}

void TGame::Show(){
	for (int i = 0; i < FLD_WIDTH * FLD_HEIGHT; i++) {
		cell[0][i].Put(screen.scr);
	}
	screen.show();
}

void TGame::Init() {
	//инициализация игры
	const int DX = 2;//стартовая позиция Ох
	const int DY = 2;//стартовая позициия Оу
	srand(GetTickCount());
	for (int i = 0; i < FLD_WIDTH; i++) {
		for (int j = 0; j < FLD_HEIGHT; j++) {
			cell[j][i].Init(DX + i * (CELL_WIDTH - 1), DY + j * (CELL_HEIGHT - 1), 0); // иниицализируем клетки карты
		}
	}
	GetNewRandNum();
	GetNewRandNum();
}
void TCell::Put(TScreenMap scr) {
	for (int i = 0; i < CELL_WIDTH; i++) {
		for (int j = 0; j < CELL_HEIGHT; j++) {
			scr[pos.y + j][pos.x + i] = (i == 0 || i == CELL_WIDTH - 1 ||
				j == 0 || j == CELL_HEIGHT - 1) ? '+' : ' ';
		}
	}
	if (value == 0) return;
	char buf[10];
	sprintf_s(buf, "%d", value);
	int len = strlen(buf);
	int posX = (CELL_WIDTH - len) / 2;
	int posY = (CELL_HEIGHT - 1) / 2;
	for (int i = 0; i < len; i++) {
		scr[pos.y + posY][pos.x + i + posX] = buf[i];
	}
}
int main()
{
	char command[1000];
	sprintf_s(command, sizeof(command), "mode con: cols=%d lines=%d", SCR_WIDTH, SCR_HEIGHT);
	system(command);
	TGame game;
	while (1) {
		game.Work();
		game.Show();
		if (GetKeyState(VK_ESCAPE) < 0) break;
		Sleep(10);
	}
	return 0;
}

