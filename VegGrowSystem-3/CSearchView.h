#pragma once
#include <afxext.h>
#include "resource.h" 

class CSearchView : public CFormView
{
	DECLARE_DYNCREATE(CSearchView)

protected:
	CSearchView();
public:
	virtual ~CSearchView();

	enum { IDD = IDD_DIALOG3 };//CSearchViewÄ£Ì¬´°¿ÚµÄID

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_sedit_input;
	void ChangeSize(CWnd* ,double ,double);
	void   CSearchView::GetCellName(int nRow, int nCol, CString &strName);
	CRect m_rect;
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CFont m_Font;
	afx_msg void OnBnClickedButton1();
	bool m_binitial;
	CListCtrl m_BgListCtr;
	afx_msg void OnBnClickedButton2();
};


