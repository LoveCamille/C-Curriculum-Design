
// SingDoc_basedView.h: CSingDocbasedView 类的接口
//

#pragma once
#include "SingDoc_basedDoc.h"

class CSingDocbasedView : public CView
{
protected: // 仅从序列化创建
	CSingDocbasedView() noexcept;
	DECLARE_DYNCREATE(CSingDocbasedView)

// 特性
public:
	CSingDocbasedDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSingDocbasedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	CPropsheet m_sheet;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // SingDoc_basedView.cpp 中的调试版本
inline CSingDocbasedDoc* CSingDocbasedView::GetDocument() const
   { return reinterpret_cast<CSingDocbasedDoc*>(m_pDocument); }
#endif

