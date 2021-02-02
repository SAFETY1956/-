#pragma once
#include"CGameControl.h"
#include"PictureEx.h"


// CGameFree 对话框

class CGameFree : public CDialogEx
{
	DECLARE_DYNAMIC(CGameFree)

public:
	CGameFree(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameFree();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	CDC m_dcMen;            //内存DC
	CDC m_dcBG;
	CDC m_dcCache;          //暂停时内存DC
	CDC m_dcElement;        //元素内存DC
	CDC m_dcMark;           //掩码内存DC
	CDC m_dcWin;            //胜利时内存DC
	CDC m_dcLose;           //失败时内存DC
	
	CPoint m_ptGame_Top;          //起始点坐标
	CSize m_sizeElem;
	bool m_bFirstPoint;           //标识第一个点
	CRect m_rtGameRect;
	CGameControl m_gameControl;
	bool m_bPlaying;             //是否在玩游戏
	bool m_bPause;	             //是否暂停 false 进行游戏中
	

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	void InitBackgroubd();
	void InitElement();
	void Initpause();
	void InitResult();
	void UpdateWindow();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex *asvPath, int nVexnum);
	void JudgeWin();
	void InitGIF();
public:
	afx_msg void OnClickedXiuHelp();
	afx_msg void OnClickedXiuPause();
	afx_msg void OnClickedXiuReset();
	afx_msg void OnClickedXiuSet();
	afx_msg void OnClickedXiuStart();
	afx_msg void OnClickedXiuTool();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPictureEx m_GIFctrl;               //动图的内存DC
	afx_msg void OnStnClickedTool();
};
