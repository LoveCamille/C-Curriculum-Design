#pragma once
#include <afxext.h>
#include "resource.h" 

class CDisplayView : public CFormView
{
	DECLARE_DYNCREATE(CDisplayView)

protected:
	CDisplayView();
public:
	virtual ~CDisplayView();

	enum { IDD = IDD_DIALOG1 };//IDD_DISPLAYVIEWÄ£Ì¬´°¿ÚµÄID

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	void CDisplayView::ChangeSize(CWnd* pWnd, double cx, double cy);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	CRect m_rect;
};
