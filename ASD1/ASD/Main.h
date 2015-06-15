#pragma once
#include "resource.h"
#include "Pic.h"
#include "PipeList.h"
#include "Land.h"
#include "Bird.h"
#include "Panel.h"
#include "Button.h"
#include <afxwin.h>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )



class CMyApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};


class CMainWindow:public CFrameWnd
{
public:
	int bg_state,game_state,last_state;

	int goals,best_goals;//·ÖÊý

	CRect m_client;
	CBitmap m_bgBitmap,m_tempBitmap;
	CDC m_cacheDC;
	CDC m_bgcDC,m_tempcDC;

	Pic pic;
	PipeList pipe;
	Land land;
	Bird bird;
	Panel panel;
    Button button;
public:
	CMainWindow ();
	
	void draw();
	void restart();
	void screenShot(CRect rect,int left,int top,char *name);
protected:
	afx_msg int  OnCreate (LPCREATESTRUCT lpcs);      
    afx_msg void OnTimer (UINT nTimerID);              
    afx_msg void OnClose ();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP();
	
};