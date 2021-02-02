#pragma once

#include"global.h"
#include"CGameControl.h"
// CGameDlg 对话框


class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

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
	int timeCount;               //计时
	void InitWeiTu();                 
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CProgressCtrl *m_GameProgress;             //进度条
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

public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonRestart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeTimeEdit();
	afx_msg void OnClickedButtonTip();
};
