
#include "stdafx.h"
#include"CDisplayWnd2.h"
#include "SingDoc_basedDoc.h"
#include "resource.h"
#include "tchart1.h"
//---------------------
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CSeries.h"
//#include "CTChart.h"
//以上均用于绘制excel表格以及创建excel


IMPLEMENT_DYNCREATE(CDisplayWnd2, CFormView)

CDisplayWnd2::CDisplayWnd2() : CFormView(IDD_DIALOG2)
, m_combox(_T(""))
, m_idate1(2015)
, m_idate2(2015)
, m_combox2(_T(""))
{
	m_binitial = false;
}

CDisplayWnd2::~CDisplayWnd2()
{
}

BEGIN_MESSAGE_MAP(CDisplayWnd2, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CDisplayWnd2::OnBnClickedButton1)
//	ON_CBN_SELENDOK(IDC_COMBO1, &CDisplayWnd2::OnCbnSelendokCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDisplayWnd2::OnCbnSelchangeCombo1)

	ON_BN_CLICKED(IDC_BUTTON2, &CDisplayWnd2::OnBnClickedButton2)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CDisplayWnd2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDisplayWnd2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CDisplayWnd2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, sdf);
	DDX_CBString(pDX, IDC_COMBO1, m_combox);
	//  DDX_Control(pDX, IDC_COMBO1, m_ctl_combox);
	DDX_Text(pDX, IDC_EDIT1, m_idate1);
	DDV_MinMaxInt(pDX, m_idate1, 2015, 2020);
	DDX_Text(pDX, IDC_EDIT2, m_idate2);
	DDV_MinMaxInt(pDX, m_idate2, 2015, 2020);
	DDX_CBString(pDX, IDC_COMBO2, m_combox2);
	DDX_Control(pDX, IDC_TCHART1, m_chart1);
}

int CDisplayWnd2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  在此添加您专用的创建代码
	

	return 0;
}


void CDisplayWnd2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	
}


void CDisplayWnd2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(TEXT("按年份信息"));
	if (m_binitial == false)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(TEXT("按面积信息"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(TEXT("按重量信息"));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(TEXT("对种类计算"));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(TEXT("对蔬菜计算"));
		m_binitial = true;
	}
}


