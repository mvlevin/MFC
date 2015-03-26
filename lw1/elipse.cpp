#include <afxwin.h>
#include <string.h>
#include "resource.h"



BOOL CApp::InitInstance()
{

	// Создание главного окна приложения и его
	// отображение.

	// Член CApp::m_pMainWnd - это указатель на объект
	// главного окна.

	m_pMainWnd = new CMainWin;
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	// Сигнализируем MFC об успешной инициализации
	// приложения. 

	return TRUE;
}

CMainWin::CMainWin()
{
	// Создание окна с заголовком. Используется
	// встроенный в MFC

	// класс окна, поэтому первый параметр 0.
	this->Create(0, TEXT("Лабораторная работа №1"));
}

afx_msg void CMainWin :: OnPaint() {
	CPaintDC paintDC(this);
	CRect elipse(600, 300, 900, 600);
	paintDC.Ellipse(elipse);
	if (((X - 750) * (X - 750) + (Y - 450) * (Y - 450)) < 150 * 150) {
		CBrush Paint1;
		Paint1.CreateSolidBrush(RGB(0, 0, 0));
		paintDC.SelectObject(Paint1);
		paintDC.Ellipse(elipse);
	}
	else {
		CBrush Paint2;
		Paint2.CreateSolidBrush(RGB(255, 255, 255));
		paintDC.SelectObject(Paint2);
		paintDC.Ellipse(elipse);
	}
}
afx_msg void CMainWin::OnLButtonUp(UINT flags, CPoint Loc) {
	X = Loc.x;
	Y = Loc.y;
    this->Invalidate(0);
}

// Реализация карты сообщений
BEGIN_MESSAGE_MAP(CMainWin /*класс окна*/, CFrameWnd
	/*класс-предок*/)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

CApp App;
