#include "stdafx.h"
#include "CSplitter.h"


CSplitter::CSplitter()
{
	m_cxSplitter = 1;
	m_cySplitter = 1;
	m_cxSplitterGap = 1;
	m_cySplitterGap = 1;
	m_cxBorder = 1;
	m_cyBorder = 1;
}


CSplitter::~CSplitter()
{
}
BEGIN_MESSAGE_MAP(CSplitter, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CSplitterWnd::OnLButtonDown(nFlags, point);
}


void CSplitter::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CSplitterWnd::OnMouseMove(nFlags, point);
}
