// CSearchView.cpp: 实现文件
//

#include "stdafx.h"
#include "CSearchView.h"
#include "SingDoc_basedDoc.h"
#include "link_chain.h"
#include "MainFrm.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"

IMPLEMENT_DYNCREATE(CSearchView, CFormView)
//CSearchView模态框的ID
CSearchView::CSearchView() : CFormView(IDD_DIALOG3), m_sedit_input(_T(""))
{
	m_binitial = false;
}

CSearchView::~CSearchView()
{
}

BEGIN_MESSAGE_MAP(CSearchView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSearchView::OnBnClickedButton2)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CSearchView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSearchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CSearchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, sdf);
	//DDX_Control(pDX, IDC_EDIT2, m_edit_output);
	DDX_Text(pDX, IDC_EDIT1, m_sedit_input);
	DDX_Control(pDX, IDC_LIST1, m_BgListCtr);
}


// CSearchView 消息处理程序




void CSearchView::ChangeSize(CWnd* pWnd,double cx ,double cy)
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


void CSearchView::OnInitialUpdate()//初始化视图和控件
{
	CFormView::OnInitialUpdate();
	GetClientRect(&m_rect);
	if (m_binitial == false)
	{
		m_Font.CreateFont(50, 15, 0, 0, 100,
			FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, TEXT("Arial"));
		CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
		m_Edit->SetFont(&m_Font, FALSE);
		GetDlgItem(IDC_EDIT1)->SetFont(&m_Font);

		DWORD dwStyle = m_BgListCtr.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT; 
		dwStyle |= LVS_EX_GRIDLINES;
		m_BgListCtr.SetExtendedStyle(dwStyle); 
		dwStyle |= LVS_EX_FULLROWSELECT; 
		m_BgListCtr.InsertColumn(0, _T("顺序"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(1, _T("分类码"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(2, _T("分类名"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(3, _T("蔬菜号"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(4, _T("蔬菜名"), LVCFMT_LEFT, 100);
		m_BgListCtr.InsertColumn(5, _T("营养成分"), LVCFMT_CENTER, 320);
		m_BgListCtr.InsertColumn(6, _T("种植号"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(7, _T("面积"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(8, _T("重量"), LVCFMT_LEFT, 80);
		m_BgListCtr.InsertColumn(9, _T("年份"), LVCFMT_LEFT, 80);

		m_binitial = true;
	}
	// TODO: 在此添加专用代码和/或调用基类
}


void CSearchView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//用于控制控件大小随窗口变化
	
	if (nType == 1)return;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_EDIT1);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_LIST1);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_BUTTON1);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_BUTTON2);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_rect);
	
	
}


void CSearchView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//模糊搜索，并显示到editbox中
	UpdateData();
	CObArray* pObArray=&((CSingDocbasedDoc*)GetDocument())->m_obarray;
	int ncount = pObArray->GetSize();
	int* Array = new int[ncount];
	for (int i = 0; i < ncount; i++)
	{
		Array[i]=vague_match(((Cfull_record*)pObArray->GetAt(i)), m_sedit_input);
	}
	CObArray temp;
	int index=0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < ncount; j++)
		{
			int test = Array[index];
			test = Array[j];
			if (Array[index] < Array[j])index = j;
		}
		if (Array[index] >= 0)temp.Add(pObArray->GetAt(index));
		Array[index] = -1;
		index = 0;
	}
	if (temp.GetSize() == 0)
	{
		MessageBox(TEXT("没有匹配到任何结果"), TEXT("warning"));
		return;
	}
	m_BgListCtr.DeleteAllItems();
	CString output;
	Cfull_record* ptr;
	for (int i = 0; i < temp.GetSize(); i++)
	{
		output.Empty();
		output.Format(TEXT("%d"), i);
		m_BgListCtr.InsertItem(i, output);
		ptr = (Cfull_record*)temp.GetAt(i);
		output.Empty();
		output.Format(TEXT("%c"), ptr->classcode);
		m_BgListCtr.SetItemText(i, 1, output);
		m_BgListCtr.SetItemText(i, 2, ptr->classname);
		output.Empty();
		output.Format(TEXT("%d"), ptr->vegcode);
		m_BgListCtr.SetItemText(i, 3, output);
		m_BgListCtr.SetItemText(i, 4, ptr->vegname);
		m_BgListCtr.SetItemText(i, 5, ptr->nutrient);
		output.Empty();
		output.Format(TEXT("%d"), ptr->plantcode);
		m_BgListCtr.SetItemText(i, 6, output);
		output.Empty();
		output.Format(TEXT("%d"), ptr->howbig);
		m_BgListCtr.SetItemText(i, 7, output);
		output.Empty();
		output.Format(TEXT("%f"), ptr->weight);
		m_BgListCtr.SetItemText(i, 8, output);
		m_BgListCtr.SetItemText(i, 9, ptr->when);
	}
	m_BgListCtr.Invalidate();

	
}

void   CSearchView::GetCellName(int nRow, int nCol, CString &strName)
{
	
	int nSeed = nCol;
	CString strRow;
	char cCell = 'A' + nCol - 1;

	strName.Format(_T("%c"), cCell);

	strRow.Format(_T("%d "), nRow);
	strName += strRow;
}

void CSearchView::OnBnClickedButton2()//导出查找结果到xls文件
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog FileDialog(FALSE, L"xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Microsoft Excel 2000(*.xls)|*.xls|所有文件(*.*)"), this);
	if (FileDialog.DoModal() != IDOK)
		return;
	CString cStrFile = FileDialog.GetPathName(); //选择保存路径名称

	COleVariant
		covTrue((short)TRUE),
		covFalse((short)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CApplication   app;
	CWorkbooks   books;
	CWorkbook   book;
	CWorksheets   sheets;
	CWorksheet   sheet;
	CRange   range;
	

	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		MessageBox(_T("创建失败！"));
		return;
	}

	//Get   a   new   workbook.
	books = app.get_Workbooks();
	book = books.Add(covOptional);

	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));

	////////////////////////////////////CListCtrl控件report风格//////////////////////////////////////////////////////////
	CHeaderCtrl   *pmyHeaderCtrl;
	pmyHeaderCtrl = m_BgListCtr.GetHeaderCtrl();//此句取得CListCtrl控件的列表頭

	int   iRow, iCol;
	int   m_cols = pmyHeaderCtrl->GetItemCount();
	int   m_rows = m_BgListCtr.GetItemCount();
	HDITEM   hdi;
	TCHAR     lpBuffer[256];
	bool       fFound = false;

	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	CString   colname;
	CString strTemp;
	for (iCol = 0; iCol < m_cols; iCol++)//将列表的标题头写入EXCEL
	{
		GetCellName(1, iCol + 1, colname);
		range = sheet.get_Range(COleVariant(colname), COleVariant(colname));
		pmyHeaderCtrl->GetItem(iCol, &hdi);
		range.put_Value2(COleVariant(hdi.pszText));
		int   nWidth = m_BgListCtr.GetColumnWidth(iCol) / 6;
		//得到第iCol+1列  
		range.AttachDispatch(range.get_Item(_variant_t((long)(iCol + 1)), vtMissing).pdispVal, true);
		//设置列宽 
		range.put_ColumnWidth(_variant_t((long)nWidth));
	}
	range = sheet.get_Range(COleVariant(_T("A1 ")), COleVariant(colname));
	range.put_RowHeight(_variant_t((long)50));//设置行的高度
	range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108

	COleSafeArray   saRet;
	DWORD   numElements[] = { m_rows,m_cols };       //5x2   element   array
	saRet.Create(VT_BSTR, 2, numElements);
	range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional);
	range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols));
	long   index[2];
	range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional);
	range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols));
	for (iRow = 1; iRow <= m_rows; iRow++)//将列表内容写入EXCEL
	{
		for (iCol = 1; iCol <= m_cols; iCol++)
		{
			index[0] = iRow - 1;
			index[1] = iCol - 1;
			CString   szTemp;
			szTemp = m_BgListCtr.GetItemText(iRow - 1, iCol - 1);
			BSTR   bstr = szTemp.AllocSysString();
			saRet.PutElement(index, bstr);
			SysFreeString(bstr);
		}
	}

	range.put_Value2(COleVariant(saRet));
	saRet.Detach();
	book.SaveCopyAs(COleVariant(cStrFile));
	//       cellinterior.ReleaseDispatch();
	book.put_Saved(true);
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();
	
}
