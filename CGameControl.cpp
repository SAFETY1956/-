#include "stdafx.h"
#include "CGameControl.h"
#include"CGameLogic.h"
int CGameControl::s_nRow = 10;
int CGameControl::s_nCols = 16;
int CGameControl::s_nPicNum = 10;
CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame() {
	CGameLogic gamelogic;
	gamelogic.InitMap(m_graph);
}




//���ĳ��ĳ�е�ͼƬ��ź���
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * 16 + nCol);
}

//���õ�һ���㺯��
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//���õڶ����㺯��
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

//�����ж�   �����жϺ���
bool CGameControl::Link(Vertex avPath[MAXVEXNUM], int & nVexnum)
{
	int nCols = CGameControl::s_nCols;
	//�ж�ѡ�еĵ��Ƿ�Ϊͬһ��ͼƬ����Ϊͬһ��ͼƬ��������ͨ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ�������ͬ������ͨ
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * nCols + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * nCols + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//�ж��Ƿ������ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//����·������
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

bool CGameControl::IsWin(int nTime)
{
	//�����߼�������
	CGameLogic logic;

	//�ж���Ϸʱ��
	if (nTime <= 0)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.IsBlank(m_graph) == true)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::IsWin()
{
	//�����߼�������
	CGameLogic logic;

	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.IsBlank(m_graph) == true)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

//����ʾ����ť����ʵ��
bool CGameControl::Help(Vertex avPath[MAXVEXNUM], int & nVexnum)
{
	CGameLogic logic;

	//�ж��Ƿ�Ϊ��
	if (logic.IsBlank(m_graph) == true)
	{
		return false;
	}
	//����һ����Ч����ʾ·��
	if (logic.SearchValidPath(m_graph))
	{
		//����·������
		nVexnum = logic.GetVexPath(avPath);

		return true;
	}
	return false;

}

//ʵ�����Ź���
void CGameControl::Reset(void)
{
	//����ͼ�ж���
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}

bool CGameControl::select(Vertex avPath[MAXVEXNUM], int & nVexnum) {
	CGameLogic logic;
	if (logic.Select(m_graph))
	{
		//����·������
		nVexnum = logic.GetVexPath(avPath);

		return true;
	}
	return false;
}
