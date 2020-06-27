#pragma once

#include <Windows.h>
#include <atlstr.h>
#include <vector>
#include <tchar.h>
using namespace std;
//数据结构是使用头节点的三重链表
namespace TYPE
{
	//---------------------------------------------------------
	class plant//种植信息
	{
	public:
		int plantcode;//编号
		int vegcode;//蔬菜编号
		int howbig;//面积
		float weight;//重量
		TCHAR when[5];//年份
		plant* next;//链表指向
		plant() { plantcode = 0; vegcode = 0; howbig = 0; weight = 0; lstrcpyW(when, TEXT("unknow")); next = NULL; }
	};
	class basic//基本信息
	{
	public:
		int vegcode;//蔬菜编号
		TCHAR vegname[20];//蔬菜名字
		TCHAR classcode;//分类编码
		TCHAR nutrient[20];//营养成分
		plant* ptr_plant;//到种植信息的指针
		basic* next;//链表指向
		basic() { vegcode = 0; lstrcpyW(vegname, TEXT("unknow")); classcode = TEXT('0'); lstrcpyW(nutrient, TEXT("unknow")); ptr_plant = NULL; next = NULL; }
	};

	class kind//种类信息
	{
	public:
		TCHAR classcode;//分类编码
		TCHAR classname[8];//分类名称
		basic* ptr_basic;//到基本信息的指针
		kind * next;//链表指向
		kind() { classcode = TEXT('0'); lstrcpyW(classname, TEXT("unknow")); ptr_basic = NULL; next = NULL; }
	};


	bool DataInterface(kind*&  header, TCHAR classcode = TEXT('0'), TCHAR classname[] = TEXT("unknow"), int vegcode = 0, TCHAR vegname[] = TEXT("unknow"),
		TCHAR nutrient[] = TEXT("unknow"), int plantcode = 0, int howbig = 0, float weight = 0, TCHAR when[] = TEXT("unknow"));
	void DataOut(CObArray& list, kind* header);
	//-----------------------------------------------------------------
	
}


class Cfull_record : public CObject //仅能用于导入和导出
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