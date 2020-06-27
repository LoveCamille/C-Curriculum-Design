// CWndChange.cpp: 实现文件
//

#include "stdafx.h"
#include "SingDoc_based.h"
#include "SingDoc_basedDoc.h"
#include "CWndChange.h"
#include "link_chain.h"
#include "MainFrm.h"

IMPLEMENT_DYNCREATE(CWndchange, CFormView)

CWndchange::CWndchange(): CFormView(IDD_DIALOG4), m_classcode(0)
, m_classname(_T(""))
, m_vegcode(0)
, m_vegname(_T(""))
, m_nutrient(_T(""))
, m_plantcode(0)
, howbig(0)
, m_weight(0)
, m_when(2015)
{

}

CWndchange::~CWndchange()
{
}

BEGIN_MESSAGE_MAP(CWndchange, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CWndchange::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWndchange::OnBnClickedButton2)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CWndchange::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CWndchange::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CWndchange::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, sdf);
	DDX_Text(pDX, IDC_EDIT1, m_classcode);
	DDX_Text(pDX, IDC_EDIT2, m_classname);
	DDX_Text(pDX, IDC_EDIT3, m_vegcode);
	DDX_Text(pDX, IDC_EDIT4, m_vegname);
	DDX_Text(pDX, IDC_EDIT5, m_nutrient);
	DDX_Text(pDX, IDC_EDIT6, m_plantcode);
	DDX_Text(pDX, IDC_EDIT7, howbig);
	DDX_Text(pDX, IDC_EDIT8, m_weight);
	DDX_Text(pDX, IDC_EDIT9, m_when);
	DDV_MinMaxInt(pDX, m_when, 2015, 2020);
}


// CWndChange 消息处理程序




void CWndchange::OnBnClickedButton1()//更新数据
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_classcode == 0 ||m_classname==TEXT("")|| m_vegcode == 0 ||m_vegname==TEXT("")||
		m_plantcode == 0|| m_nutrient == TEXT("") || m_plantcode == 0 || howbig == 0 || ((int)m_weight) == 0)
	{
		MessageBox(TEXT("你没有提供全面的数据"), TEXT("warning"));
		return;
	}
	CString when;
	when.Empty();
	when.Format(TEXT("%d"), m_when);
	TYPE::DataInterface(((CSingDocbasedDoc*)GetDocument())->header, m_classcode + '0', (LPTSTR)(LPCTSTR)m_classname);
	TYPE::DataInterface(((CSingDocbasedDoc*)GetDocument())->header,m_classcode+'0',TEXT("unknow"),m_vegcode, (LPTSTR)(LPCTSTR)m_vegname
	 , (LPTSTR)(LPCTSTR)m_nutrient);
	TYPE::DataInterface(((CSingDocbasedDoc*)GetDocument())->header, '0', TEXT("unknow"), m_vegcode, TEXT("unknow")
		 , TEXT("unknow"), m_plantcode, howbig, m_weight, (LPTSTR)(LPCTSTR)when);
	TYPE::DataOut(((CSingDocbasedDoc*)GetDocument())->m_obarray, ((CSingDocbasedDoc*)GetDocument())->header);
}


