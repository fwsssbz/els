#include"elsh.h"
#include<time.h>


char square[20][10] = {0};
char elem[2][4] = {0}; 
char currsq[2][4] = {0};
int squareid;
int nextid;
int sqline;
int sqrow;
int score = 0;
int times = 500;
int sqdown;

void OnPaint(HDC hdc){
	//创建兼容性DC 
	HDC hMemDC=CreateCompatibleDC(hdc);
	HBITMAP hBitMap=CreateCompatibleBitmap(hdc, 500, 600);
	SelectObject(hMemDC, hBitMap);

	PaintSquare(hMemDC);
	showscore(hMemDC); 
	BitBlt(hdc, 0, 0, 500, 600, hMemDC, 0, 0, SRCCOPY);	
	
	
	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}


void showscore(HDC hdc){
	int i,j;
	char strscore[10] = {0};
	Rectangle(hdc, 300, 0, 500, 600);
	Rectangle(hdc, 310, 100, 450, 200);
	for( i = 0;i < 2;i++){
		for(j = 0;j < 4;j++){
			if(elem[i][j] == 1){
				Rectangle(hdc, 325+j*30, 125+i*30, 325+j*30+30, 125+i*30+30);
			}
		}
	}
	itoa(score, strscore, 10);
	TextOut(hdc, 400, 450, strscore, strlen(strscore) );

}

void OnCreate(){
	
	srand((unsigned int)time(NULL));
	createradom();
	getnext();
	copysquare();
	createradom();
}
//画方块 
void PaintSquare(HDC hdc){
	int i = 0,j = 0;
	Rectangle(hdc, 0, 0, 300, 600);
	
	for(i=0; i<20; i++){
		for(j=0; j<10; j++){
			if(square[i][j]==1 ){
				
				Rectangle(hdc, j*30, i*30, j*30+30, i*30+30);
			}
		}
	}	
		showsquare(hdc);
}
//随机产生方块 
int createradom(){
	
	
	int n=rand()%7;
	switch(n){
		case 0: elem[0][0] = 1; elem[0][1] = 1; elem[0][2] = 0; elem[0][3] = 0;
				elem[1][0] = 0; elem[1][1] = 1; elem[1][2] = 1; elem[1][3] = 0;

				break;
		case 1: elem[0][0] = 0; elem[0][1] = 1; elem[0][2] = 1; elem[0][3] = 0;
				elem[1][0] = 1; elem[1][1] = 1; elem[1][2] = 0; elem[1][3] = 0;
				
				break;
		case 2: elem[0][0] = 1; elem[0][1] = 0; elem[0][2] = 0; elem[0][3] = 0;
				elem[1][0] = 1; elem[1][1] = 1; elem[1][2] = 1; elem[1][3] = 0;
			
				break;
		case 3: elem[0][0] = 0; elem[0][1] = 0; elem[0][2] = 1; elem[0][3] = 0;
				elem[1][0] = 1; elem[1][1] = 1; elem[1][2] = 1; elem[1][3] = 0;
			
				break;
		case 4: elem[0][0] = 0; elem[0][1] = 1; elem[0][2] = 0; elem[0][3] = 0;
				elem[1][0] = 1; elem[1][1] = 1; elem[1][2] = 1; elem[1][3] = 0;
			
				break;
		case 5: elem[0][0] = 0; elem[0][1] = 1; elem[0][2] = 1; elem[0][3] = 0;
				elem[1][0] = 0; elem[1][1] = 1; elem[1][2] = 1; elem[1][3] = 0;
			
				break;
		case 6: elem[0][0] = 1; elem[0][1] = 1; elem[0][2] = 1; elem[0][3] = 1;
				elem[1][0] = 0; elem[1][1] = 0; elem[1][2] = 0; elem[1][3] = 0;
			
				break;
	
	}
	nextid = n;
	return nextid; 
}

//复制方块 
void copysquare(){
	int i = 0,j = 0;
	for(i = 0 ;i < 2; i++){
		for(j = 0;j < 4;j++){
		square[i][j+3] = currsq[i][j];
		} 
	}
}

//void copysquare2(){
//	int i = 0,j = 0;
//	for(i = 0 ;i < 2; i++){
//		for(j = 0;j < 4;j++){
//		currsq[i][j] = elem[i][j];
//		} 
//	}
//}

void OnReturn(HWND hWnd){
	
	SetTimer(hWnd, TIMER1, 	times, NULL); 
}
//方块下落 
void squaredown(){
	int i,j;
	
	for(i = 19;i >= 0;i--){
		for(j = 0;j < 10;j++){
			if(square[i][j]==1){
				square[i+1][j] = square[i][j];
				square[i][j] = 0;
			}
		}
	}
}


