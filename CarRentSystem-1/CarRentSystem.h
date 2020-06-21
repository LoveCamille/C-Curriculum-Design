//
//  CarRentSystem.h
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/2/4.
//  Copyright © 2020 🌲. All rights reserved.
//

#ifndef CarRentSystem_h
#define CarRentSystem_h

//预编译
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结构体声明
struct Car_Sort_Info;           //车辆分类信息
struct Car_Basic_Info;          //车辆基本信息
struct Rent_Order_Info;         //租车订单信息
struct Sort_Node;               //车辆分类节点
struct Car_Node;                //车辆信息节点
struct Order_Node;              //租车订单节点

//车辆分类信息
typedef struct Car_Sort_Info {
    //基本信息
    char Sort_Num;              //类型编码
    char Sort_Name[20];         //类型名称
    int Stock_Num;              //该类型库存数量
}Car_Sort_Info;

//车辆基本信息
typedef struct Car_Basic_Info {
    //基本信息
    int Serial_Num;             //车辆编号
    char Plate_Num[10];         //车牌号
    char Type_Num;              //车辆类型编码
    char Name[20];              //车辆名称
    char Gear_Mode[12];         //排挡方式
    float Daily_Rent;           //每日租金
    char Rental_Status;         //出租状态
}Car_Basic_Info;

//租车订单信息
typedef struct Rent_Order_Info {
    //基本信息
    char Order_Num[20];         //订单编号
    char ID_Num[20];            //身份证号
    char Client_Nam[20];        //客人姓名
    char Phone_Num[20];         //手机号码
    int Rent_Serial_Num;    //租用车辆编号
    char Pick_Time[18];         //取车时间
    char Promised_Ret_Time[18]; //预约还车时间
    float Deposit;              //押金
    char Actual_Ret_Time[18];   //实际还车时间
    float Promised_Fee;         //应缴费用
    float Actual_Fee;           //实缴费用
}Rent_Order_Info;

//车辆分类节点
typedef struct Sort_Node {
    //信息域💾
    struct Car_Sort_Info Sort;
    //链接对象🔗
    struct Sort_Node * Next_Sort;
}Sort_Node;

//车辆信息节点
typedef struct Car_Node {
    //信息域💾
    struct Car_Basic_Info Info;
    //链接对象🔗
    struct Car_Node * Next_Info;
    struct Order_Node * Order;
}Car_Node;

//租车订单节点
typedef struct Order_Node {
    //信息域💾
    struct Rent_Order_Info OrderInfo;
    //链接对象🔗
    struct Order_Node * Next_Order;
}Order_Node;

//函数声明
//显示函数
void draw(float p);//画图
void Show_Menu(void);//显示菜单

//输出类函数
void CarSortInfo_Print(Sort_Node * sort_head);//输出车辆类型信息
void CarBasicInfo_Print(Car_Node * head);//输出车辆基本信息
void RentOrderInfo_Print(Car_Node * car_head);//输出租车订单信息

//类型数据维护函数
void CarSortInfo_Add(Sort_Node * sort_head);//增加车辆类型
void CarSortInfo_Delete(Sort_Node * sort_head);//删除车辆类型
void CarSortInfo_Edit(Sort_Node * sort_head);//修改车辆类型

//车辆信息数据维护函数
void CarBasicInfo_Add(Car_Node * car_head);//增加车辆信息
void CarBasicInfo_Delete(Car_Node * car_head);//删除车辆信息
void CarBasicInfo_Edit(Car_Node * car_head);//修改车辆信息

//租车订单数据维护函数
void RentOrderInfo_Add(Car_Node * car_head);//增加租车订单
void RentOrderInfo_Delete(Car_Node * car_head);//删除租车订单
void RentOrderInfo_Edit(Car_Node * car_head);//修改租车订单

#endif /* CarRentSystem_h */