void CWndchange::OnBnClickedButton2()//删除数据
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (((CSingDocbasedDoc*)GetDocument())->header == NULL)
	{
		MessageBox(TEXT("链表为空"));
		return;
	}
	if ((m_vegcode != 0 && m_classcode != 0)|| (m_vegcode != 0 && m_plantcode != 0)|| (m_plantcode != 0 && m_classcode != 0))
	{
		MessageBox(TEXT("三个分类号只能有一个不为0"));
		return;
	}
	TYPE::kind* ptr1 = ((CSingDocbasedDoc*)GetDocument())->header->next;
	TYPE::basic* ptr2;
	TYPE::plant* ptr3;
	if (ptr1->ptr_basic != NULL)
		ptr2 = ptr1->ptr_basic->next;//跳过头节点
	else
		ptr2 = NULL;
	if (ptr2 != NULL && ptr2->ptr_plant != NULL)
		ptr3 = ptr2->ptr_plant->next;
	else
		ptr3 = NULL;

	if (m_plantcode != 0)
	{
		TYPE::plant* pre=ptr3;
		while (ptr1 != NULL)
		{


			if (ptr2 != NULL)
			{

				if (ptr3 != NULL)
				{
					if (ptr3->plantcode == m_plantcode)
					{
						pre->next = ptr3->next;
						delete ptr3;
						MessageBox(TEXT("删除成功"));
						TYPE::DataOut(((CSingDocbasedDoc*)GetDocument())->m_obarray, ((CSingDocbasedDoc*)GetDocument())->header);
						return;
					}
					pre = ptr3;
					ptr3 = ptr3->next;

				}
				else
				{
					ptr2 = ptr2->next;
					if (ptr2 != NULL && ptr2->ptr_plant != NULL)
					{
						pre = ptr2->ptr_plant;
						ptr3 = ptr2->ptr_plant->next;
					}
				}
			}
			else
			{
				ptr1 = ptr1->next;
				if (ptr1 != NULL && ptr1->ptr_basic != NULL)
				{
					ptr2 = ptr1->ptr_basic->next;
					if (ptr2 != NULL && ptr2->ptr_plant != NULL)
					{
						pre = ptr2->ptr_plant;
						ptr3 = ptr2->ptr_plant->next;
					}
				}
			}

		}
		MessageBox(TEXT("没有找到种植号对应的信息"));
		
	}
	else if(m_vegcode!=0)
	{
		TYPE::basic* pre;
		while (ptr1 != NULL)
		{


			if (ptr2 != NULL)
			{
				if (ptr2->vegcode == m_vegcode)
				{
					pre->next = ptr2->next;
					ptr3 = ptr2->ptr_plant;
					TYPE::plant* pre3;
					while (ptr3!=NULL)
					{
						pre3 = ptr3;
						ptr3 = ptr3->next;
						delete pre3;
					}
					delete ptr2;
					MessageBox(TEXT("删除成功"));
					TYPE::DataOut(((CSingDocbasedDoc*)GetDocument())->m_obarray, ((CSingDocbasedDoc*)GetDocument())->header);
					return;
				}

				pre = ptr2->next;
				ptr2 = ptr2->next;
					
			}
			else
			{
				ptr1 = ptr1->next;
				if (ptr1 != NULL && ptr1->ptr_basic != NULL)
				{
					pre = ptr1->ptr_basic;
					ptr2 = ptr1->ptr_basic->next;
					
				}
			}

		}
		MessageBox(TEXT("没有找到蔬菜号对应的信息"));

	}
	else if (m_classcode!=0)
	{
		TYPE::kind* pre= ((CSingDocbasedDoc*)GetDocument())->header;
		while(ptr1->classcode!=m_classcode+'0')
			if (ptr1->next != NULL)
			{
				pre = ptr1;
				ptr1 = ptr1->next;
			}
			else
			{
				break;
			}
		TCHAR i = m_classcode + '0';
		if (ptr1->classcode == m_classcode+'0')
		{
			pre->next = ptr1->next;
			ptr2 = ptr1->ptr_basic;
			while (ptr2 != NULL)
			{
				ptr3 = ptr2->ptr_plant;
				TYPE::plant* pre3;
				while (ptr3 != NULL)
				{
					pre3 = ptr3;
					ptr3 = ptr3->next;
					delete pre3;
				}
				TYPE::basic * pre2 = ptr2;
				ptr2 = ptr2->next;
				delete pre2;
			}
			delete ptr1;
			MessageBox(TEXT("删除成功"));
			TYPE::DataOut(((CSingDocbasedDoc*)GetDocument())->m_obarray, ((CSingDocbasedDoc*)GetDocument())->header);
			return;

		}
		else
		{
			MessageBox(TEXT("没有找到分类号对应的信息"));
		}
	}
	else
	{
		MessageBox(TEXT("没有选择任何内容"), TEXT("waring"));
	}
}
