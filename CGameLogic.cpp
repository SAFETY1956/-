#include "stdafx.h"
#include "CGameLogic.h"
#include"CGameControl.h"
#include<iostream>
using namespace std;

typedef struct {                 //������ʱջ
	int top;                //ջ��λ��
	int stacksize;          //ջ���õ��������
} SqStack;



CGameLogic::CGameLogic()
{
	m_nVexNum = 0;     //������ʵ��Ԫ�صĸ���
	m_nCorner = 0;     //·���еĹյ���
}


CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(CGraph &g) {
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	//�����ڴ�ռ�
	int *pGameMap = new int [nRows*nCols];
	//���ٻ�ɫ
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0;i < nPicNum;i++) {
		//�ظ���
		for (int j = 0;j < nRepeatNum;j++) {
			pGameMap[nCount++] = i;			
		}
	}
	//��������
	srand((int)time(NULL));

	//������⽻����������
	int nVertexNum = nRows * nCols;
	for (int i = 0;i < nVertexNum;i++) {
		//����õ���������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;

		//����������ֵ
		int nTmp = pGameMap[nIndex1];
		pGameMap[nIndex1] = pGameMap[nIndex2];
		pGameMap[nIndex2] = nTmp;
	}
	for (int i = 0;i < nVertexNum;i++) {
		g.AddVertex(pGameMap[i]);
	}
	//����ͼ��ϵ����
	for (int i = 0;i < nRows;i++) {
		for (int j = 0;j < nCols;j++) {
			UpdateArc(g, i, j);
		}
	}

}
void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol) {
	int nCols= CGameControl::s_nCols;
	int nV1Index = nRow * nCols + nCol;
	if (nCol > 0)   //�������
	{
		int nV2Index = nV1Index - 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж���������ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < nCols - 1)   //�ұ�����
	{
		int nV2Index = nV1Index + 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж����ұ����ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)   //���Ϸ�����
	{
		int nV2Index = nV1Index - nCols;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж������Ϸ����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < nCols - 1)   //���·�����
	{
		int nV2Index = nV1Index + nCols;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж������·����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}

//�����жϺ���
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	//��ö���������
	int nV1Index = v1.row *  nCols + v1.col;
	int nV2Index = v2.row *  nCols + v2.col;

	PushVertex(nV1Index);  //ѹ���һ����

	//��Ѱ����֮�����ͨ·��
	if (SearchPath(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}

	PopVertex();

	/*�޸��ж���Ȧ������*/

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


//���һ��·������
void CGameLogic::PushVertex(int nV)
{
	//������ѹջ
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//�ж��Ƿ��γ��µĹյ�
	if (IsCornor())
	{
		m_nCorner++;
	}
}

//ȡ��һ��·������
void CGameLogic::PopVertex()
{
	//�ж��Ƿ��γɹյ㣬������ڹյ㣬��ȡ��֮ǰ���ٹյ���
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//�õ�·�������ص��Ƕ�����
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

//���Ӻ���
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	//��ö���������
	int nV1Index = v1.row * nCols + v1.col;
	int nV2Index = v2.row * nCols + v2.col;

	//���¶���
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);

	//���±���Ϣ
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}


//ʹ�����������������Ѱһ����Ч��ͨ·��
bool CGameLogic::SearchPath(CGraph &graph, int nV0, int nV1)
{
	//�õ�������
	int nVexnum = graph.GetVexnum();

	//����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			
			PushVertex(nVi);
			//���յ�������2 ʱ��ֱ�ӷ����ö���
			if (m_nCorner > 2)
			{
				PopVertex();          //ȡ��ѹ��Ķ���
				continue;
			}
			//��ǰ���㲻��nViʱ��������Ѱ��һ����������ͨ�Ķ���
			if (nVi != nV1)
			{
				if (graph.GetVertex(nVi) != BLANK)
				{
					PopVertex();      //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
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

			PopVertex();     //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
		}
	}
	return false;
}

//�ж϶����Ƿ�����·���д���
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

//�жϹյ����Ч��
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
	//�õ�������
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���
		if (graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		//�����õ��ڶ���ͬɫ����
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//�����i����͵�j����ͬɫ
				if (graph.GetVertex(i) == graph.GetVertex(j))
				{
					//ѹ���һ����
					PushVertex(i);
					if (SearchPath(graph, i, j) == true)
					{
						return true;
					}
					//ȡ��ѹ��Ķ���ʱ����PushVertex(i);��Ӧ
					PopVertex();
				}

			}
		}
	}
	return false;
}


//�ж�ͼ�ж����ǲ���Ϊ��
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


//ʵ��ͼ�ṹ������
void CGameLogic::ResetGraph(CGraph& graph)
{
	int nRows = CGameControl::s_nRow;
	int nCols = CGameControl::s_nCols;
	//��������������������������ֵ
	for (int i = 0; i < 200; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAXVEXNUM;
		int nIndex2 = rand() % MAXVEXNUM;

		//����������ֵ
		graph.ChangeVerex(nIndex1, nIndex2);
	}

	//���»���Ϣ
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			UpdateArc(graph, i, j);
		}
	}

}
//ʵ�ֵ���
bool CGameLogic::Select(CGraph& graph) {
	//�õ�������
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���
		if (graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		//�����õ��ڶ���ͬɫ����
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//�����i����͵�j����ͬɫ
				if (graph.GetVertex(i) == graph.GetVertex(j))
				{
					//ѹ���һ����
					PushVertex(i);
					//ѹ��ڶ�����
					PushVertex(j);
					return true;
				}

			}
		}
	}
	return false;
}