int OnTimer(HWND hWnd){
	int f = 0;
	HDC hdc=GetDC(hWnd);
	if(cansqdown() && cansqdown2()){
	squaredown();
	sqline++;
	f = 1;
  	}
  	else{
  		change1to2();
  		destroysq();
  		SetTimer(hWnd, TIMER1, 	times-score, NULL); 
  		if(!isover()){
  			KillTimer(hWnd, TIMER1);
  			return 0;
  		}
  		getnext();
  		copysquare();
  		createradom();
  	}
	OnPaint(hdc);
 
	ReleaseDC(hWnd, hdc);
	return f;
}

//判断方块是否到底 
int cansqdown(){
	int i;
	for(i = 0;i < 10;i++){
		if(square[19][i] == 1)
			return 0;
	}

	
	return 1;
}


void change1to2(){
	int i,j;
	for(i = 0;i < 20;i++){
		for(j = 0;j < 10;j++){
			if(square[i][j] == 1)
			 	square[i][j] = 2;
		}
	}
}

//显示底部方块 
void showsquare(HDC hdc){
	int i,j;
 	HBRUSH oldbrush;
	HBRUSH hbrush = CreateSolidBrush(RGB(50, 150, 52));
	oldbrush = SelectObject(hdc, hbrush);
	for(i=0; i<20; i++){
		for(j=0; j<10; j++){
			if(square[i][j] == 2){
				
				Rectangle(hdc, j*30, i*30, j*30+30, i*30+30);
			}
		}
	}
		hbrush = SelectObject(hdc, oldbrush);
		DeleteObject(hbrush);
}
//判断方块下面有无其他方块 
int cansqdown2(){
	int i,j;
		for(i = 19;i >= 0;i--){
		for(j = 0;j < 10;j++){
			if(square[i][j] == 1){
				if(square[i+1][j] == 2)
					return 0;
			}
		}
	}
	return 1;
}

//左移
void moveleft(HWND hWnd){
	
	if(canmoveleft()){
		HDC hdc =GetDC(hWnd);
		toleft();
		sqrow--;
		OnPaint(hdc) ;
		ReleaseDC(hWnd ,hdc);
 	}
	 sqdown = 0;
}
void toleft(){
	int i,j;
	for(j = 0;j < 10;j++){
		for(i = 0;i < 20;i++){
			if(square[i][j] == 1){
				
					square[i][j-1] = square[i][j];
					square[i][j] = 0;
				
			}
		}
	}
}


int canmoveleft(){
	int i,j;
	for(i = 0;i < 20;i++){
		if(square[i][0]==1)
			return 0;
	}
	for(i = 0;i < 20;i++){
		for(j = 0;j < 10;j++){
			if(square[i][j] == 1){
				if(square[i][j-1] == 2)
					return 0;
			}
		}
	}
	return 1;
}
//右移 
void moveright(HWND hWnd){
		if(canmoveright()){
		HDC hdc = GetDC(hWnd);
		toright();
		sqrow++;
		OnPaint(hdc);
		ReleaseDC(hWnd ,hdc);
 		}
 		 sqdown = 0;
}

void toright(){
		int i,j;
	for(i = 0;i < 20;i++){
		for(j = 9;j >= 0;j--){
			if(square[i][j] == 1){
				
					square[i][j+1] = square[i][j];
					square[i][j] = 0;
				
			}
		}
	}
}


int canmoveright(){
		int i,j;
	for(i = 0;i < 20;i++){
		if(square[i][9]==1)
			return 0;
	}
	for(i = 0;i < 20;i++){
		for(j = 0;j < 10;j++){
			if(square[i][j] == 1){
				if(square[i][j+1] == 2)
					return 0;
			}
		}
	}
	return 1;
}

//下落键
void movedown(HWND hWnd){
	if( sqdown == 0){
	OnTimer(hWnd);
	sqdown = 1;
	}
	else if(sqdown == 1){
		while(OnTimer(hWnd));
		sqdown = 0;
	}
}
//变形 
void changesquare(HWND hWnd){
	HDC hdc = GetDC(hWnd);
	switch(squareid){
		//普通变形 
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			if(canchanges()){
			normalchange();
			}
			else {
				return;
			}	
			break;
			//方形 
		case 5:
			
			break;
			//长条形 
		case 6:
			if(canchangerec()){
				rectchange();
			}
			else {
				return;
			}
			break;
		
	}
	OnPaint(hdc);
	ReleaseDC(hWnd, hdc);
	 sqdown = 0;
} 

