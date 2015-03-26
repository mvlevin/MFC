#include <afxwin.h>
#include <afxcmn.h>

class CApp : public CWinApp {
public:
	BOOL InitInstance();
};

class CMainWin : public CFrameWnd {
public:
	CMainWin();
	afx_msg void OnPaint();

	afx_msg void RedLessBnClicked();
	afx_msg void RedMoreBnClicked();
	afx_msg void GreenLessBnClicked();
	afx_msg void GreenMoreBnClicked();
	afx_msg void BlueLessBnClicked();
	afx_msg void BlueMoreBnClicked();

	afx_msg void OnHScroll(UINT SBCode, UINT Pos, CScrollBar *SB);

	byte red = 0;
	byte green = 0;
	byte blue = 0;

private:
	CButton RedColorMore;
	CButton RedColorLess;
	CButton GreenColorMore;
	CButton GreenColorLess;
	CButton BlueColorMore;
	CButton BlueColorLess;

	SCROLLINFO ColorSBInfo;
	int SBPos = 0;

	CSliderCtrl RedColorSlider;
	CSliderCtrl GreenColorSlider;
	CSliderCtrl BlueColorSlider;

	DECLARE_MESSAGE_MAP();
};
