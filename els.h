#ifndef DEF_ELSH
#define DEF_ELSH 

#include<windows.h>
#define TIMER1 1234

void OnPaint(HDC hdc);
//画方块 
void PaintSquare(HDC hdc);

//每次的动作 
int OnTimer(HWND hWnd);

void OnCreate();
//随机产生方块 
int createradom();
//复制方块 
void copysquare();
void copysquare2();

void OnReturn(HWND hWnd);

//下落
void movedown(HWND hWnd);
void squaredown(); 
//左移
void moveleft(HWND hWnd); 
void toleft();
//右移
void moveright(HWND hWnd);
void toright(); 
// 消除方块
void destroysq(); 
//显示分数
void showscore(HDC hdc);
 


//判断能否下落 
int cansqdown(); 
//判断能否左移
int canmoveleft(); 
//判断能否右移
int canmoveright(); 
//判断方块下面有没有其他方块 
int cansqdown2();
//判断方块能否变形
int canchanges(); 
//判断长条能否变形
int canchangerec(); 
//结束
int isover();
//下一个
void getnext(); 
 
void change1to2();

//显示底部方块 
void showsquare(HDC hdc);
//判断方块下面有没有其他方块 
int cansqdown2();

//变形
void changesquare(HWND hWnd); 

void normalchange();

void rectchange();








#endif
