#include <afxwin.h>// MFC Основные и стандартные компоненты
#include "afxext.h"
#include <string.h>
#include "resource.h" //Файл ресурсов
#include <ctime>
#include <time.h>
#include <math.h>
#include <vector>

//Задаем класс окна и определяем его поведение
class CMainWnd : public CFrameWnd
{
public:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	void Menu_QUIT();
	CMenu m_wndMenu; // Добавляем меню
	CMainWnd();
	~CMainWnd();
private:
	DECLARE_MESSAGE_MAP(); // таблица откликов
};
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)	// таблица откликов на сообщения
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_QUIT, Menu_QUIT)
END_MESSAGE_MAP()
int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_wndMenu.LoadMenu(IDR_MENU1);	// Загрузить меню из файла ресурса
	SetMenu(&m_wndMenu);	// Установить меню
	return 0;
}
CMainWnd::CMainWnd()
{
	Create(NULL, TEXT("Flappy Bird"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);// Создать окно программы
}
afx_msg void CMainWnd::OnPaint() {
	CPaintDC paintDC(this);
	CBitmap pic;
	pic.LoadBitmapW(IDB_BITMAP2);
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(&paintDC);
	dcTemp.SelectObject(pic);
	GetDC()->BitBlt(0, 0, 100, 100, &dcTemp, 0, 0, SRCCOPY);

}
CMainWnd::~CMainWnd(){
}
void CMainWnd::Menu_QUIT(){
	MessageBox(_T("Всего хорошего!"), _T("Благодарим за игру!"), MB_ICONINFORMATION | MB_OK);
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);
}
//Определяем класс приложения
class CMyApp : public CWinApp
{
public:
	CMyApp();			//конструктор по умолчанию
	virtual BOOL InitInstance();//стандартная инициализация
};

CMyApp::CMyApp() // конструктор главного класса приложения
{}
BOOL CMyApp::InitInstance() // стандартная инициализация
{
	m_pMainWnd = new CMainWnd();	// создать класс окна
	ASSERT(m_pMainWnd);	// проверить его правильность
	m_pMainWnd->ShowWindow(SW_SHOW);// Показать окно
	m_pMainWnd->UpdateWindow();	// Обновить окно
	return TRUE;		// Вернуть что все нормально
};
CMyApp theApp;	// запуск приложения