void CDisplayWnd2::OnBnClickedButton1()//绘制柱状图
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_combox == TEXT(""))
	{
		MessageBox(TEXT("请选择你想要的统计原则"), TEXT("warning"));
		return;
	}
	if (m_combox2 == TEXT(""))
	{
		MessageBox(TEXT("请选择你想要的统计对象"), TEXT("warning"));
		return;
	}
	if (((CSingDocbasedDoc*)GetDocument())->m_obarray.GetSize() == 0)
	{
		MessageBox(TEXT("没有任何内容"), TEXT("warning"));
		return;
	}
	int ncount = ((CSingDocbasedDoc*)GetDocument())->m_obarray.GetSize();
	for (long i = 0; i < m_chart1.get_SeriesCount(); i++)
	{
		((CSeries)m_chart1.Series(i)).Clear();
	}
	
	if (m_combox == TEXT("按面积信息"))
	{
		if (m_combox2 == TEXT("对种类计算"))
		{
			CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
			CString classname = ((Cfull_record*)pobarray->GetAt(0))->classname;
			int howbig = 0;
			vector<int> list;
			vector<CString> name;
			for (int i = 0; i < ncount; i++)
			{

				if (((Cfull_record*)pobarray->GetAt(i))->classname == classname &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
					howbig += ((Cfull_record*)pobarray->GetAt(i))->howbig;
				else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
					if (howbig != 0)
					{
						list.push_back(howbig);
						name.push_back(classname);
					}
					classname = ((Cfull_record*)pobarray->GetAt(i))->classname;
					howbig = ((Cfull_record*)pobarray->GetAt(i))->howbig;
				}

			}
			list.push_back(howbig);
			name.push_back(classname);
			int* array_int = new int[list.size()];
			CString* array_str = new CString[list.size()];
	

			int index = 0;
			for (long i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list.size(); j++)
				{
					if (list.at(index) < list.at(j))index = j;
				}
				if (list.at(index) > 0)
				{
					array_int[i] = list.at(index);
					array_str[i] = name.at(index);
				}
				list.at(index) = -1;
				index = 0;
			}
			for (long i = 0; i < m_chart1.get_SeriesCount(); i++)
			{
				((CSeries)m_chart1.Series(i)).Clear();
			}
			CSeries barSeries = (CSeries)m_chart1.Series(0);
			barSeries.Clear();
			for (int i = 0; i < list.size(); i++)
			{
				barSeries.AddXY((double)i, array_int[i], array_str[i], 0);
			}
			
			
			
			


		}

		else
		{
			CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
			CString vegname = ((Cfull_record*)pobarray->GetAt(0))->vegname;
			int howbig = 0;
			vector<int> list;
			vector<CString> name;
			for (int i = 0; i < ncount; i++)
			{

				if (((Cfull_record*)pobarray->GetAt(i))->vegname ==vegname &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
					howbig += ((Cfull_record*)pobarray->GetAt(i))->howbig;
				else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
					if (howbig != 0)
					{
						list.push_back(howbig);
						name.push_back(vegname);
					}
					vegname = ((Cfull_record*)pobarray->GetAt(i))->vegname;
					howbig = ((Cfull_record*)pobarray->GetAt(i))->howbig;
				}
			}
			list.push_back(howbig);
			name.push_back(vegname);
			int* array_int = new int[list.size()];
			CString* array_str = new CString[list.size()];
			int index = 0;
			for (long i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list.size(); j++)
				{
					if (list.at(index) < list.at(j))index = j;
				}
				if (list.at(index) > 0)
				{
					array_int[i] = list.at(index);
					array_str[i] = name.at(index);
				}
				list.at(index) = -1;
				index = 0;
			}
			for (long i = 0; i < m_chart1.get_SeriesCount(); i++)
			{
				((CSeries)m_chart1.Series(i)).Clear();
			}
			CSeries barSeries = (CSeries)m_chart1.Series(0);
			barSeries.Clear();
			for (int i = 0; i < list.size(); i++)
			{
				barSeries.AddXY((double)i, array_int[i], array_str[i], 0);
			}
		}
	}

	//————————————————————————————————————
	else if (m_combox == TEXT("按重量信息"))
	{
		if (m_combox2 == TEXT("对种类计算"))
		{
		
			CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
			CString classname = ((Cfull_record*)pobarray->GetAt(0))->classname;
			float weight = 0;
			vector<float> list;
			vector<CString> name;
			for (int i = 0; i < ncount; i++)
			{

				if (((Cfull_record*)pobarray->GetAt(i))->classname == classname &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
					weight += ((Cfull_record*)pobarray->GetAt(i))->weight;
				else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
					if ((int)weight != 0)
					{
						list.push_back(weight);
						name.push_back(classname);
					}

					classname = ((Cfull_record*)pobarray->GetAt(i))->classname;
					weight = ((Cfull_record*)pobarray->GetAt(i))->weight;
				}
			}
			list.push_back(weight);
			name.push_back(classname);
			double* array_int = new double[list.size()];
			CString* array_str = new CString[list.size()];
			int index = 0;
			for (long i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list.size(); j++)
				{
					if (list.at(index) < list.at(j))index = j;
				}
				if (list.at(index) > 0)
				{
					array_int[i] = list.at(index);
					array_str[i] = name.at(index);
				}
				list.at(index) = -1;
				index = 0;
			}
			for (long i = 0; i < m_chart1.get_SeriesCount(); i++)
			{
				((CSeries)m_chart1.Series(i)).Clear();
			}
			CSeries barSeries = (CSeries)m_chart1.Series(0);
			barSeries.Clear();
			for (int i = 0; i < list.size(); i++)
			{
				barSeries.AddXY((double)i, array_int[i], array_str[i], 0);
			}

			//----------------------------------------------------
		}
		else//对蔬菜计算
		{
			CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
			CString vegname = ((Cfull_record*)pobarray->GetAt(0))->vegname;
			float weight = 0;
			vector<float> list;
			vector<CString> name;
			for (int i = 0; i < ncount; i++)
			{

				if (((Cfull_record*)pobarray->GetAt(i))->vegname == vegname &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
					weight += ((Cfull_record*)pobarray->GetAt(i))->weight;
				else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
					_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
					if ((int)weight != 0)
					{
						list.push_back(weight);
						name.push_back(vegname);
					}

					vegname = ((Cfull_record*)pobarray->GetAt(i))->classname;
					weight = ((Cfull_record*)pobarray->GetAt(i))->weight;
				}
			}
			list.push_back(weight);
			name.push_back(vegname);
			double* array_int = new double[list.size()];
			CString* array_str = new CString[list.size()];
			int index = 0;
			for (long i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list.size(); j++)
				{
					if (list.at(index) < list.at(j))index = j;
				}
				if (list.at(index) > 0)
				{
					array_int[i] = list.at(index);
					array_str[i] = name.at(index);
				}
				list.at(index) = -1;
				index = 0;
			}
			for (long i = 0; i < m_chart1.get_SeriesCount(); i++)
			{
				((CSeries)m_chart1.Series(i)).Clear();
			}
			CSeries barSeries = (CSeries)m_chart1.Series(0);
			barSeries.Clear();
			for (int i = 0; i < list.size(); i++)
			{
				barSeries.AddXY((double)i, array_int[i], array_str[i], 0);
			}


		}
	}
	


	
}





