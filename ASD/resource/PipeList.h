#pragma once
#include "PipeList.h"
#include "resource.h"
#include "Pic.h"
#include "Bird.h"
#include <afxwin.h>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )
#define  $d 12

class PipeList{
private:
	class Pipe{
	public:
		int pos_x,pos_y,speed;
		Pipe(int x=300,int y=rand()%200-270,int Speed=-4){
			pos_x=x;pos_y=y;speed=Speed;
		}
		void logic(){pos_x+=speed;}
		void stop() {speed=0;}
		void start(){speed=-4;}
	};
public:
	CList<Pipe, Pipe&> pipe;
	TCHAR mcicmd[300];
public:
	PipeList();
	void recover();
	void add();
	void logic(int &goals,Bird &bird,int &game_state);
	void draw(Pic &All,CDC* To,CDC* From);
};	
