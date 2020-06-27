
// SingDoc_basedDoc.cpp: CSingDocbasedDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SingDoc_based.h"
#endif

#include "SingDoc_basedDoc.h"
#include "link_chain.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include <afxdisp.h>
#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CSingDocbasedDoc

IMPLEMENT_DYNCREATE(CSingDocbasedDoc, CDocument)

BEGIN_MESSAGE_MAP(CSingDocbasedDoc, CDocument)
	ON_COMMAND(ID_XLS32773, &CSingDocbasedDoc::OnXls32773)
	//ON_COMMAND(ID_XLS32774, &CSingDocbasedDoc::OnXls32774)
END_MESSAGE_MAP()


// CSingDocbasedDoc 构造/析构

CSingDocbasedDoc::CSingDocbasedDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	header = NULL;

}

CSingDocbasedDoc::~CSingDocbasedDoc()
{
}

BOOL CSingDocbasedDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSingDocbasedDoc 序列化

void CSingDocbasedDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		
	}
	else
	{
		// TODO: 在此添加加载代码
		int ncount = m_obarray.GetSize();
		for (int i = 0; i < ncount; i++)
			delete m_obarray.GetAt(i);
		m_obarray.RemoveAll();
	}
	m_obarray.Serialize(ar);
	if (!ar.IsStoring())
	{
		int ncount = m_obarray.GetSize();
		for (int i = 0; i < ncount; i++)
		{
			TYPE::DataInterface(header, ((Cfull_record*)m_obarray.GetAt(i))->classcode, (LPTSTR)(LPCTSTR)((Cfull_record*)m_obarray.GetAt(i))->classname , 0, (LPTSTR)(LPCTSTR)((Cfull_record*)m_obarray.GetAt(i))->vegname);
			if (((Cfull_record*)m_obarray.GetAt(i))->vegcode != 0)
			{
				TYPE::DataInterface(header, ((Cfull_record*)m_obarray.GetAt(i))->classcode, TEXT("unknow"), ((Cfull_record*)m_obarray.GetAt(i))->vegcode, (LPTSTR)(LPCTSTR)((Cfull_record*)m_obarray.GetAt(i))->vegname
					, (LPTSTR)(LPCTSTR)((Cfull_record*)m_obarray.GetAt(i))->nutrient);
				TYPE::DataInterface(header, '0', TEXT("unknow"), ((Cfull_record*)m_obarray.GetAt(i))->vegcode, TEXT("unknow")
					, TEXT("unknow"), ((Cfull_record*)m_obarray.GetAt(i))->plantcode, ((Cfull_record*)m_obarray.GetAt(i))->howbig, ((Cfull_record*)m_obarray.GetAt(i))->weight, (LPTSTR)(LPCTSTR)((Cfull_record*)m_obarray.GetAt(i))->when);
			}
		}

	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSingDocbasedDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSingDocbasedDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSingDocbasedDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSingDocbasedDoc 诊断

#ifdef _DEBUG
void CSingDocbasedDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSingDocbasedDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSingDocbasedDoc 命令


void CSingDocbasedDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类
	int ncount;
	ncount = m_obarray.GetSize();
	for (int i = 0; i < ncount; i++)
	{
		delete m_obarray.GetAt(i);
	}
	m_obarray.RemoveAll();
	CDocument::DeleteContents();
}


