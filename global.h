#pragma once

typedef struct tagVertex {
	int row;
	int col;
	int info;
}Vertex;

#define BLANK -1
#define MAX_PIC_NUM 16
#define MAP_TOP             50         //��Ϸ��ͼ���Ͻ�������
#define MAP_LETF            50         //��Ϸ��ͼ���ϽǺ�����

#define GAME_LOSE           -1   //ʧ��
#define GAME_SUCCESS        0    //��ʤ
#define GAME_PLAY           1    //��Ϸ���ڽ���
#define MAXVEXNUM           160
