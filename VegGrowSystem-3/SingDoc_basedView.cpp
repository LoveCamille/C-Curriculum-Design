
// SingDoc_basedView.cpp: CSingDocbasedView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SingDoc_based.h"
#endif

#include "SingDoc_basedDoc.h"
#include "SingDoc_basedView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingDocbasedView

IMPLEMENT_DYNCREATE(CSingDocbasedView, CView)

BEGIN_MESSAGE_MAP(CSingDocbasedView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSingDocbasedView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSingDocbasedView 构造/析构

CSingDocbasedView::CSingDocbasedView() noexcept
	
{
	// TODO: 在此处添加构造代码
	

}

CSingDocbasedView::~CSingDocbasedView()
{
}

BOOL CSingDocbasedView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSingDocbasedView 绘图

void CSingDocbasedView::OnDraw(CDC* /*pDC*/)
{
	CSingDocbasedDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSingDocbasedView 打印


void CSingDocbasedView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSingDocbasedView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSingDocbasedView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSingDocbasedView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSingDocbasedView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSingDocbasedView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSingDocbasedView 诊断

#ifdef _DEBUG
void CSingDocbasedView::AssertValid() const
{
	CView::AssertValid();
}

void CSingDocbasedView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingDocbasedDoc* CSingDocbasedView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingDocbasedDoc)));
	return (CSingDocbasedDoc*)m_pDocument;
}
#endif //_DEBUG


// CSingDocbasedView 消息处理程序


//int CSingDocbasedView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CView::OnCreate(lpCreateStruct) == -1)
//		return -1;
//	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
//	m_sheet.SetWindowPos(NULL, 20, 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}
