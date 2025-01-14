#include "ui.h"

IMAGE plate;
vector<IMAGE> imgs;

// 棋盘尺寸
const int BOARD_ROW = 10;  // 9x10的棋盘
const int BOARD_COL = 9;
const int CELL_SIZE = 60;  // 每个棋盘格子的尺寸
const int BOARD_WIDTH = BOARD_COL * CELL_SIZE;
const int BOARD_HEIGHT = BOARD_ROW * CELL_SIZE; // 10行棋盘

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD *dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD *draw = GetImageBuffer(); 
	DWORD *src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

// 绘制棋子
void drawBoard(vector<vector<int>>& board, vector<vector<int>>& valid_moves) {
	BeginBatchDraw();
	putimage(0, 0, &plate);
    for(int i=0; i<BOARD_ROW; ++i){
		for(int j=0; j<BOARD_COL; ++j){
			if(board[i][j]!=-1){
				int cy = i * CELL_SIZE, cx = j * CELL_SIZE;
				drawAlpha(&imgs[board[i][j]], cx, cy);
			}
		}
	}
	setcolor(YELLOW);
	setlinestyle(PS_SOLID,6);
	for(auto& v: valid_moves){
		int cy = v[2] * CELL_SIZE + CELL_SIZE/2 , cx = v[3] * CELL_SIZE + CELL_SIZE/2;
		circle(cx, cy, CELL_SIZE/2);
	}
	EndBatchDraw();
}

void loadImage(){
    imgs.resize(14);
    loadimage(&imgs[0], L"F:\\chess\\images\\0.png", 60, 60);
    loadimage(&imgs[1], L"F:\\chess\\images\\1.png", 60, 60);
    loadimage(&imgs[2], L"F:\\chess\\images\\2.png", 60, 60);
    loadimage(&imgs[3], L"F:\\chess\\images\\3.png", 60, 60);
    loadimage(&imgs[4], L"F:\\chess\\images\\4.png", 60, 60);
    loadimage(&imgs[5], L"F:\\chess\\images\\5.png", 60, 60);
    loadimage(&imgs[6], L"F:\\chess\\images\\6.png", 60, 60);
    loadimage(&imgs[7], L"F:\\chess\\images\\7.png", 60, 60);
    loadimage(&imgs[8], L"F:\\chess\\images\\8.png", 60, 60);
    loadimage(&imgs[9], L"F:\\chess\\images\\9.png", 60, 60);
    loadimage(&imgs[10], L"F:\\chess\\images\\10.png", 60, 60);
    loadimage(&imgs[11], L"F:\\chess\\images\\11.png", 60, 60);
    loadimage(&imgs[12], L"F:\\chess\\images\\12.png", 60, 60);
    loadimage(&imgs[13], L"F:\\chess\\images\\13.png", 60, 60);
    
    loadimage(&plate, L"F:\\chess\\images\\board.png", 540, 600);
}
