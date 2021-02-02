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
	void UpdateArc(CGraph &g, int nRow, int nCol);         //���б������ͼ�ṹ��������
	bool IsLink(CGraph &g, Vertex v1, Vertex v2);  //�ж��Ƿ���ͨ
	void Clear(CGraph &graph, Vertex v1, Vertex v2);       //����
	bool SearchPath(CGraph &graph, int nV0, int nV1);      //�ж�ѡ������������Ƿ���ͨ
	bool SearchValidPath(CGraph &graph);                   //��ʾ
	int GetVexPath(Vertex avPath[MAXVEXNUM]);             //�õ�·�������ص��Ƕ�����	
	void ResetGraph(CGraph& graph);               //ʵ��ͼ�ṹ������
	bool IsBlank(CGraph &graph);                       //�ж�ͼ�ж����ǲ���ȫ�ǿ�
	bool Select(CGraph& graph);
protected:
	bool IsExsit(int nVi);                             //�ж϶����Ƿ�����·���д���
	bool IsCornor(void);                              //�жϹյ����Ч��
	void PushVertex(int v);                           //���һ��·������
	void PopVertex();                                   //ȡ��һ��·������

private:
	Vertex m_avPath[MAXVEXNUM];    //��������·������ʼ�㡢�յ㡢�յ�
	int m_anPath[MAXVEXNUM];		//�����ڽ��������ж�ʱ�������Ķ���
	int m_nCorner;						//����·���еĹյ���
	int m_nVexNum;						//��ʾ������

};



