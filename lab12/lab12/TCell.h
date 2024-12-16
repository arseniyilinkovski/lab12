#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <cmath>

using namespace std;
const int SCR_WIDTH = 80;
const int SCR_HEIGHT = 25;
const int CELL_WIDTH = 8;
const int CELL_HEIGHT = 5;
const int FLD_WIDTH = 4;
const int FLD_HEIGHT = 4;


typedef char TScreenMap[SCR_HEIGHT][SCR_WIDTH];

class TCell {
public:
	int value;
	POINT pos;
	TCell() { Init(0, 0, 0); }
	void Init(int x, int y, int val) { value = val; pos = { x, y }; }
	void Put(TScreenMap scr);
};

class TAnimatedCell : public TCell {
	float ax, ay;
	float dx, dy;
	int aCnt;
	int faceVal;
public:
	TAnimatedCell() : TCell() { aCnt = 0; }
	void Anim(POINT to);
	bool IsAnim() { return aCnt > 0 ? true : false; }
	bool IsStat() { return (dx == 0 && dy == 0) ? true : false; }
	void Work() { aCnt--; ax += dx; ay += dy; };
	void PutAnim(TScreenMap scr);
	void PutStat(TScreenMap scr);
};

