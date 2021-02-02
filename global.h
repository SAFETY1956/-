#pragma once

typedef struct tagVertex {
	int row;
	int col;
	int info;
}Vertex;

#define BLANK -1
#define MAX_PIC_NUM 16
#define MAP_TOP             50         //游戏地图左上角纵坐标
#define MAP_LETF            50         //游戏地图左上角横坐标

#define GAME_LOSE           -1   //失败
#define GAME_SUCCESS        0    //获胜
#define GAME_PLAY           1    //游戏正在进行
#define MAXVEXNUM           160
