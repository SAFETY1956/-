#pragma once

#include "global.h";

//ͼ  ���ݽṹ��

class CGraph
{
public:
	CGraph();
	~CGraph();

	typedef int Vertices[MAXVEXNUM];						//������������
	typedef bool AdjMatrix[MAXVEXNUM][MAXVEXNUM];		    //�ڽӾ���


protected:

	Vertices m_Vertices;					//��������  
	AdjMatrix m_AdjMatrix;					//��ϵ����  

	int m_nVexnum;		//������
	int m_nArcnum;		//����

public:

	//��ʼ��ͼ
	void InitGraph();

	//��Ӷ��㣬����ö������
	int AddVertex(int nInfo);

	//������ɱ�
	void AddArc(int nV1Index, int nV2Index);

	//��ȡ����������
	int GetVertex(int nIndex);

	//�����������ı���Ϣ
	bool GetArc(int nV1Index, int nV2Index);

	//���¶���,��ͼ����������������ΪNIndex�Ķ����ֵ����Ϊinfo
	void UpdateVertex(int nIndex, int info);

	//��ȡͼ�ж���ĸ���
	int GetVexnum();

	//����ͼ�ṹ
	void ClearGraph(void);

	//�����������λ��
	void ChangeVerex(int nIndex1, int nIndex2);


};

