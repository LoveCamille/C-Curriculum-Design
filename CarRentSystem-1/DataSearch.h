//
//  DataSearch.h
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/6/2.
//  Copyright © 2020 🌲. All rights reserved.
//

#ifndef DataSearch_h
#define DataSearch_h

//预编译
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarRentSystem.h"

//函数声明
//查找类型
void search_by_type(Sort_Node* sort_head, Car_Node* car_head,char *s);//综合查找的子模块
void Comprehensive_Search_by_Type(Car_Node* car_head, Sort_Node* sort_head);//综合查找

//查找车辆
int Car_FreeSearch(Car_Node * car_head);
int Car_Search(Car_Node * car_head, FILE * fp);//查找车辆
int Car_Search_PlateNum(Car_Node * car_head, FILE * fp);//车牌号为依据
int Car_Search_Name(Car_Node * car_head, FILE * fp);//车辆名称为依据
int Car_Search_RentalStatus(Car_Node * car_head, FILE * fp);//出租状态为依据

//查找订单
int Order_Search_Client(Car_Node * car_head, FILE *fp);//客人信息
int Order_Search_Car(Car_Node * car_head, FILE *fp);//车辆信息
int Order_Search_Time(Car_Node * car_head, FILE *fp);//时间范围

//数据统计
void Calculate_Sort(Sort_Node * sort_head,Car_Node * car_head);//类型统计
void Calculate_Profit(Sort_Node * sort_head, Car_Node * car_head);//类型利润统计
void Calculate_Carprofit(Car_Node * car_head);//车辆利润
void Calculate_mvp(Car_Node * car_head);//前十的利润

#endif /* DataSearch_h */
