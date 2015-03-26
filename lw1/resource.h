#include <afxwin.h>

class CMainWin : public CFrameWnd {
public:
	CMainWin();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT flags, CPoint Loc);
	int X;
	int Y;

	DECLARE_MESSAGE_MAP()
};

class CApp : public CWinApp {
	BOOL InitInstance();
};
