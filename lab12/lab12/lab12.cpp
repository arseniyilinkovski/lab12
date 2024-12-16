#include "lab12.h"


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




class TGame {
	TScreen screen;
	TAnimatedCell cell[FLD_HEIGHT][FLD_WIDTH];
	bool MoveValInArray(TAnimatedCell *valArr[], int cnt);
	void Move(int dx, int dy);
	void GetNewRandNum(bool anim = false);
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
void TGame::GetNewRandNum(bool anim) {
	if (GetFreeCellCnt() == 0) return;
	int cnt = 1;
	while (cnt > 0) {
		int x = rand() % FLD_WIDTH;
		int y = rand() % FLD_HEIGHT;
		if (cell[y][x].value == 0) {
			if (anim) {
				cell[y][x].Anim(cell[y][x].pos);
			}
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
	if (KeyDownOnce('W') || KeyDownOnce(0x26)) Move(0, -1);
	if (KeyDownOnce('S') || KeyDownOnce(0x28)) Move(0, 1);
	if (KeyDownOnce('A') || KeyDownOnce(0x25)) Move(-1, 0);
	if (KeyDownOnce('D') || KeyDownOnce(0x27)) Move(1, 0);
}
void TGame::Move(int dx, int dy) {
	bool moved = false;
	if (dx != 0) {
		for (int j = 0; j < FLD_HEIGHT; j++) {
			TAnimatedCell* valArr[FLD_WIDTH];
			for (int i = 0; i < FLD_WIDTH; i++) {
				int x = (dx < 0) ? i : FLD_WIDTH - i -1;
				valArr[i] = &cell[j][x];
			}
			if (MoveValInArray(valArr, FLD_WIDTH)) moved = true;
		}
	}
	if (dy != 0) {
		for (int i = 0; i < FLD_HEIGHT; i++) {
			TAnimatedCell* valArr[FLD_HEIGHT];
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

			GetNewRandNum(true);
		}
	}
}
bool TGame::MoveValInArray(TAnimatedCell *valArr[], int cnt) {
	bool moved = false;
	int lastX = 0;
	for (int i = 1; i < cnt; i++) {
		if (valArr[i]->value != 0) {
			if (valArr[lastX]->value == 0) {
				valArr[i]->Anim(valArr[lastX]->pos);
				valArr[lastX]->Anim(valArr[lastX]->pos);
				moved = true;
				valArr[lastX]->value = valArr[i]->value;
				valArr[i]->value = 0;
			}
			else {
				if (valArr[lastX]->value == valArr[i]->value) {
					valArr[i]->Anim(valArr[lastX]->pos);
					valArr[lastX]->Anim(valArr[lastX]->pos);
					moved = true;
					valArr[lastX]->value += valArr[i]->value;
					valArr[i]->value = 0;
					lastX++;
				}
				else {
					if (valArr[lastX]->value != valArr[i]->value) {

						lastX++;
						if (lastX != i) {
							valArr[i]->Anim(valArr[lastX]->pos);
							valArr[lastX]->Anim(valArr[lastX]->pos);
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
		cell[0][i].PutStat(screen.scr);
	}
	for (int i = 0; i < FLD_WIDTH * FLD_HEIGHT; i++) {
		cell[0][i].PutAnim(screen.scr);
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
