//
//  ExcelFunction.h
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/6/2.
//  Copyright © 2020 🌲. All rights reserved.
//

#ifndef ExcelFunction_h
#define ExcelFunction_h

//预编译
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarRentSystem.h"

//函数声明
//数据导入函数
Sort_Node * CarSortInfo_CSV_Load(FILE * fp);//导入车辆分类的csv文件🏍📃
Car_Node * CarBasicInfo_CSV_Load(FILE * fp);//导入车辆信息的csv文件🚙📃
Car_Node * RentOrderInfo_CSV_Load(Car_Node * car_head, FILE * fp);//导入租车订单的csv文件🚚📃

//数据导出函数
void CarSortInfo_CSV_Output(Sort_Node * sort_head, FILE * fp);//导出车辆分类的csv文件🏍📃
void CarBasicInfo_CSV_Output(Car_Node * car_head, FILE * fp);//导出车辆信息的csv文件🚙📃
void RentOrderInfo_CSV_Output(Car_Node * car_head, FILE *fp);//导出租车订单的csv文件🚚📃

#endif /* ExcelFunction_h */
