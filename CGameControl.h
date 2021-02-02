#pragma once
#include"global.h"
#include"graph.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	//开始游戏函数
	void StartGame();

	//获得某行某列的图片编号函数
	int GetElement(int nRow, int nCol);

	void SetFirstPoint(int nRow, int nCol);             //设置第一个点函数
	void SetSecPoint(int nRow, int nCol);               //设置第二个点函数

	//连接判断函数
	bool Link(Vertex avPath[MAXVEXNUM], int &nVexnum);

	bool IsWin(int nTime);
	bool IsWin();
	bool Help(Vertex avPath[MAXVEXNUM], int &nVexnum);  //帮助、提示方法	
	void Reset(void);            //实现重排
	bool select(Vertex avPath[MAXVEXNUM], int & nVexnum);               //找到任意位置同号项并消去
	static int s_nRow;               //游戏行数
	static int s_nCols;               //游戏列数
	static int s_nPicNum;               //游戏行数

private:
	CGraph m_graph;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;

};



