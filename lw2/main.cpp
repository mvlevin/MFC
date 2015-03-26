#include <afxwin.h>
#include <afxcmn.h>
#include <string.h>
#include "resource.h"

CApp App;

BOOL CApp::InitInstance() {
	m_pMainWnd = new CMainWin;
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CMainWin::CMainWin() {
	this->Create(0, TEXT("LW 2"));
	RedColorLess.Create(TEXT("-"), WS_CHILD | CBRS_HIDE_INPLACE | BS_PUSHBUTTON, CRect(700, 200, 750, 260), this, 101);
	RedColorMore.Create(TEXT("+"), WS_CHILD | CBRS_HIDE_INPLACE | BS_PUSHBUTTON, CRect(750, 200, 800, 260), this, 102);
	GreenColorLess.Create(TEXT("-"), WS_CHILD | CBRS_HIDE_INPLACE | BS_PUSHBUTTON, CRect(700, 270, 750, 330), this, 103);
	GreenColorMore.Create(TEXT("+"), WS_CHILD | CBRS_HIDE_INPLACE | BS_PUSHBUTTON, CRect(750, 270, 800, 330), this, 104);
	BlueColorLess.Create(TEXT("-"), WS_CHILD | CBRS_HIDE_INPLACE | BS_PUSHBUTTON, CRect(700, 340, 750, 400), this, 105);
	BlueColorMore.Create(TEXT("+"), WS_CHILD | CBRS_HIDE_INPLACE | BS_PUSHBUTTON, CRect(750, 340, 800, 400), this, 106);

	

	// initialization ColorSBInfo
	{
		ColorSBInfo.cbSize = sizeof(SCROLLINFO);
		ColorSBInfo.fMask = SIF_ALL;
		ColorSBInfo.nMin = 0;
		ColorSBInfo.nMax = 225;
		ColorSBInfo.nPage = 0;
	}
	

	RedColorSlider.Create(WS_CHILD | WS_VISIBLE | TBS_HORZ, CRect(800, 200, 1200, 260), this, 107);
	GreenColorSlider.Create(WS_CHILD | WS_VISIBLE | TBS_HORZ, CRect(800, 270, 1200, 330), this, 108);
	BlueColorSlider.Create(WS_CHILD | WS_VISIBLE | TBS_HORZ, CRect(800, 340, 1200, 400), this, 109);


}

afx_msg void CMainWin::OnPaint() {
	CPaintDC paintDC(this);
	paintDC.TextOut(500, 50, TEXT("Лабораторная работа №2"));
	paintDC.TextOut(630, 220, "  RED");
	paintDC.TextOut(630, 290, "GREEN");
	paintDC.TextOut(630, 360, " BLUE");
	CRect elipse(300, 200, 500, 400);
	CBrush Paint;
	Paint.CreateSolidBrush(RGB(red, green, blue));
	paintDC.SelectObject(Paint);
	paintDC.Ellipse(elipse);
}

afx_msg void CMainWin::RedLessBnClicked() {
	red -= 10;
	RedColorSlider.SetScrollPos(107, red);
	this->InvalidateRect(0);
}
afx_msg void CMainWin::RedMoreBnClicked() {
	red += 10;
	RedColorSlider.SetScrollPos(107, red);
	this->InvalidateRect(0);
}
afx_msg void CMainWin::GreenLessBnClicked() {
	green -= 10;
	GreenColorSlider.SetScrollPos(108, green);
	this->InvalidateRect(0);
}
afx_msg void CMainWin::GreenMoreBnClicked() {
	green += 10;
	GreenColorSlider.SetScrollPos(108, green);
	this->InvalidateRect(0);
}
afx_msg void CMainWin::BlueLessBnClicked() {
	blue -= 10;
	BlueColorSlider.SetScrollPos(109, blue);
	this->InvalidateRect(0);
}
afx_msg void CMainWin::BlueMoreBnClicked() {
	blue += 10;
	BlueColorSlider.SetScrollPos(109, blue);
	this->InvalidateRect(0);
}

afx_msg void CMainWin::OnHScroll(UINT SBCode, UINT Pos, CScrollBar *SB) {
	if (SBCode == SB_THUMBPOSITION) {
		SBPos = Pos;
	}
	if (SBCode == SB_THUMBTRACK) {
		SBPos = Pos;
	}
	if (SBCode == SB_LINELEFT) {
		--SBPos;
	}
	if (SBCode == SB_LINERIGHT) {
		++SBPos;
	}
	if (SBCode == SB_PAGELEFT) {
		SBPos -= 10;
	}
	if (SBCode == SB_PAGERIGHT) {
		SBPos += 10;
	}

	

	if (*SB == RedColorSlider) {
		red = SBPos;
		this->InvalidateRect(0);
	}
	if (*SB == GreenColorSlider) {
		green = SBPos;
		this->InvalidateRect(0);
	}
	if (*SB == BlueColorSlider) {
		blue = SBPos;
		this->InvalidateRect(0);
	}

	SCROLLINFO NewSBInfo;
	NewSBInfo.cbSize = sizeof(NewSBInfo);
	NewSBInfo.fMask = SIF_POS;
	NewSBInfo.nPos = SBPos;
	SB->SetScrollInfo(&NewSBInfo);
}



BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_WM_PAINT()

	ON_BN_CLICKED(101, RedLessBnClicked)
	ON_BN_CLICKED(102, RedMoreBnClicked)
	ON_BN_CLICKED(103, GreenLessBnClicked)
	ON_BN_CLICKED(104, GreenMoreBnClicked)
	ON_BN_CLICKED(105, BlueLessBnClicked)
	ON_BN_CLICKED(106, BlueMoreBnClicked)

	ON_WM_HSCROLL()

END_MESSAGE_MAP()
