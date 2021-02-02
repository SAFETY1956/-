// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGame_Top.x = 50;
	m_ptGame_Top.y = 50;

	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGame_Top.y;
	m_rtGameRect.left = m_ptGame_Top.x;
	m_rtGameRect.right = m_rtGameRect.left + 16 * m_sizeElem.cx;
	m_rtGameRect.bottom = m_rtGameRect.top + 10 * m_sizeElem.cy;

	m_bFirstPoint = true;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnBnClickedButtonPause)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CGameDlg::OnClickedButtonRestart)
	ON_WM_TIMER()

	ON_EN_CHANGE(IDC_TIME_EDIT, &CGameDlg::OnChangeTimeEdit)
	ON_BN_CLICKED(IDC_BUTTON_TIP, &CGameDlg::OnClickedButtonTip)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackgroubd()
{
	HBITMAP bmp = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP1);
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);

	//初始化内存DC
	m_dcMen.CreateCompatibleDC(&dc);
	CBitmap bmpMen;
	bmpMen.CreateCompatibleBitmap(&dc, 1000, 600);
	m_dcMen.SelectObject(&bmpMen);

	//绘制背景到内存DC
	m_dcMen.BitBlt(0, 0, 1000, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackgroubd();
	InitElement();
	Initpause();
	InitResult();
	//设置进度条隐藏
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_TIME_EDIT)->ShowWindow(FALSE);
	return TRUE;  
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 1000, 600, &m_dcMen, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement() {
	HBITMAP bmp = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP4);
	CClientDC dc(this);

	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(bmp);
	HBITMAP bmp1 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP5);

	m_dcMark.CreateCompatibleDC(&dc);

	m_dcMark.SelectObject(bmp1);
}
void CGameDlg::InitWeiTu(){
}

void CGameDlg::OnBnClickedButtonStart()
{
	m_bPlaying = true;
	m_bPause = false;
	if (m_bPause == true) return;  //暂停时不响应
	//初始时间是300
	timeCount = 300;
	m_gameControl.StartGame();	
	//初始化进度条
	m_GameProgress = (CProgressCtrl*)GetDlgItem(IDC_GAME_TIME);
	m_GameProgress->SetRange(0, 60 * 5);    //初始范围
	m_GameProgress->SetStep(-1);            //初始步数值
	m_GameProgress->SetPos(60 * 5);         //设置初始值
	
	this->SetTimer(1, 1000, NULL);  //启动定时器
	UpdateMap();

	//设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_TIME_EDIT)->ShowWindow(TRUE);

}
void CGameDlg::Initpause() {
	CClientDC dc(this);
	HBITMAP bmp2 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP3);
	m_dcCache.CreateCompatibleDC(&dc);
	m_dcCache.SelectObject(bmp2);
}

void CGameDlg::InitResult() {
	CClientDC dc(this);
	HBITMAP bmp3 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP6);
	m_dcWin.SelectObject(bmp3);
	HBITMAP bmp4 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP2);
	m_dcLose.CreateCompatibleDC(&dc);
	m_dcLose.SelectObject(bmp4);
}


void CGameDlg::OnBnClickedButtonPause()
{
	//获得当前对话框的视频内容
	CClientDC dc(this);

	//游戏没在进行时，直接返回
	if (m_bPlaying == false)
		return;

	//如果游戏没有暂停
	if (m_bPause == false)
	{
		
		//绘制背景到内存DC中
		m_dcMen.BitBlt(MAP_LETF, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);

		// GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(0);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}

	//如果游戏暂停
	if (m_bPause == true)
	{
		UpdateMap();
		//GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新

		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}

	m_bPause = !m_bPause;
}

void CGameDlg::UpdateWindow() {
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, 1000 + nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}

void CGameDlg::UpdateMap() {
	int nLeft = m_ptGame_Top.x;
	int nTop = m_ptGame_Top.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMen.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 16;j++) {
			int nInfo = m_gameControl.GetElement(i, j);
			//m_dcMen.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW,nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMen.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMark, 0, nInfo * nElemH, SRCPAINT);
			m_dcMen.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0,nInfo * nElemH, SRCAND);

		}
		Invalidate(FALSE);
	}
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (point.x < m_ptGame_Top.x || point.y < m_ptGame_Top.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGame_Top.y) / m_sizeElem.cy;
	int nCol= (point.x - m_ptGame_Top.x) / m_sizeElem.cx;
	if (nRow > 9|| nCol > 15) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		//判断是否是相同图片	
		Vertex avPath[MAXVEXNUM];
		int nVernum = 0;
		if (m_gameControl.Link(avPath,nVernum)) {			
			DrawTipLine(avPath,nVernum);
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
	m_bFirstPoint=!m_bFirstPoint;
	JudgeWin();	
}

void CGameDlg::DrawTipFrame(int nRow,int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(223, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGame_Top.x + nCol*m_sizeElem.cx;
	rtTipFrame.top = m_ptGame_Top.y + nRow *m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


void CGameDlg::DrawTipLine(Vertex *asvPath,int nVexnum) {
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
    //将画笔选入DC
	CPen *pOldPen = dc.SelectObject(&penLine);

	//绘制连接线

	dc.MoveTo(m_ptGame_Top.x +asvPath[0].col *m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGame_Top.y + asvPath[0].row *m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 0;i < nVexnum-1;i++) {
		dc.LineTo(m_ptGame_Top.x + asvPath[i+1].col *m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGame_Top.y + asvPath[i+1].row *m_sizeElem.cy + m_sizeElem.cy / 2);		
	}
	dc.SelectObject(pOldPen);
}


void CGameDlg::OnClickedButtonRestart()
{
	m_gameControl.Reset();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	JudgeWin();
	//设置进度条的位置之前，需要判断计时器的编号是否是当前的计时器
	if (nIDEvent ==1 && m_bPlaying && m_bPause == false)
	{
		//游戏时间减一秒
		if (timeCount > -1)
		{
			CString str;
			str.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_TIME_EDIT, str);

			UpdateData(false);
			timeCount--;

			m_GameProgress->StepIt();
		}

	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::JudgeWin() {
	//游戏胜负判断
	int bGameStatus = m_gameControl.IsWin(m_GameProgress->GetPos());
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;

		//关闭定时器
		KillTimer(1);

		//提示获胜
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			m_dcMen.BitBlt(0, 0, 786, 600, &m_dcWin, 0, 0, SRCCOPY);
			Sleep(200);
			MessageBox(_T("赢啦(´▽｀)ノ♪"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			m_dcMen.BitBlt(0, 0, 786, 600, &m_dcLose, 0, 0, SRCCOPY);
			Sleep(200);
			MessageBox(_T("很遗憾，时间到了(╥﹏╥)"), strTitle);
		}
		//还原开始游戏按钮，使用按钮可以点击
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	}
}







void CGameDlg::OnChangeTimeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void CGameDlg::OnClickedButtonTip()
{
	//如果没有进行游戏，则返回
	if (m_bPlaying == false)
		return;

	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAXVEXNUM];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//画第一个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		//画提示线
		DrawTipLine(avPath, nVexnum);

		Sleep(1000);    //延迟

		UpdateMap();	//更新地图

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
	}
}
