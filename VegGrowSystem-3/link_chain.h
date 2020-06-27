#pragma once

#include <Windows.h>
#include <atlstr.h>
#include <vector>
#include <tchar.h>
using namespace std;
//���ݽṹ��ʹ��ͷ�ڵ����������
namespace TYPE
{
	//---------------------------------------------------------
	class plant//��ֲ��Ϣ
	{
	public:
		int plantcode;//���
		int vegcode;//�߲˱��
		int howbig;//���
		float weight;//����
		TCHAR when[5];//���
		plant* next;//����ָ��
		plant() { plantcode = 0; vegcode = 0; howbig = 0; weight = 0; lstrcpyW(when, TEXT("unknow")); next = NULL; }
	};
	class basic//������Ϣ
	{
	public:
		int vegcode;//�߲˱��
		TCHAR vegname[20];//�߲�����
		TCHAR classcode;//�������
		TCHAR nutrient[20];//Ӫ���ɷ�
		plant* ptr_plant;//����ֲ��Ϣ��ָ��
		basic* next;//����ָ��
		basic() { vegcode = 0; lstrcpyW(vegname, TEXT("unknow")); classcode = TEXT('0'); lstrcpyW(nutrient, TEXT("unknow")); ptr_plant = NULL; next = NULL; }
	};

	class kind//������Ϣ
	{
	public:
		TCHAR classcode;//�������
		TCHAR classname[8];//��������
		basic* ptr_basic;//��������Ϣ��ָ��
		kind * next;//����ָ��
		kind() { classcode = TEXT('0'); lstrcpyW(classname, TEXT("unknow")); ptr_basic = NULL; next = NULL; }
	};


	bool DataInterface(kind*&  header, TCHAR classcode = TEXT('0'), TCHAR classname[] = TEXT("unknow"), int vegcode = 0, TCHAR vegname[] = TEXT("unknow"),
		TCHAR nutrient[] = TEXT("unknow"), int plantcode = 0, int howbig = 0, float weight = 0, TCHAR when[] = TEXT("unknow"));
	void DataOut(CObArray& list, kind* header);
	//-----------------------------------------------------------------
	
}


class Cfull_record : public CObject //�������ڵ���͵���
{
	DECLARE_SERIAL(Cfull_record)
public:
	TCHAR classcode;
	CString classname;
	int vegcode;
	CString vegname;
	CString nutrient;
	int plantcode;
	int howbig;
	float weight;
	CString when;
	Cfull_record() { classcode = TEXT('0'); classname = TEXT("unknow"); vegcode = 0; vegname = TEXT("unknow"); classcode = TEXT('0'); nutrient = TEXT("unknow"); plantcode = 0; howbig = 0; weight = 0; when = TEXT("unknow"); }
	void Serialize(CArchive& ar);
};
int minOfTreeNum(int a, int b, int c);
int levenSTDistance(CString x, CString y);
int vague_match(Cfull_record* pReco, CString checkinfo);