void CSingDocbasedDoc::OnXls32773()//xls数据导入
{
	// TODO: 在此添加命令处理程序代码
	//从excel表中读取数据
	CFileDialog  filedlg(true, L"*.xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Xls文件 (*.xls)|*.xls");
	filedlg.m_ofn.lpstrTitle = L"打开文件";
	CString strFilePath;
	if (IDOK == filedlg.DoModal())
	{
		strFilePath = filedlg.GetPathName();
	}
	else
	{
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	CApplication app;
	CWorkbook book;
	CWorkbooks books;
	CWorksheet sheet;
	CWorksheets sheets;
	CRange range;
	LPDISPATCH lpDisp;
	//定义变量
	COleVariant covOptional((long)
		DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxGetMainWnd()->MessageBox(_T("无法创建Excel应用"));
		return;
	}
	books = app.get_Workbooks();
	//打开Excel，其中pathname为Excel表的路径名
	lpDisp = books.Open(strFilePath, covOptional
		, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional
		, covOptional, covOptional, covOptional
		, covOptional, covOptional, covOptional
		, covOptional);
	book.AttachDispatch(lpDisp);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant(short(1)));//取excel文件中的第一个工作表
	COleVariant vResult;
	//读取已经使用区域的信息，包括已经使用的行数、列数、起始行、起始列
	range.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(range.get_Rows());
	//取得已经使用的行数
	long iRowNum = range.get_Count();
	range.AttachDispatch(range.get_Columns());
	//取得已经使用的列数
	long iColNum = range.get_Count();
	//取得已使用区域的起始行，从1开始
	long iStartRow = range.get_Row();
	//取得已使用区域的起始列，从1开始
	long iStartCol = range.get_Column();
	range.AttachDispatch(sheet.get_Cells());
	range.AttachDispatch(range.get_Item(COleVariant((long)1),
		COleVariant((long)1)).pdispVal);
	
	vResult = range.get_Value2();
	CString str = vResult.bstrVal;
	TCHAR classcode;
	CString classname;
	int vegcode;
	CString vegname;
	int howbig;
	int plant_code;
	float weight;
	int year;
	if (str == TEXT("分类编号"))
	{
		for (int j = 2; j <= iColNum; j++)//j为对应的列号
		{
			for (int i = 1; i <= iRowNum; i++)
			{
				range.AttachDispatch(sheet.get_Cells());
				range.AttachDispatch(range.get_Item(COleVariant((long)i),
					COleVariant((long)j)).pdispVal);
				vResult = range.get_Value2();
				str = vResult.bstrVal;
				if (vResult.vt == VT_BSTR)     //若是字符串
				{
					str = vResult.bstrVal;
					if (!str.IsEmpty() && i == 2)
						classname = str;
					if (!str.IsEmpty() && i >= 3)
					{
						TYPE::DataInterface(header, classcode, (LPTSTR)(LPCTSTR)classname, 0, (LPTSTR)(LPCTSTR)str);
					}
				}
				else if (vResult.vt == VT_R8) 
				{
					classcode =(int)vResult.dblVal+TEXT('0');
				}

			}
		}
	}
	else if (str == TEXT("蔬菜编号"))
	{
		for (int i = 2; i <= iRowNum; i++)
		{
			for (int j = 1; j <= iColNum; j++)
			{
				range.AttachDispatch(sheet.get_Cells());
				range.AttachDispatch(range.get_Item(COleVariant((long)i),
					COleVariant((long)j)).pdispVal);
				vResult = range.get_Value2();
				str = vResult.bstrVal;
				switch (j)
				{
				case 1:vegcode = vResult.dblVal;
					break;
				case 2:vegname = vResult.bstrVal;
					break;
				case 3:classcode = (int)vResult.dblVal + TEXT('0');
					break;
				case 4:
					if (!str.IsEmpty())
						TYPE::DataInterface(header, classcode, TEXT("unknow"), vegcode, (LPTSTR)(LPCTSTR)vegname,
						(LPTSTR)(LPCTSTR)str);
					break;

				}
			}
		}
		
	}
	else if (str == TEXT("编号"))
	{
		for (int i = 2; i <= iRowNum; i++)
		{
			for (int j = 1; j <= iColNum; j++)
			{
				range.AttachDispatch(sheet.get_Cells());
				range.AttachDispatch(range.get_Item(COleVariant((long)i),
					COleVariant((long)j)).pdispVal);
				vResult = range.get_Value2();
				str = vResult.bstrVal;
				switch (j)
				{
				case 1:plant_code = vResult.dblVal;
					break;
				case 2:vegcode = vResult.dblVal;
					break;
				case 3:howbig = vResult.dblVal;
					break;
				case 4:weight = vResult.dblVal;
					break;
				case 5:
					year = vResult.dblVal;
					str.Format(TEXT("%d"), year);
					if (!str.IsEmpty())
						TYPE::DataInterface(header,TEXT('0'), TEXT("unknow"), vegcode, TEXT("unknow"), TEXT("unknow"), plant_code,
							howbig, weight, (LPTSTR)(LPCTSTR)str);
					break;

				}
			}
		}
		TYPE::DataOut(m_obarray, header);
	}

	

	books.Close();	
	app.Quit(); 	//释放对象      	
	range.ReleaseDispatch();	
	sheet.ReleaseDispatch();	
	sheets.ReleaseDispatch();	
	book.ReleaseDispatch();
	books.ReleaseDispatch();	
	app.ReleaseDispatch();
	


}


//void CSingDocbasedDoc::OnXls32774()//xls数据导出
//{
//	// TODO: 在此添加命令处理程序代码
//}
