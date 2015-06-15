#include "PipeList.h"


void PipeList::recover(){
	int count=pipe.GetCount();
	for(int i=0;i<count;i++){
		pipe.RemoveHead();
	}
}
void PipeList::add(){
	Pipe temp;
	pipe.AddTail(temp);
}
void PipeList::logic(int &goals,Bird &bird,int &game_state){
	int count=pipe.GetCount();
	for(int i=0;i<count;i++){
		Pipe temp=pipe.GetHead();
		pipe.RemoveHead();
		temp.logic();
		if(temp.pos_x==64){
			goals+=1;
			mciSendString(_T("close mymusic"), NULL, 0, NULL);
			mciSendString(mcicmd, NULL,0, NULL);
			mciSendString(_T("play mymusic"),NULL,0, NULL);	
		}
		if(temp.pos_x>=-70)pipe.AddTail(temp);

		if(23+bird.y+48-$d>400){
			bird.y=400-230-48+$d;
			bird.stop();
			game_state=2;
		}else if(!(65+48-$d < temp.pos_x || temp.pos_x+52<65+$d)){
			if(!(230+bird.y+$d > temp.pos_y+320 && temp.pos_y+420 > 230+bird.y+48-$d)){
				game_state=2;
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_HIT),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
			}
		}
	}
	if((pipe.GetTail()).pos_x<=140){
		Pipe temp;
		pipe.AddTail(temp);
	}
}
void PipeList::draw(Pic &All,CDC* To,CDC* From){
	int count=pipe.GetCount();
	for(int i=0;i<count;i++){
		Pipe temp=pipe.GetHead();
		pipe.RemoveHead();
		pipe.AddTail(temp);
		All.pipe_down.TBlt(temp.pos_x,temp.pos_y,To,From);
		All.pipe_up.TBlt(temp.pos_x,temp.pos_y+420,To,From);
	}
}
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	HRSRC	hRes	= ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem	= ::LoadResource(NULL, hRes);
	DWORD	dwSize	= ::SizeofResource(NULL, hRes);
	DWORD dwWrite = 0;
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

PipeList::PipeList(){
	TCHAR tmpwav[_MAX_PATH];
	::GetTempPath(_MAX_PATH,tmpwav);
	_tcscat_s(tmpwav, _T("testapp_background.wav"));
	ExtractResource(tmpwav, _T("WAVE"), MAKEINTRESOURCE(IDR_WAVE_POINT));
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"),tmpwav);
}