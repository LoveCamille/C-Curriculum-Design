#pragma once
#include <afxext.h>
#include "resource.h" 

class CWndchange : public CFormView
{
	DECLARE_DYNCREATE(CWndchange)
protected:
	CWndchange();
public:
	virtual ~CWndchange();

	enum { IDD = IDD_DIALOG4 };

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_classcode;
	CString m_classname;
	int m_vegcode;
	CString m_vegname;
	CString m_nutrient;
	int m_plantcode;
	int howbig;
	float m_weight;
	int m_when;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
