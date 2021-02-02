#include "stdafx.h"
#include "Graph.h"


CGraph::CGraph()
{
	InitGraph();   //��ʼ��ͼ
}


CGraph::~CGraph()
{
}

////��ʼ��ͼ
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	//��ʼ�����������Ϣ
	for (int i = 0; i < MAXVEXNUM; i++) {
		//��ʼ������
		m_Vertices[i] = -1;
	}

	for (int i = 0; i < MAXVEXNUM; i++) {
		for (int j = 0; j < MAXVEXNUM; j++) {
			//��ʼ����
			m_AdjMatrix[i][j] = false;
		}
	}

}

//���Ӷ��㣬����ö������
int CGraph::AddVertex(int nInfo)
{
	if (m_nVexnum >= MAXVEXNUM) {
		return 0;
	}
	m_Vertices[m_nVexnum] = nInfo;
	m_nVexnum++;
	return m_nVexnum;
}

//���ɱ�  ��ʼ���ڽӾ���
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//�Ӷ���������ȡ����Ӧ�Ķ���
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//�����������Ļ���Ϣ
bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

//���µ�nIndex������Ϊinfo
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//��ȡͼ�ж���ĸ���
int CGraph::GetVexnum()
{
	return m_nVexnum;
}

//����ͼ�ṹ
void CGraph::ClearGraph(void)
{
	InitGraph();
}

//�����������λ��
void CGraph::ChangeVerex(int nIndex1, int nIndex2)
{
	int Temp = m_Vertices[nIndex1];
	m_Vertices[nIndex1] = m_Vertices[nIndex2];
	m_Vertices[nIndex2] = Temp;
}



