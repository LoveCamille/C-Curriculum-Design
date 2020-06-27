#include "stdafx.h"
#include "link_chain.h"
#include <atlconv.h>
namespace TYPE
{
	bool DataInterface(kind*&  header, TCHAR classcode, TCHAR classname[] , int vegcode , TCHAR vegname[] ,
		TCHAR nutrient[], int plantcode, int howbig, float weight, TCHAR when[])
		//���������ݵ����룬ʹ��ͳһ�����ݽӿ�
	{
		/*
		���Է��֣������Ѱ·������ʵ�ǳ��򵥣�ֻʹ�����߲˵ķ���Ż��߲�����ı�ţ��������ҽ���ͨ���鿴����źͱ�ŵ�����ȷ���������е�λ��
		ֻ�з����-����������
		ͬʱ�з���ź��߲˺�-�������߲���Ϣ������д�������ƣ�
		-----------------------------------------------
		ֻ���߲˺�-��������ֲ������д�߲���Ϣ��
		ֻ����ֲ������ǰ���룬��Ϊ����ȷ�������λ��
		*/
		if (classcode != TEXT('0') || vegcode != 0)
		{
			if (header == NULL)header = new kind;//ͷ�ڵ㣬���洢����
			if (classcode != TEXT('0'))//�����߲������ �� �߲���Ϣ��
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
					if (ptr2 == NULL)ptr1->ptr_basic = new basic;//ͷ�ڵ㣬���洢����
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
			else//������ֲ��Ϣ��
			{
				kind* ptr1 = header->next;
				basic* ptr2 = header->next->ptr_basic->next;//����ͷ�ڵ�
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
					if (ptr3 == NULL)ptr2->ptr_plant = new plant;//ͷ�ڵ�
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


	void DataOut(CObArray& list, kind* header)//list���ڴ�ֵ,�����������������ɼ�¼�������ڶ�̬�����У����ݸ�������
	{
		kind* ptr1 = header->next;
		basic* ptr2;
		plant* ptr3;
		if (ptr1->ptr_basic != NULL)
			ptr2= header->next->ptr_basic->next;//����ͷ�ڵ�
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

int minOfTreeNum(int a, int b, int c)  //����a��b��c����������Сֵ
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

int levenSTDistance(CString x, CString y)  //�����ַ���x���ַ���y��levenshtein����
{
	int lenx = x.GetLength();
	int leny = y.GetLength();
	int **levenST = new int*[lenx + 1];
	for (int i = 0; i < lenx + 1; i++)
		levenST[i] = new int[leny + 1];

	//����һ����ά�����ű༭����
	int eq = 0;                   //���������ĸ�Ƿ����
	int i, j;

	//��ʼ����ά���飬Ҳ���ǽ�������ε�levenshtein����д��
	for (i = 0; i <= lenx; i++)
	{
		levenST[i][0] = i;
	}
	for (j = 0; j <= leny; j++)
	{
		levenST[0][j] = j;
	}

	//����x�ʹ�y�е���ĸ�������бȽϣ��ó���Ӧ�ִ��ı༭����
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
	//����ֵ��ƥ���������ƶȣ�Ϊint������ֵԽ��֤�����ƶȾ�Խ��
	//ƥ��������Ѿ��γɵ����ƶȲ�����Ϊ������ƥ�������
	int ret = -1;
	checkinfo.Trim();
	CString seperator = TEXT(" \t");
	CString token;
	int pos = 0;
	token = checkinfo.Tokenize(seperator, pos);
	while (!token.IsEmpty())
	{
		int len = token.GetLength();
		if (token==token.SpanIncluding(TEXT("0123456789.")))//�����ֽ���ƥ��
		{
			CString str;
			str.Empty();
			str.Insert(0, pReco->classcode);
			if (token.Find(TEXT(".")) == -1)//��������ƥ��
			{
				if (pReco->vegcode == _ttoi(token) )ret += 3;
				if( _ttoi(str) == _ttoi(token))ret += 3;
				if(pReco->howbig == _ttoi(token)) ret += 3;
				if(pReco->plantcode == _ttoi(token))ret += 3;
				if (pReco->when == token)ret += 3;
			}
			else//�Ը�������ƥ��
			{
				str.Empty();
				str.Format(TEXT("%f"), pReco->weight);
				if (str == token)ret += 3;
			}



		}
		else//���ַ�����ƥ��
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
