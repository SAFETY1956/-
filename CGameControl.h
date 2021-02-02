#pragma once
#include"global.h"
#include"graph.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	//��ʼ��Ϸ����
	void StartGame();

	//���ĳ��ĳ�е�ͼƬ��ź���
	int GetElement(int nRow, int nCol);

	void SetFirstPoint(int nRow, int nCol);             //���õ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);               //���õڶ����㺯��

	//�����жϺ���
	bool Link(Vertex avPath[MAXVEXNUM], int &nVexnum);

	bool IsWin(int nTime);
	bool IsWin();
	bool Help(Vertex avPath[MAXVEXNUM], int &nVexnum);  //��������ʾ����	
	void Reset(void);            //ʵ������
	bool select(Vertex avPath[MAXVEXNUM], int & nVexnum);               //�ҵ�����λ��ͬ�����ȥ
	static int s_nRow;               //��Ϸ����
	static int s_nCols;               //��Ϸ����
	static int s_nPicNum;               //��Ϸ����

private:
	CGraph m_graph;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;

};



