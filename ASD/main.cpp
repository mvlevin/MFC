#include "Main.h"
#define bird_time 0
#define land_time 1

#define before_game 0
#define during_game 1
#define dying_game  2
#define end_game    3
#define start_game  4
#define bird_delay  4

CMyApp myapp;


BOOL CMyApp::InitInstance(){
	m_pMainWnd=new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE ()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMainWindow::CMainWindow(){
	CString strWndClass = AfxRegisterWndClass (
        CS_HREDRAW | CS_VREDRAW,
        myapp.LoadStandardCursor (IDC_ARROW),
        (HBRUSH) (COLOR_3DFACE + 1),
        myapp.LoadIcon (IDIGNORE)
    );

    Create (strWndClass,_T("@-@"),WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX);
    CRect rect (0,0,286,512);
    CalcWindowRect (&rect);

    SetWindowPos (NULL, 0, 0, rect.Width (), rect.Height (),
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);

	HICON a = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(a,true);

	CDC *cDC=this->GetDC();
	GetClientRect(&m_client);   
	m_cacheDC.CreateCompatibleDC(cDC);
	m_bgcDC.CreateCompatibleDC(cDC);
	m_tempcDC.CreateCompatibleDC(cDC);
	m_tempBitmap.CreateCompatibleBitmap(cDC,m_client.Width(),m_client.Height());
	m_bgBitmap.LoadBitmap(IDB_BITMAP1);
	m_cacheDC.SelectObject(&m_tempBitmap);
	ReleaseDC(cDC); 

	srand((unsigned)time(NULL));
	bg_state=rand()%2;game_state=0;last_state=0;
	goals=best_goals=0;
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpcs){
	if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

    if (!SetTimer (bird_time,100, NULL)) {
        MessageBox (_T ("Error: SetTimer failed"));
        return -1;
    }
    if (!SetTimer (land_time,60, NULL)) {
        MessageBox (_T ("Error: SetTimer failed"));
        return -1;
    }
    return 0;
}
void CMainWindow::OnTimer(UINT nTimerID){
	switch(nTimerID){
	case bird_time:
		if(game_state==before_game)bird.logic(before_game,game_state);
		break;
	case land_time:
		if(game_state==before_game){
			land.logic();
		}else if(game_state==during_game){
			if(bird.state!=bird_delay)land.logic();
			bird.logic(1,game_state);
			if(bird.state!=bird_delay)pipe.logic(goals,bird,game_state);
		}else if(game_state==dying_game){
			bird.logic(2,game_state);
		}else if(game_state==end_game){
			if(panel.state==finish)button.logic(game_state);
			if(last_state>=10)panel.logic(goals,best_goals);
		}else if(game_state==start_game){
			restart();
			game_state=before_game;
		}
		break;
	default:break;
	}
	draw();
}
void CMainWindow::OnClose(){
    KillTimer(0);
	KillTimer(1);
    CFrameWnd::OnClose ();
}
void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point){
	if(game_state==0){
		game_state=1;
		pipe.add();
		bird.jump();
	}else if(game_state==1){
		bird.jump();
	}else if(game_state==3){
		button.click(point);
	}
}
void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	if(game_state==end_game && (::GetKeyState (VK_CONTROL) < 0)){
		screenShot(CRect(0,0,280,508),0,0,"ABCDEFG.bmp");
	}
	if(game_state==during_game && (::GetKeyState (VK_SHIFT) < 0)){
		goals+=10;
	}
}
void CMainWindow::draw(){

	CDC *cDC=this->GetDC();   

	m_bgcDC.SelectObject(&m_bgBitmap); 
	pic.bg[bg_state].TBlt(0,0,&m_cacheDC,&m_bgcDC);
	pipe.draw(pic,&m_cacheDC,&m_bgcDC);
	land.draw(pic,&m_cacheDC,&m_bgcDC);
	bird.paint(&m_cacheDC,&m_tempcDC);

	if(game_state==before_game ||game_state==during_game ||game_state==dying_game){
		int copy=goals,wei=1;
		while(copy/10){wei++;copy/=10;}copy=goals;
		int this_wei,first_pos=142-12*wei-wei/2;
		while(wei--){
			this_wei=copy%10;
			copy/=10;
			pic.font[this_wei].TBlt(first_pos+wei*25,60,&m_cacheDC,&m_bgcDC);
		}
		
		if(game_state==before_game){
			pic.text_ready.TBlt(50,140,&m_cacheDC,&m_bgcDC);
			pic.tutorial.TBlt(85,220,&m_cacheDC,&m_bgcDC);
		}
	}else if(game_state==end_game || game_state==start_game){
		if(last_state==0){
			pic.text_game_over.TBlt(50,105,&m_cacheDC,&m_bgcDC);
			last_state=1;
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_PANEL),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
		}else if(last_state>=1){
			pic.text_game_over.TBlt(50,115,&m_cacheDC,&m_bgcDC);
			if(last_state==10){
				panel.draw(pic,&m_cacheDC,&m_bgcDC);
				if(panel.state==2){
					button.draw(pic,&m_cacheDC,&m_bgcDC);
				}
			}else last_state++;
		}
	}

	m_cacheDC.SelectObject(&m_tempBitmap);
	cDC->BitBlt(0,0,m_client.Width(),m_client.Height(),&m_cacheDC,0,0,SRCCOPY); 

	ReleaseDC(cDC);
}
void CMainWindow::restart(){
	bg_state=rand()%2;
	game_state=0;
	last_state=0;
	goals=0;

	pipe.recover();
	land.recover();
	bird.recover();
	panel.recover();
}
void CMainWindow::screenShot(CRect rect,int left,int top,char *name){
    CBitmap*  m_pBitmap;
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
   	CPaintDC   dc(pMainFrame); 
	
	m_pBitmap=new   CBitmap;   
	m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   

	CDC   memDC;  
	memDC.CreateCompatibleDC(&dc); 
	CBitmap memBitmap, *oldmemBitmap;
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	
    oldmemBitmap = memDC.SelectObject(&memBitmap);
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,left, top, SRCCOPY);
	BITMAP bmp;
    memBitmap.GetBitmap(&bmp);
    
    FILE *fp = fopen(name, "w+b");
	
    BITMAPINFOHEADER bih = {0};
    bih.biBitCount = bmp.bmBitsPixel;
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
    bih.biWidth = bmp.bmWidth;
    
    BITMAPFILEHEADER bfh = {0};
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];
	
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);
	
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);
    delete [] p;	
    fclose(fp);
	memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();
}
