#pragma once
#include <afxext.h>
class CSplitter :
	public CSplitterWnd
{
public:
	CSplitter();
	virtual ~CSplitter();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

