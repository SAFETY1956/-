#pragma once
#include"global.h"
#include"graph.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

public:
	void InitMap(CGraph &g);
	void UpdateArc(CGraph &g, int nRow, int nCol);         //若有边则更新图结构，并返回
	bool IsLink(CGraph &g, Vertex v1, Vertex v2);  //判断是否联通
	void Clear(CGraph &graph, Vertex v1, Vertex v2);       //消子
	bool SearchPath(CGraph &graph, int nV0, int nV1);      //判断选择的两个顶点是否联通
	bool SearchValidPath(CGraph &graph);                   //提示
	int GetVexPath(Vertex avPath[MAXVEXNUM]);             //得到路径，返回的是顶点数	
	void ResetGraph(CGraph& graph);               //实现图结构的重排
	bool IsBlank(CGraph &graph);                       //判断图中顶点是不是全是空
	bool Select(CGraph& graph);
protected:
	bool IsExsit(int nVi);                             //判断顶点是否已在路径中存在
	bool IsCornor(void);                              //判断拐点的有效性
	void PushVertex(int v);                           //添加一个路径顶点
	void PopVertex();                                   //取出一个路径顶点

private:
	Vertex m_avPath[MAXVEXNUM];    //保存连接路径的起始点、拐点、终点
	int m_anPath[MAXVEXNUM];		//保存在进行连接判断时所经过的顶点
	int m_nCorner;						//保存路径中的拐点数
	int m_nVexNum;						//表示顶点数

};



