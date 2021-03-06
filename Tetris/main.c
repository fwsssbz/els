#include<windows.h>
#include"elsh.h"

	LRESULT CALLBACK PELouSi(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	

	
	//初始化窗口类 
	WNDCLASSEX wc;
 	HWND hWnd;
 	MSG mSg;
	
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL ,NULL);
	wc.hIcon = LoadIcon(NULL,NULL);
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = PELouSi;
	wc.lpszClassName = "els";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	
	
	//注册窗口
	if(0 == RegisterClassEx(&wc)){
		//error
		int a = GetLastError();
		return 0;
	} 
	
	//创建窗口
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW|WS_SIZEBOX, "els", "俄罗斯方块", WS_OVERLAPPEDWINDOW, 100, 50, 500, 640, 	NULL, NULL, hInstance, NULL); 
	if(NULL == hWnd){
		return 0;
	} 
	
	//显示窗口
	ShowWindow(hWnd, SW_SHOWNORMAL);
	
	//消息循环
	while(GetMessage(&mSg, NULL, 0, 0)){
		//翻译消息 
		TranslateMessage(&mSg);
		//分发消息 
		DispatchMessage(&mSg);
		
	}
	 
	return 0;
}

LRESULT CALLBACK PELouSi(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT pt;
	HDC hdc;
	switch(nMsg){
		
		case WM_CREATE:
			OnCreate();
			break;
		case WM_PAINT:
			hdc=BeginPaint(hWnd, &pt);
			
			OnPaint(hdc);
			
			EndPaint(hWnd, &pt);
			break;
			
		case WM_KEYDOWN:
			switch(wParam){
				case VK_RETURN:
					OnReturn(hWnd);
					break;
				case VK_LEFT:
					//左移
					moveleft(hWnd);
					break;
				case VK_RIGHT:
					moveright(hWnd);
					break;
				case VK_SPACE:
					changesquare(hWnd);
					break;
				case VK_DOWN:
					movedown(hWnd);
					break;
			} 
			 
			 break;
			
		case WM_TIMER:
			OnTimer(hWnd);
			
			break;
		case WM_DESTROY:
			KillTimer(hWnd, TIMER1);
			PostQuitMessage(0);
			break;
	}
	
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}


