#include <afxwin.h>
#include "afxext.h"
#include <string.h>
#include "resource.h"
#include <ctime>
#include <time.h>
#include <math.h>
#include <vector>
#include <random>

COLORREF RED = RGB(255, 0, 0);
COLORREF BLACK = RGB(0, 0, 0);
CRect MAIN_WINDOW(0, 0, 1024, 768);
int FALLING_SPEED = 15;
int PIPEWIDTH = 70;
int PIPEHEIGHT = 768;
int OPENINGSPACEHEIGHT = 200;
int BIRDSPEED = 20;
int PIPESPEED = 9;

class PIPE {
public:
	CRect TopPart;
	CRect BottomPart;
	COLORREF Color;
	bool move;
	int direction;
	PIPE(CPoint topLeft, COLORREF color) {
		TopPart = CRect(topLeft.x, 0, topLeft.x + PIPEWIDTH, topLeft.y);
		BottomPart = CRect(topLeft.x, topLeft.y + OPENINGSPACEHEIGHT, topLeft.x + PIPEWIDTH, MAIN_WINDOW.bottom);
		Color = color;
		move = false;
		direction = 1;
	}
	PIPE(const PIPE& other) {
		TopPart = other.TopPart;
		BottomPart = other.BottomPart;
		Color = other.Color;
		move = other.move;
		direction = other.direction;
	}
	void operator=(const PIPE& other) {
		TopPart = other.TopPart;
		BottomPart = other.BottomPart;
		Color = other.Color;
		move = other.move;
		direction = other.direction;
	}
};

class BIRD {
public:
	int Height;
	int Width;
	CRect Location;
	int JumpHeight;
	COLORREF Color;
	bool tackle;
	BIRD(int height, int width, CPoint topLeft, int jumpHeight, COLORREF color) {
		Height = height;
		Width = width;
		Location = CRect(topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height);
		JumpHeight = jumpHeight;
		Color = color;
		tackle = false;
	}
	BIRD(const BIRD& other) {
		Height = other.Height;
		Width = other.Width;
		Location = other.Location;
		JumpHeight = other.JumpHeight;
		Color = other.Color;
		tackle = other.tackle;
	}
	void operator=(const BIRD& other) {
		Height = other.Height;
		Width = other.Width;
		Location = other.Location;
		JumpHeight = other.JumpHeight;
		Color = other.Color;
		tackle = other.tackle;
	}
	void ProcessPosition(std::vector<PIPE>& pipes, int& counter) {
		if (Location.top < MAIN_WINDOW.top) {
			Location.top = MAIN_WINDOW.top;
			Location.bottom = Location.top + Height;
		}
		if (Location.bottom >= MAIN_WINDOW.bottom) {
			tackle = true;
		}
		for (int i = 0; i < pipes.size(); i++) {
			if (((Location.top <= pipes[i].TopPart.bottom) || (Location.bottom >= pipes[i].BottomPart.top))
				&& (Location.right > pipes[i].TopPart.left) && (Location.left < pipes[i].TopPart.right)) {
				tackle = true;
			}
			if (((Location.top > pipes[i].TopPart.bottom) && (Location.bottom < pipes[i].BottomPart.top)
				&& (pipes[i].TopPart.right < Location.left) && (pipes[i].TopPart.right > Location.left - BIRDSPEED))) {
				counter++;
			}
		}
	}
};

int Counter = 0;
BIRD Bird(0, 0, CPoint(0, 0), 0, RGB(255, 0, 0));
std::vector<PIPE> Pipes;


class CMainWnd : public CFrameWnd
{
public:

	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	void Menu_QUIT();
	void Menu_NEWGAME();
	afx_msg void OnKeyUp(UINT nButtonCode, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nButtonCode, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nTimerID);
	CMenu m_wndMenu;
	CMainWnd();
	~CMainWnd();

	bool Start = false;
	bool End = false;
	bool Quit = false;
private:
	DECLARE_MESSAGE_MAP();
};
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_QUIT, Menu_QUIT)
	ON_COMMAND(ID_NEWGAME, Menu_NEWGAME)
	ON_WM_TIMER()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()
