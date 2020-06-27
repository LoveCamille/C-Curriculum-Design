#pragma once
#include <afxext.h>
#include "resource.h" 
#include "CTChart.h"
#include "tchart1.h"
class CDisplayWnd2 : public CFormView
{
	DECLARE_DYNCREATE(CDisplayWnd2)

protected:
	CDisplayWnd2();
public:
	virtual ~CDisplayWnd2();

	enum { IDD = IDD_DIALOG2 };

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString m_combox;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnCbnSelendokCombo1();
	int m_idate1;
	int m_idate2;
	CString m_combox2;
	afx_msg void OnCbnSelchangeCombo1();

	afx_msg void OnBnClickedButton2();
	bool m_binitial;

	CTchart1 m_chart1;
};