void normalchange(){
	char tem[3][3] = {0};
	int i,j;
	int f=2;
	for(i = 0;i < 3;i++){
		for(j = 0;j < 3;j++){
			tem[i][j] = square[sqline+i][sqrow+j];
		}
	}
	for(i = 0;i < 3;i++){
		for(j = 0;j < 3;j++){
			square[sqline+i][sqrow+j] = tem[f][i];
			f--;
		}
		f = 2;
	}
}

void rectchange(){
	//竖条 
	if(square[sqline + 1][sqrow] == 1){
		square[sqline+1][sqrow] = 0;
		square[sqline-1][sqrow] = 0;
		square[sqline+2][sqrow] = 0;
		if(square[sqline][sqrow-1] == 2 || sqrow == 0){
			square[sqline][sqrow+1] = 1;
			square[sqline][sqrow+2] = 1;
			square[sqline][sqrow+3] = 1;
			sqrow++;			
		}else if(square[sqline][sqrow+1] == 2 || sqrow == 9) {
			square[sqline][sqrow-1] = 1;
			square[sqline][sqrow-2] = 1;
			square[sqline][sqrow-3] = 1;
			sqrow = sqrow - 2; 
		}else if(square[sqline][sqrow+2] == 2 || sqrow == 8){
			square[sqline][sqrow-1] = 1;
			square[sqline][sqrow-2] = 1;
			square[sqline][sqrow+1] = 1;
			sqrow = sqrow - 1;
		}
		else {
			square[sqline][sqrow+1] = 1;
			square[sqline][sqrow+2] = 1;
			square[sqline][sqrow-1] = 1;	
		}
	}// 横条 
	else if ( square[sqline][sqrow - 1] == 1){
		square[sqline][sqrow-1] = 0;
		square[sqline][sqrow+1] = 0;
		square[sqline][sqrow+2] = 0;
		if(square[sqline+1][sqrow] == 2){
			square[sqline-1][sqrow] = 1;
			square[sqline-3][sqrow] = 1;
			square[sqline-2][sqrow] = 1;
			sqline = sqline - 2;
		}else if(square[sqline+2][sqrow] == 2){
			square[sqline-1][sqrow] = 1;
			square[sqline+1][sqrow] = 1;
			square[sqline-2][sqrow] = 1;
			sqline = sqline - 1;
		}else {
			square[sqline+1][sqrow] = 1;
			square[sqline-1][sqrow] = 1;
			square[sqline+2][sqrow] = 1;
		}
	} 
}


int canchanges(){
	int i,j;
	for(i = 0;i < 3;i++){
		for(j = 0;j < 3;j++){
			if(square[sqline + i][sqrow + j] == 2)
				return 0;
		}
	}
//	if(sqrow < 0 || sqline + 2 > 9){
//		return 0;
//	}
	if(sqrow < 0){
		sqrow = 0;
	}
	else if(sqrow + 2 > 9){
		sqrow = 7;
	}
	return 1;
}

int canchangerec(){
	int i,j;
	for( i = 1;i < 4;i++){
		if(square[sqline][sqrow+i] == 2 || sqrow+i >9){
			break;
		}
	}
	for( j = 1;j < 4;j++){
		if(square[sqline][sqrow-j] == 2 || sqrow-j < 0){
			break;
		}
	}
	if(i-1+j-1 < 3){
		return 0;
	}
	return 1; 
}


void destroysq(){
	int i,j;
	int n = 0;
	int t = 0;
	for(i = 19;i >= 0;i--){
		for(j = 0; j < 10; j++){
			n += square[i][j];
		}
		if( n == 20){
			for( t = i - 1; t >= 0;t--){
				for( j = 0;j < 10; j++){
					square[t+1][j] = square[t][j];
				}
			}
			score++;
			i = 20;
		}
		n = 0;
	}
}


void getnext(){
	int i = 0,j = 0;
	for(i = 0 ;i < 2; i++){
		for(j = 0;j < 4;j++){
		currsq[i][j] = elem[i][j];
		} 
	}
	squareid = nextid;
	switch(squareid){
		case 0:		
		case 1: 
		case 2:
		case 3:
		case 4:
				sqline = 0;
				sqrow = 3;break;
		case 5:		
		case 6: sqline = 0;
				sqrow = 4;break;
	}
}

int isover(){
	int i;
	for(i = 0; i < 10 ;i++){
		if(square[0][i] == 2){
			MessageBox(NULL, "Game Over！！！", "提示", MB_OK);
			return 0;
		}
	}
	return 1;
}
