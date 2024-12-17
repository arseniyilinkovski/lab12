#include "TCell.h"


void TAnimatedCell::PutStat(TScreenMap scr) {
	if (IsAnim()) {
		TCell cell;
		if (IsStat()) {
			cell.Init(pos.x, pos.y, faceVal);
		}
		else {
			cell.Init(pos.x, pos.y, 0);
		}
		cell.Put(scr);
	}
	else {
		Put(scr);
	}
}
void TCell::Init(int x, int y, int val) { value = val; pos = { x, y }; }


bool TAnimatedCell::IsAnim() { return aCnt > 0 ? true : false; }


bool TAnimatedCell::IsStat() { return (dx == 0 && dy == 0) ? true : false; }
void TAnimatedCell::Work() { aCnt--; ax += dx; ay += dy; };
void TAnimatedCell::PutAnim(TScreenMap scr) {
	if (IsAnim()) {
		Work();
		if (IsStat()) return;
		TCell cell;
		cell.Init(lround(ax), lround(ay), faceVal);
		cell.Put(scr);
	}
}
void TAnimatedCell::Anim(POINT to) {
	if (IsAnim()) return;
	faceVal = value;
	aCnt = 20;
	ax = pos.x;
	ay = pos.y;
	dx = (to.x - ax) / (float)aCnt;
	dy = (to.y - ay) / (float)aCnt;
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