int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_wndMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_wndMenu);
	return 0;
}
CMainWnd::CMainWnd()
{
	Create(NULL, TEXT("Flappy Bird"), WS_OVERLAPPEDWINDOW, MAIN_WINDOW, NULL, NULL);
}
afx_msg void CMainWnd::OnPaint() {
	CPaintDC DeviceContext(this);
	CBitmap MCity;
	MCity.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP2));
	CDC DCMemory1;
	DCMemory1.CreateCompatibleDC(&DeviceContext);
	DCMemory1.SelectObject(MCity);
	GetDC()->BitBlt(0, 0, MAIN_WINDOW.right, MAIN_WINDOW.bottom, &DCMemory1,
		0, 0, SRCCOPY);
	//CBitmap Picture;
	//CDC DCMemory;
	//DCMemory.CreateCompatibleDC(&DeviceContext);
	if (End) {
		CBitmap MOver;
		MOver.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP4));
		CDC DCMemory2;
		DCMemory2.CreateCompatibleDC(&DeviceContext);
		DCMemory2.SelectObject(MOver);
		GetDC()->BitBlt(-0.45*MAIN_WINDOW.right, -0.2*MAIN_WINDOW.bottom, 1.45*MAIN_WINDOW.right, 1.2*MAIN_WINDOW.bottom, &DCMemory2,
			0, 0, SRCCOPY);
		CString Score;
		Score.Format(L"%d", Counter);
		DeviceContext.TextOutW(500, 250, Score);
	}
	if (!Start) {
		CBitmap MArrow;
		MArrow.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP1));
		CDC DCMemory;
		DCMemory.CreateCompatibleDC(&DeviceContext);
		DCMemory.SelectObject(MArrow);
		GetDC()->TransparentBlt(-10, 20, 100, 100, &DCMemory,
			0, 0, 100, 100, RGB(255, 255, 255));
	}
	if (Start) {
		//CRect Rectt(100, 100, 200, 200);
		//CBrush ColorBrush;
		//ColorBrush.CreateSolidBrush(Bird.Color);
		//DeviceContext.SelectObject(ColorBrush);
		//DeviceContext.Ellipse(Bird.Location);
		CBitmap MiaBird;
		MiaBird.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP3));
		CDC DCMemory;
		DCMemory.CreateCompatibleDC(&DeviceContext);
		DCMemory.SelectObject(MiaBird);
		GetDC()->TransparentBlt(Bird.Location.left, Bird.Location.top, Bird.Width, Bird.Height, &DCMemory,
			0, 0, Bird.Width, Bird.Height, RGB(0, 0, 0));
		for (int i = 0; i < Pipes.size(); i++) {
			CBrush ColorBrush2;
			ColorBrush2.CreateSolidBrush(Pipes[i].Color);
			DeviceContext.SelectObject(ColorBrush2);
			DeviceContext.Rectangle(Pipes[i].TopPart);
			DeviceContext.Rectangle(Pipes[i].BottomPart);
		}
		CString Score;
		Score.Format(L"%d", Counter);
		DeviceContext.TextOutW(80, 60, Score);
	}
}
CMainWnd::~CMainWnd(){
}
void CMainWnd::Menu_QUIT() {
	MessageBox(_T("Удачного дня!"), _T("Благодарим за игру!"), MB_ICONINFORMATION | MB_OK);
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);
}
void CMainWnd::Menu_NEWGAME() {
	Start = true;
	End = false;
	Quit = false;
	Counter = 0;
	Bird = BIRD(50, 50, CPoint(300, 400), 50, RED);
	Pipes.clear();
	this->SetTimer(1, 100, NULL);
	this->SetTimer(2, 2000, NULL);
	this->InvalidateRect(0);
}
afx_msg void CMainWnd::OnKeyUp(UINT nButtonCode, UINT nRepCnt, UINT nFlags) {
	if (nButtonCode == VK_SPACE) {
		Bird.Location.bottom -= Bird.JumpHeight;
		Bird.Location.top = Bird.Location.bottom - Bird.Height;
	}
}
afx_msg void CMainWnd::OnKeyDown(UINT nButtonCode, UINT nRepCnt, UINT nFlags) {
	if (nButtonCode == VK_DOWN) {
		Bird.Location.bottom += 15;
		Bird.Location.top = Bird.Location.bottom - Bird.Height;
	}
}
afx_msg void CMainWnd::OnTimer(UINT nTimerID) {
	if (Start) {
		if (nTimerID == 1) {
			Bird.Location.bottom += FALLING_SPEED;
			Bird.Location.top = Bird.Location.bottom - Bird.Height;
			for (int i = 0; i < Pipes.size(); i++) {
				Pipes[i].TopPart.left -= BIRDSPEED;
				Pipes[i].TopPart.right -= BIRDSPEED;
				Pipes[i].BottomPart.left -= BIRDSPEED;
				Pipes[i].BottomPart.right -= BIRDSPEED;
				if (Pipes[i].move) {
					Pipes[i].TopPart.bottom -= PIPESPEED * Pipes[i].direction;
					Pipes[i].BottomPart.top -= PIPESPEED * Pipes[i].direction;
					if ((Pipes[i].TopPart.bottom <= MAIN_WINDOW.top) || (Pipes[i].BottomPart.top >= MAIN_WINDOW.bottom)) {
						Pipes[i].direction *= -1;
					}
				}
				if (Pipes[i].TopPart.right < MAIN_WINDOW.left) {
					Pipes.erase(Pipes.begin() + i);
				}
			}
			Bird.ProcessPosition(Pipes, Counter);
			if (Bird.tackle) {
				Start = false;
				End = true;
				Quit = false;
			}
			this->InvalidateRect(0);
		}
		else if (nTimerID == 2) {
			int spaceTop = std::rand() % (MAIN_WINDOW.bottom - OPENINGSPACEHEIGHT);
			PIPE Pipe(CPoint(MAIN_WINDOW.right, spaceTop), BLACK);
			if (std::rand() % 3 == 0) {
				Pipe.move = true;
				if (std::rand() % 2 == 0) {
					Pipe.direction = -1;
				}
			}
			Pipes.push_back(Pipe);
		}
	}
}

class CMyApp : public CWinApp
{
public:
	CMyApp();
	virtual BOOL InitInstance();
};

CMyApp::CMyApp()
{}
BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWnd();
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
};
CMyApp theApp;