void CDisplayWnd2::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	UpdateData();
	if (!m_combox.Compare( TEXT("按面积信息")) ||!m_combox.Compare( TEXT("按重量信息")))
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(false);
		GetDlgItem(IDC_EDIT2)->EnableWindow(false);
		
	}
	if (!m_combox.Compare( TEXT("按年份信息")))
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow();
		GetDlgItem(IDC_EDIT2)->EnableWindow();
	}
	Invalidate();
	UpdateWindow();
	*/
}






void CDisplayWnd2::OnBnClickedButton2()//导出到文件xls
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE, _T("(*.xls)"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("(*.xls)|*.xls||"), NULL);

	
	if (dlg.DoModal() == IDOK)
	{
		//获取路径
		UpdateData();
		if (m_combox == TEXT(""))
		{
			MessageBox(TEXT("请选择你想要的统计原则"), TEXT("warning"));
			return;
		}
		if (m_combox2 == TEXT(""))
		{
			MessageBox(TEXT("请选择你想要的统计对象"), TEXT("warning"));
			return;
		}
		if (((CSingDocbasedDoc*)GetDocument())->m_obarray.GetSize() == 0)
		{
			MessageBox(TEXT("没有任何内容"), TEXT("warning"));
			return;
		}
		CString strFileName = dlg.GetPathName();
		COleVariant
			covTrue((short)TRUE),
			covFalse((short)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		CApplication app;
		CWorkbook book;
		CWorkbooks books;
		CWorksheet sheet;
		CWorksheets sheets;
		CRange range;
		if (!app.CreateDispatch(_T("Excel.Application")))
		{
			MessageBox(_T("Error!"));
		}

		books = app.get_Workbooks();
		book = books.Add(covOptional);
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));//打开第一个工作页
		int ncount = ((CSingDocbasedDoc*)GetDocument())->m_obarray.GetSize();
		int lines = 2;
		CString str;
		str.Empty();

		if (m_combox == TEXT("按面积信息"))
		{
			if (m_combox2 == TEXT("对种类计算"))
			{

				//-----------------------------------
				CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
				range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
				range.put_Value2(COleVariant(TEXT("面积")));
				range = sheet.get_Range(COleVariant(_T("B1")), COleVariant(_T("B1")));
				range.put_Value2(COleVariant(TEXT("种类")));
				if (m_idate1 == m_idate2)
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
				}
				else
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("起始年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
					range = sheet.get_Range(COleVariant(_T("D1")), COleVariant(_T("D1")));
					range.put_Value2(COleVariant(TEXT("终止年份")));
					range = sheet.get_Range(COleVariant(_T("D2")), COleVariant(_T("D2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate2);
					range.put_Value2(COleVariant(str));
				}
				CString classname = ((Cfull_record*)pobarray->GetAt(0))->classname;
				int howbig = 0;
				for (int i = 0; i < ncount; i++)
				{
					if (((Cfull_record*)pobarray->GetAt(i))->classname == classname &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
						howbig += ((Cfull_record*)pobarray->GetAt(i))->howbig;
					else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
						if (howbig != 0)
						{
							str.Empty();
							str.Format(TEXT("A%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							str.Empty();
							str.Format(TEXT("%d"), howbig);
							range.put_Value2(COleVariant(str));
							str.Empty();
							str.Format(TEXT("B%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							range.put_Value2(COleVariant(classname));
							lines++;
						}
						classname = ((Cfull_record*)pobarray->GetAt(i))->classname;
						howbig = ((Cfull_record*)pobarray->GetAt(i))->howbig;
						
					}
				}//最后一次没有计入
				str.Empty();
				str.Format(TEXT("A%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				str.Empty();
				str.Format(TEXT("%d"), howbig);
				range.put_Value2(COleVariant(str));
				str.Empty();
				str.Format(TEXT("B%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				range.put_Value2(COleVariant(classname));
				//---------------------------------------
			}

			else
			{

				//----------------------------------------
				CObArray* pobarray = &(((CSingDocbasedDoc*)GetDocument())->m_obarray);
				range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
				range.put_Value2(COleVariant(TEXT("面积")));
				range = sheet.get_Range(COleVariant(_T("B1")), COleVariant(_T("B1")));
				range.put_Value2(COleVariant(TEXT("蔬菜")));
				if (m_idate1 == m_idate2)
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
				}
				else
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("起始年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
					range = sheet.get_Range(COleVariant(_T("D1")), COleVariant(_T("D1")));
					range.put_Value2(COleVariant(TEXT("终止年份")));
					range = sheet.get_Range(COleVariant(_T("D2")), COleVariant(_T("D2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate2);
					range.put_Value2(COleVariant(str));
				}
				CString vegname = ((Cfull_record*)(pobarray->GetAt(0)))->vegname;
				int howbig = 0;
				for (int i = 0; i < ncount; i++)
				{
					if (((Cfull_record*)pobarray->GetAt(i))->vegname == vegname &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
						howbig += ((Cfull_record*)pobarray->GetAt(i))->howbig;
					else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
						if (howbig != 0)
						{
							str.Empty();
							str.Format(TEXT("A%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							str.Empty();
							str.Format(TEXT("%d"), howbig);
							range.put_Value2(COleVariant(str));
							str.Empty();
							str.Format(TEXT("B%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							range.put_Value2(COleVariant(vegname));
							lines++;
						}
						vegname = ((Cfull_record*)pobarray->GetAt(i))->vegname;
						howbig = ((Cfull_record*)pobarray->GetAt(i))->howbig;
						
					}
				}
				str.Empty();
				str.Format(TEXT("A%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				str.Empty();
				str.Format(TEXT("%d"), howbig);
				range.put_Value2(COleVariant(str));
				str.Empty();
				str.Format(TEXT("B%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				range.put_Value2(COleVariant(vegname));


				//---------------------------------------
			}
		}

		//————————————————————————————————————
		else if (m_combox == TEXT("按重量信息"))
		{
			if (m_combox2 == TEXT("对种类计算"))
			{
				CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
				range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
				range.put_Value2(COleVariant(TEXT("重量")));
				range = sheet.get_Range(COleVariant(_T("B1")), COleVariant(_T("B1")));
				range.put_Value2(COleVariant(TEXT("种类")));
				if (m_idate1 == m_idate2)
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
				}
				else
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("起始年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
					range = sheet.get_Range(COleVariant(_T("D1")), COleVariant(_T("D1")));
					range.put_Value2(COleVariant(TEXT("终止年份")));
					range = sheet.get_Range(COleVariant(_T("D2")), COleVariant(_T("D2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate2);
					range.put_Value2(COleVariant(str));
				}
				CString classname = ((Cfull_record*)pobarray->GetAt(0))->classname;
				int weight = 0;
				for (int i = 0; i < ncount; i++)
				{
					if (((Cfull_record*)pobarray->GetAt(i))->classname == classname &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
						weight += ((Cfull_record*)pobarray->GetAt(i))->weight;
					else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
						if (weight != 0)
						{
							str.Empty();
							str.Format(TEXT("A%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							str.Empty();
							str.Format(TEXT("%d"), weight);
							range.put_Value2(COleVariant(str));
							str.Empty();
							str.Format(TEXT("B%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							range.put_Value2(COleVariant(classname));
							lines++;
						}
						classname = ((Cfull_record*)pobarray->GetAt(i))->classname;
						weight = ((Cfull_record*)pobarray->GetAt(i))->weight;
						
					}
				}//最后一次没有计入
				str.Empty();
				str.Format(TEXT("A%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				str.Empty();
				str.Format(TEXT("%d"), weight);
				range.put_Value2(COleVariant(str));
				str.Empty();
				str.Format(TEXT("B%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				range.put_Value2(COleVariant(classname));

				//----------------------------------------------------
			}
			else//对蔬菜计算
			{

				//-----------------------------------------------------
				CObArray* pobarray = &((CSingDocbasedDoc*)GetDocument())->m_obarray;
				range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
				range.put_Value2(COleVariant(TEXT("重量")));
				range = sheet.get_Range(COleVariant(_T("B1")), COleVariant(_T("B1")));
				range.put_Value2(COleVariant(TEXT("蔬菜")));
				if (m_idate1 == m_idate2)
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
				}
				else
				{
					range = sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C1")));
					range.put_Value2(COleVariant(TEXT("起始年份")));
					range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate1);
					range.put_Value2(COleVariant(str));
					range = sheet.get_Range(COleVariant(_T("D1")), COleVariant(_T("D1")));
					range.put_Value2(COleVariant(TEXT("终止年份")));
					range = sheet.get_Range(COleVariant(_T("D2")), COleVariant(_T("D2")));
					str.Empty();
					str.Format(TEXT("%d"), m_idate2);
					range.put_Value2(COleVariant(str));
				}
				CString vegname = ((Cfull_record*)pobarray->GetAt(0))->vegname;
				int weight = 0;
				for (int i = 0; i < ncount; i++)
				{
					if (((Cfull_record*)pobarray->GetAt(i))->vegname == vegname &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1)
						weight += ((Cfull_record*)pobarray->GetAt(i))->weight;
					else if (_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) <= m_idate2 &&
						_wtoi(((Cfull_record*)pobarray->GetAt(i))->when) >= m_idate1) {
						if (weight != 0)
						{
							str.Empty();
							str.Format(TEXT("A%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							str.Empty();
							str.Format(TEXT("%d"), weight);
							range.put_Value2(COleVariant(str));
							str.Empty();
							str.Format(TEXT("B%d"), lines);
							range = sheet.get_Range(COleVariant(str), COleVariant(str));
							range.put_Value2(COleVariant(vegname));
							lines++;
						}
						vegname = ((Cfull_record*)pobarray->GetAt(i))->vegname;
						weight = ((Cfull_record*)pobarray->GetAt(i))->weight;
						
					}
				}
				str.Empty();
				str.Format(TEXT("A%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				str.Empty();
				str.Format(TEXT("%d"), weight);
				range.put_Value2(COleVariant(str));
				str.Empty();
				str.Format(TEXT("B%d"), lines);
				range = sheet.get_Range(COleVariant(str), COleVariant(str));
				range.put_Value2(COleVariant(vegname));
				//--------------------------------------


			}
		}



		book.SaveCopyAs(COleVariant(strFileName));
		book.put_Saved(true);
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		app.Quit();
		app.ReleaseDispatch();
	}

		

}
