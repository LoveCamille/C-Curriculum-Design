// CDisplayView.cpp: 实现文件
//

#include "stdafx.h"
#include "CDisplayView.h"
#include "CDisplayWnd2.h"
#include "CSearchView.h"
#include "CWndChange.h"
#include "MainFrm.h"

// CDisplayView
IMPLEMENT_DYNCREATE(CDisplayView, CFormView)
//IDD_DISPLAYVIEW模态框的ID
CDisplayView::CDisplayView() : CFormView(IDD_DIALOG1) {

}

CDisplayView::~CDisplayView()
{
}

BEGIN_MESSAGE_MAP(CDisplayView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDisplayView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDisplayView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDisplayView::OnBnClickedButton2)
	ON_WM_SIZE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CDisplayView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDisplayView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CDisplayView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, sdf);
}


void CDisplayView::OnBnClickedButton1()//搜索界面
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	((CMainFrame*)AfxGetMainWnd())->GetClientRect(&rect);
	CRuntimeClass *pViewClass = RUNTIME_CLASS(CSearchView);
	((CMainFrame*)AfxGetMainWnd())->ReplaceView(0, 1, pViewClass, CSize(rect.Width() - 350, rect.Height()));
	((CFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1))->SendMessage(WM_INITIALUPDATE);
}


void CDisplayView::OnBnClickedButton3()//Listview的控制界面
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	((CMainFrame*)AfxGetMainWnd())->GetClientRect(&rect);
	CRuntimeClass *pViewClass = RUNTIME_CLASS(CWndchange);
	((CMainFrame*)AfxGetMainWnd())->ReplaceView(0, 1, pViewClass, CSize(rect.Width() - 350, rect.Height()));
	((CFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1))->SendMessage(WM_INITIALUPDATE);
}


void CDisplayView::OnBnClickedButton2()//excel图表显示
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	((CMainFrame*)AfxGetMainWnd())->GetClientRect(&rect);
	CRuntimeClass *pViewClass = RUNTIME_CLASS(CDisplayWnd2);
	((CMainFrame*)AfxGetMainWnd())->ReplaceView(0, 1, pViewClass, CSize(rect.Width() - 350, rect.Height()));
	((CFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1))->SendMessage(WM_INITIALUPDATE);
}

void CDisplayView::ChangeSize(CWnd* pWnd, double cx, double cy)
{
	// TODO: 在此处添加实现代码.
	if (pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建	
	{
		CRect rect;   //获取控件变化前的大小  
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标

		//    cx/m_rect.Width()为对话框在横向的变化比例
		rect.left = rect.left*cx / m_rect.Width();//调整控件大小
		rect.right = rect.right*cx / m_rect.Width();
		rect.top = rect.top*cy / m_rect.Height();
		rect.bottom = rect.bottom*cy / m_rect.Height();
		pWnd->MoveWindow(rect);//设置控件大小
	}
}


void CDisplayView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if (nType == 1)return;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_BUTTON1);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_BUTTON2);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_BUTTON3);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_rect);
	// TODO: 在此处添加消息处理程序代码
}


void CDisplayView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetClientRect(&m_rect);
	// TODO: 在此添加专用代码和/或调用基类
}
