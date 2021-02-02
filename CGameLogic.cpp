#include "stdafx.h"
#include "CGameLogic.h"
#include"CGameControl.h"
#include<iostream>
using namespace std;

typedef struct {                 //创建临时栈
	int top;                //栈顶位置
	int stacksize;          //栈可用的最大容量
} SqStack;



CGameLogic::CGameLogic()
{
	m_nVexNum = 0;     //数组中实际元素的个数
	m_nCorner = 0;     //路径中的拐点数
}


CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(CGraph &g) {
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	//开辟内存空间
	int *pGameMap = new int [nRows*nCols];
	//多少花色
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0;i < nPicNum;i++) {
		//重复数
		for (int j = 0;j < nRepeatNum;j++) {
			pGameMap[nCount++] = i;			
		}
	}
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	int nVertexNum = nRows * nCols;
	for (int i = 0;i < nVertexNum;i++) {
		//随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;

		//交换两个数值
		int nTmp = pGameMap[nIndex1];
		pGameMap[nIndex1] = pGameMap[nIndex2];
		pGameMap[nIndex2] = nTmp;
	}
	for (int i = 0;i < nVertexNum;i++) {
		g.AddVertex(pGameMap[i]);
	}
	//更新图关系数组
	for (int i = 0;i < nRows;i++) {
		for (int j = 0;j < nCols;j++) {
			UpdateArc(g, i, j);
		}
	}

}
void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol) {
	int nCols= CGameControl::s_nCols;
	int nV1Index = nRow * nCols + nCol;
	if (nCol > 0)   //左边相邻
	{
		int nV2Index = nV1Index - 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与左边相邻的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < nCols - 1)   //右边相邻
	{
		int nV2Index = nV1Index + 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与右边相邻的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)   //正上方相邻
	{
		int nV2Index = nV1Index - nCols;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与正上方的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < nCols - 1)   //正下方相邻
	{
		int nV2Index = nV1Index + nCols;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与正下方的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}

//连接判断函数
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	//获得顶点索引号
	int nV1Index = v1.row *  nCols + v1.col;
	int nV2Index = v2.row *  nCols + v2.col;

	PushVertex(nV1Index);  //压入第一个点

	//搜寻两点之间的连通路径
	if (SearchPath(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}

	PopVertex();

	/*修改判断外圈可连接*/

	if (v1.row == v2.row) {
		if (v1.row == 0 || v1.row == nRows - 1) {
			return true;
		}
	}

	if (v1.col == v2.col) {
		if (v1.col == 0 || v1.col == nCols - 1) {
			return true;
		}
	}
	return false;
}


//添加一个路径顶点
void CGameLogic::PushVertex(int nV)
{
	//将顶点压栈
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//判断是否形成新的拐点
	if (IsCornor())
	{
		m_nCorner++;
	}
}

//取出一个路径顶点
void CGameLogic::PopVertex()
{
	//判断是否形成拐点，如果存在拐点，在取出之前减少拐点数
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//得到路径，返回的是顶点数
int CGameLogic::GetVexPath(Vertex avPath[MAXVEXNUM])
{

	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < nCols; point.col++)
		{
			for (point.row = 0; point.row < nRows; point.row++)
			{
				if (point.row * nCols + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}
	return m_nVexNum;
}

//消子函数
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	//获得顶点索引号
	int nV1Index = v1.row * nCols + v1.col;
	int nV2Index = v2.row * nCols + v2.col;

	//更新顶点
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);

	//更新边信息
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}


//使用深度优先搜索法搜寻一条有效连通路径
bool CGameLogic::SearchPath(CGraph &graph, int nV0, int nV1)
{
	//得到顶点数
	int nVexnum = graph.GetVexnum();

	//遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			
			PushVertex(nVi);
			//当拐点数大于2 时，直接放弃该顶点
			if (m_nCorner > 2)
			{
				PopVertex();          //取出压入的顶点
				continue;
			}
			//当前顶点不是nVi时，继续搜寻下一个相邻且连通的顶点
			if (nVi != nV1)
			{
				if (graph.GetVertex(nVi) != BLANK)
				{
					PopVertex();      //取出压入的顶点，与PushWertex(nVi)对应
					continue;
				}
				if (SearchPath(graph, nVi, nV1))
				{
					return true;
				}
			}
			else
			{
				return true;
			}

			PopVertex();     //取出压入的顶点，与PushWertex(nVi)对应
		}
	}
	return false;
}

//判断顶点是否已在路径中存在
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi)
		{
			return true;
		}
	}
	return false;
}

//判断拐点的有效性
bool CGameLogic::IsCornor(void)
{
	if (m_nVexNum >= 3)
	{
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}
bool CGameLogic::SearchValidPath(CGraph& graph)
{
	//得到顶点数
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//得到第一个非空顶点
		if (graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		//遍历得到第二个同色顶点
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//如果第i个点和第j个点同色
				if (graph.GetVertex(i) == graph.GetVertex(j))
				{
					//压入第一个点
					PushVertex(i);
					if (SearchPath(graph, i, j) == true)
					{
						return true;
					}
					//取出压入的顶点时，与PushVertex(i);对应
					PopVertex();
				}

			}
		}
	}
	return false;
}


//判断图中顶点是不是为空
bool CGameLogic::IsBlank(CGraph &graph)
{
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		if (graph.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}


//实现图结构的重排
void CGameLogic::ResetGraph(CGraph& graph)
{
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	//随机交换顶点数组中两个顶点的值
	for (int i = 0; i < 200; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAXVEXNUM;
		int nIndex2 = rand() % MAXVEXNUM;

		//交换两个数值
		graph.ChangeVerex(nIndex1, nIndex2);
	}

	//更新弧信息
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			UpdateArc(graph, i, j);
		}
	}

}
//实现道具
bool CGameLogic::Select(CGraph& graph) {
	//得到顶点数
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//得到第一个非空顶点
		if (graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		//遍历得到第二个同色顶点
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//如果第i个点和第j个点同色
				if (graph.GetVertex(i) == graph.GetVertex(j))
				{
					//压入第一个点
					PushVertex(i);
					//压入第二个点
					PushVertex(j);
					return true;
				}

			}
		}
	}
	return false;
}



