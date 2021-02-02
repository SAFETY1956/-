// CGameFree.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CGameFree.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <MMSystem.h> 
#pragma comment( lib,"winmm.lib" )

// CGameFree 对话框

IMPLEMENT_DYNAMIC(CGameFree, CDialogEx)

CGameFree::CGameFree(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
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

CGameFree::~CGameFree()
{
}

void CGameFree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOOL, m_GIFctrl);
}


BEGIN_MESSAGE_MAP(CGameFree, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_XIU_HELP, &CGameFree::OnClickedXiuHelp)
	ON_BN_CLICKED(IDC_XIU_PAUSE, &CGameFree::OnClickedXiuPause)
	ON_BN_CLICKED(IDC_XIU_RESET, &CGameFree::OnClickedXiuReset)
	ON_BN_CLICKED(IDC_XIU_SET, &CGameFree::OnClickedXiuSet)
	ON_BN_CLICKED(IDC_XIU_START, &CGameFree::OnClickedXiuStart)
	ON_BN_CLICKED(IDC_XIU_TOOL, &CGameFree::OnClickedXiuTool)
	ON_WM_LBUTTONUP()
	ON_STN_CLICKED(IDC_TOOL, &CGameFree::OnStnClickedTool)
END_MESSAGE_MAP()

void CGameFree::InitBackgroubd()
{
	HBITMAP bmp = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP7);
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
BOOL CGameFree::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackgroubd();
	InitElement();
	Initpause();
	InitResult();
	InitGIF();
	return TRUE;
}

void CGameFree::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 1000, 600, &m_dcMen, 0, 0, SRCCOPY);
}

void CGameFree::InitElement() {
	HBITMAP bmp = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP4);
	CClientDC dc(this);

	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(bmp);
	HBITMAP bmp1 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP5);

	m_dcMark.CreateCompatibleDC(&dc);

	m_dcMark.SelectObject(bmp1);
}

// CGameFree 消息处理程序


void CGameFree::OnClickedXiuHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameFree::OnClickedXiuPause()
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
		GetDlgItem(IDC_XIU_RESET)->EnableWindow(0);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_XIU_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}

	//如果游戏暂停
	if (m_bPause == true)
	{
		UpdateMap();
		//GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(1);
		GetDlgItem(IDC_XIU_RESET)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新

		this->GetDlgItem(IDC_XIU_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}

	m_bPause = !m_bPause;
}

void CGameFree::UpdateWindow() {
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

void CGameFree::UpdateMap() {
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
			m_dcMen.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);

		}
		Invalidate(FALSE);
	}
}

void CGameFree::OnClickedXiuReset()
{
	m_gameControl.Reset();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameFree::OnClickedXiuSet()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameFree::OnClickedXiuStart()
{
	m_bPlaying = true;
	m_bPause = false;
	if (m_bPause == true) return;  //暂停时不响应
	m_gameControl.StartGame();
	UpdateMap();
}

void CGameFree::Initpause() {
	CClientDC dc(this);
	HBITMAP bmp2 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP3);
	m_dcCache.CreateCompatibleDC(&dc);
	m_dcCache.SelectObject(bmp2);
}

void CGameFree::InitResult() {
	CClientDC dc(this);
	HBITMAP bmp3 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP6);
	m_dcWin.SelectObject(bmp3);
	HBITMAP bmp4 = LoadBitmap(AfxGetInstanceHandle(), (LPCWSTR)IDB_BITMAP2);
	m_dcLose.CreateCompatibleDC(&dc);
	m_dcLose.SelectObject(bmp4);
}

void CGameFree::OnClickedXiuTool()
{

	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAXVEXNUM];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.select(avPath, nVexnum))
	{

		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//画第一个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);
		
		
		m_GIFctrl.ShowWindow(SW_SHOW); //显示控件
		
		UpdateMap();	//更新地图
        

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
	}
}





void CGameFree::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (point.x < m_ptGame_Top.x || point.y < m_ptGame_Top.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGame_Top.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGame_Top.x) / m_sizeElem.cx;
	if (nRow > 9 || nCol > 15) {
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
		if (m_gameControl.Link(avPath, nVernum)) {
			DrawTipLine(avPath, nVernum);
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
	m_bFirstPoint = !m_bFirstPoint;

}

void CGameFree::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(223, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGame_Top.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGame_Top.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameFree::DrawTipLine(Vertex *asvPath, int nVexnum) {
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen *pOldPen = dc.SelectObject(&penLine);

	//绘制连接线

	dc.MoveTo(m_ptGame_Top.x + asvPath[0].col *m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGame_Top.y + asvPath[0].row *m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 0;i < nVexnum - 1;i++) {
		dc.LineTo(m_ptGame_Top.x + asvPath[i + 1].col *m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGame_Top.y + asvPath[i + 1].row *m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

// 获取执行文件所有的路径
CString GetAbsolutePath()
{
	CString strTemp;
	TCHAR *pBuf = strTemp.GetBuffer(MAX_PATH);

	::GetModuleFileName(NULL, pBuf, MAX_PATH);
	strTemp.ReleaseBuffer();
	strTemp = strTemp.Left(strTemp.ReverseFind(_T('\\'))) + _T('\\');

	return strTemp;
}
void CGameFree::InitGIF()
{

	CString strFile = GetAbsolutePath() + _T("tool.gif");
	if (m_GIFctrl.Load(strFile))
	{
		m_GIFctrl.Draw();
	}
	m_GIFctrl.ShowWindow(SW_HIDE);         //再隐藏控件
	UpdateWindow();
}


void CGameFree::OnStnClickedTool()
{
	
}
