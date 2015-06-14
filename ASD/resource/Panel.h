#pragma once
#include "Pic.h"
#include "resource.h"
#include <afxwin.h>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )

#define panel_move 0
#define goals_add  1
#define finish     2

class Panel
{
public:
	int state;
	int goals,best_goals;
	int y;
	bool new_goals;
	bool ring;
public:
	Panel();
	void recover();
	void draw(Pic &All,CDC* To,CDC* From);
	void logic(int &_goals,int &_best_goals);
};
