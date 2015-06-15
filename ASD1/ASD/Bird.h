#pragma once
#include "Pic.h"
#include "resource.h"
#include <afxwin.h>
#include <cmath>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )

#define bird_v0 -14
#define bird_a0 2
#define $d 12
#define PI 3.1415926

#define state_up		 0
#define state_turn		 2
#define state_down		 3
#define state_delay      4

class Bird
{
public:
	int bird_state,fly_state,dis_state;
	int y,v,a;
	double Time;
	int state;
	int delay;
	CBitmap bird[3][3];
public:
	Bird();
	void recover();
	void stop();
	void jump();
	void logic(int ID,int &game_state);
	void paint(CDC* To,CDC* From);
};