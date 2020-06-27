#include "stdafx.h"
#include "link_chain.h"
#include <atlconv.h>
namespace TYPE
{
	bool DataInterface(kind*&  header, TCHAR classcode, TCHAR classname[] , int vegcode , TCHAR vegname[] ,
		TCHAR nutrient[], int plantcode, int howbig, float weight, TCHAR when[])
		//尽量简化数据的输入，使用统一的数据接口
	{
		/*
		可以发现，链表的寻路规则其实非常简单，只使用了蔬菜的分类号或蔬菜自身的编号，所以能且仅能通过查看分类号和编号的内容确定在链表中的位置
		只有分类号-》导入分类表
		同时有分类号和蔬菜号-》导入蔬菜信息表（不能写分类名称）
		-----------------------------------------------
		只有蔬菜号-》导入种植表（不能写蔬菜信息）
		只有种植表不能提前导入，因为不能确定导入的位置
		*/
		if (classcode != TEXT('0') || vegcode != 0)
		{
			if (header == NULL)header = new kind;//头节点，不存储内容
			if (classcode != TEXT('0'))//导入蔬菜种类表 或 蔬菜信息表
			{
				kind* ptr1 = header;
				while (ptr1->classcode != classcode)
					if (ptr1->next != NULL) ptr1 = ptr1->next;
					else
					{
						break;
					}
				if (ptr1->next == NULL&&ptr1->classcode!=classcode) {
					ptr1->next = new kind; ptr1->next->classcode = classcode;
					lstrcpyW(ptr1->next->classname, classname);
					ptr1 = ptr1->next;
				}
				
					basic* ptr2 = ptr1->ptr_basic;
					if (ptr2 == NULL)ptr1->ptr_basic = new basic;//头节点，不存储内容
					ptr2 = ptr1->ptr_basic;
					while ((ptr2->vegcode != vegcode &&CString(ptr2->vegname)!=CString( vegname)) || vegcode ==0)
						if (ptr2->next != NULL) ptr2 = ptr2->next;
						else
						{
							break;
						}
					if ((ptr2->vegcode != vegcode && CString(ptr2->vegname) != CString(vegname)) || vegcode==0) {
						ptr2->next = new basic; ptr2 = ptr2->next;
					}
					ptr2->classcode = classcode;
					ptr2->vegcode = vegcode;
					lstrcpyW(ptr2->vegname, vegname);
					lstrcpyW(ptr2->nutrient, nutrient);
				if(vegcode==0)
					lstrcpyW(ptr1->classname, classname);
					

			}
			else//导入种植信息表
			{
				kind* ptr1 = header->next;
				basic* ptr2 = header->next->ptr_basic->next;//跳过头节点
				while (ptr2->vegcode != vegcode && ptr1 != NULL)
				{
					if (ptr2->next != NULL)
					{
						ptr2 = ptr2->next;
					}
					else 
					{
						ptr1 = ptr1->next;
						if (ptr1 != NULL && ptr1->ptr_basic != NULL)
							ptr2 = ptr1->ptr_basic->next;
					}
				}
				if (ptr1 == NULL)return false;
				else
				{
					plant* ptr3 = ptr2->ptr_plant;
					if (ptr3 == NULL)ptr2->ptr_plant = new plant;//头节点
					ptr3 = ptr2->ptr_plant;
					while (true)
					{
						if (ptr3->next != NULL)ptr3 = ptr3->next;
						else break;
					}
					ptr3->next = new plant;
					ptr3->next->howbig = howbig;
					ptr3->next->plantcode = plantcode;
					ptr3->next->vegcode = vegcode;
					ptr3->next->weight = weight;
					lstrcpyW(ptr3->next->when, when);
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}


	void DataOut(CObArray& list, kind* header)//list用于传值,将链表里的内容整理成记录，储存在动态数组中，传递给调用者
	{
		kind* ptr1 = header->next;
		basic* ptr2;
		plant* ptr3;
		if (ptr1->ptr_basic != NULL)
			ptr2= header->next->ptr_basic->next;//跳过头节点
		else
			ptr2 = NULL;
		if (ptr2 != NULL && ptr2->ptr_plant != NULL)
			ptr3 = ptr2->ptr_plant->next;
		else
			ptr3 = NULL;
		
		int ncount = list.GetSize();
		for (int i = 0; i < ncount; i++)
			delete list.GetAt(i);
		list.RemoveAll();
		Cfull_record* ptr;
		while (ptr1 != NULL)
		{

			if (ptr2 != NULL)
			{
				if (ptr2->ptr_plant == NULL)
				{
					ptr = new Cfull_record;
					ptr->classcode = ptr1->classcode;
					ptr->classname = ptr1->classname;
					ptr->vegname = ptr2->vegname;
					ptr->vegcode = ptr2->vegcode;
					ptr->nutrient = ptr2->nutrient;
					ptr->howbig = 0;
					ptr->weight = 0;
					ptr->when = TEXT("unknow");
					ptr->plantcode = 0;
					list.Add(ptr);
				}
				if (ptr3 != NULL)
				{
					
					ptr = new Cfull_record;
					ptr->classcode = ptr1->classcode;
					ptr->classname = ptr1->classname;
					ptr->vegname = ptr2->vegname;
					ptr->vegcode = ptr2->vegcode;
					ptr->nutrient = ptr2->nutrient;
					ptr->howbig = ptr3->howbig;
					ptr->plantcode = ptr3->plantcode;
					ptr->weight = ptr3->weight;
					ptr->when = ptr3->when;
					ptr3 = ptr3->next;
					list.Add(ptr);
				}
				else
				{
					ptr2 = ptr2->next;
					if (ptr2 != NULL && ptr2->ptr_plant != NULL)
						ptr3 = ptr2->ptr_plant->next;
				}
			}
			else
			{
				ptr1 = ptr1->next;
				if (ptr1 != NULL && ptr1->ptr_basic != NULL)
				{
					ptr2 = ptr1->ptr_basic->next;
					if (ptr2 != NULL && ptr2->ptr_plant != NULL)
						ptr3 = ptr2->ptr_plant->next;
				}
			}

		}
	}


	

	
	//------------------------------------------------------------------

}
IMPLEMENT_SERIAL(Cfull_record,CObject,1)
void Cfull_record::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << classcode << classname << vegcode << vegname << nutrient << plantcode
			<< howbig << weight << when;
	}
	else
	{
		ar >> classcode >> classname >> vegcode >> vegname >> nutrient >> plantcode
			>> howbig >> weight >> when;
	}
}

int minOfTreeNum(int a, int b, int c)  //返回a，b，c三个数中最小值
{
	int minNum = a;
	if (minNum > b)
	{
		minNum = b;
	}
	if (minNum > c)
	{
		minNum = c;
	}
	return minNum;
}

int levenSTDistance(CString x, CString y)  //计算字符串x和字符串y的levenshtein距离
{
	int lenx = x.GetLength();
	int leny = y.GetLength();
	int **levenST = new int*[lenx + 1];
	for (int i = 0; i < lenx + 1; i++)
		levenST[i] = new int[leny + 1];

	//申请一个二维数组存放编辑距离
	int eq = 0;                   //存放两个字母是否相等
	int i, j;

	//初始化二维数组，也就是将最简单情形的levenshtein距离写入
	for (i = 0; i <= lenx; i++)
	{
		levenST[i][0] = i;
	}
	for (j = 0; j <= leny; j++)
	{
		levenST[0][j] = j;
	}

	//将串x和串y中的字母两两进行比较，得出相应字串的编辑距离
	for (i = 1; i <= lenx; i++)
	{
		for (j = 1; j <= leny; j++)
		{
			if (x[i - 1] == y[j - 1])
			{
				eq = 0;
			}
			else {
				eq = 1;
			}
			levenST[i][j] = minOfTreeNum(levenST[i - 1][j] + 1, levenST[i][j - 1] + 1, levenST[i - 1][j - 1] + eq);
		}
	}
	int m = levenST[lenx][leny];
	for (int i = 0; i < lenx + 1; i++)
		delete[] levenST[i];
	delete[] levenST;
	
	return m;
}


int vague_match(Cfull_record* pReco, CString checkinfo)
{
	//返回值是匹配结果的相似度，为int，返回值越大，证明相似度就越高
	//匹配过程中已经形成的相似度不能因为后续不匹配而降低
	int ret = -1;
	checkinfo.Trim();
	CString seperator = TEXT(" \t");
	CString token;
	int pos = 0;
	token = checkinfo.Tokenize(seperator, pos);
	while (!token.IsEmpty())
	{
		int len = token.GetLength();
		if (token==token.SpanIncluding(TEXT("0123456789.")))//对数字进行匹配
		{
			CString str;
			str.Empty();
			str.Insert(0, pReco->classcode);
			if (token.Find(TEXT(".")) == -1)//对整数的匹配
			{
				if (pReco->vegcode == _ttoi(token) )ret += 3;
				if( _ttoi(str) == _ttoi(token))ret += 3;
				if(pReco->howbig == _ttoi(token)) ret += 3;
				if(pReco->plantcode == _ttoi(token))ret += 3;
				if (pReco->when == token)ret += 3;
			}
			else//对浮点数的匹配
			{
				str.Empty();
				str.Format(TEXT("%f"), pReco->weight);
				if (str == token)ret += 3;
			}



		}
		else//对字符进行匹配
		{
			CString str;
			str.Empty();
			str.Insert(0, token[0]);
			if (pReco->vegname.Find(token) != -1) { ret += 3; }
			else {
				CString str, substr;
				str.Empty();
				str.Insert(0, token[0]);
				substr.Empty();
				if (pReco->vegname.Find(str) != -1)
				{
					substr = pReco->vegname.Mid(pReco->vegname.Find(str), len);
					ret += (3 - levenSTDistance(substr, token)) > 0 ? (3 - levenSTDistance(substr, token)) : 0;
				}
			}
			if (pReco->nutrient.Find(token) != -1) { ret += 3; }
			else {
				CString str, substr;
				str.Empty();
				str.Insert(0, token[0]);
				substr.Empty();
				if (pReco->nutrient.Find(str) != -1)
				{
					substr = pReco->nutrient.Mid(pReco->nutrient.Find(str), len);
					ret += (3 - levenSTDistance(substr, token)) > 0 ? (3 - levenSTDistance(substr, token)) : 0;
				}
			}
			if (pReco->classname.Find(token) != -1) { ret += 3; }
			else {
				CString str, substr;
				str.Empty();
				str.Insert(0, token[0]);
				substr.Empty();
				if (pReco->classname.Find(str) != -1)
				{
					substr = pReco->classname.Mid(pReco->classname.Find(str), len);
					ret += (3 - levenSTDistance(substr, token)) > 0 ? (3 - levenSTDistance(substr, token)) : 0;
				}
			}

			CString strtemp(pReco->when);
			if (strtemp.Find(token) != -1) { ret += 3; }
			else {
				CString substr;
				substr.Empty();
				if (strtemp.Find(str) != -1)
				{
					substr = strtemp.Mid(strtemp.Find(str), len);
					ret += (3 - levenSTDistance(substr, token)) > 0 ? (3 - levenSTDistance(substr, token)) : 0;
				}
			}

		}
		token = checkinfo.Tokenize(seperator, pos);
	}
	return ret;
}
