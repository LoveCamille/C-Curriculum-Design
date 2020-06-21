//
//  ExcelFunction.c
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/6/2.
//  Copyright © 2020 🌲. All rights reserved.
//

//预编译
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ExcelFunction.h"
#include "CarRentSystem.h"

//函数定义
//导入车辆分类的csv文件🏍📃（已经没有BUG🛫️）
Sort_Node * CarSortInfo_CSV_Load(FILE * fp) {//指向要加载的文件
    
    if (fp == NULL) {
        printf("文件不存在！！！⚠️\n");
    }
    
    char buffer[50];//存放文件指针读出来的一行文本内容
    char * row;//存放取出来的整行数据
    char * grid;//存放取出来的一格一格的数据
    
    Sort_Node * sort_head;//表头不放数据
    Sort_Node * p;//放数据的指针
    Sort_Node * q;//遍历指针
    
    sort_head = (Sort_Node * )malloc(sizeof(Sort_Node));
    q = sort_head;
    
    fseek(fp, 56L, SEEK_CUR);//定位到第二行数据
    while ((row = fgets(buffer, sizeof(buffer), fp)) != NULL) {//取出来的数据不为NULL就写
        
        p = (Sort_Node * )malloc(sizeof(Sort_Node));//分配内存空间
        
        grid = strtok(row, ",");//分割一整行
        p->Sort.Sort_Num = atoi(grid);//将char转换为int写入类型编码
        grid = strtok(NULL, ",");
        strcpy(p->Sort.Sort_Name, grid);//写入类型名
        grid = strtok(NULL, ",");
        p->Sort.Stock_Num = atoi(grid);//写入库存数量
        
        q->Next_Sort = p;
        q = p;
    }
    q->Next_Sort = NULL;
    printf("数据导入成功！！！\n");
    return (sort_head);
}

//导入车辆信息的csv文件🚙📃（已经没有BUG）
Car_Node * CarBasicInfo_CSV_Load(FILE * fp) {//指向要加载的文件
    
    if (fp == NULL) {
        printf("文件不存在！！！⚠️\n");
    }
    
    char buffer[100];//存放文件指针读出来的一行文本内容
    char * row;//存放取出来的整行数据
    char * grid;//存放取出来的一格一格的数据
    
    Car_Node * car_head;//表头不放数据
    Car_Node * p;//放数据的指针
    Car_Node * q;//遍历指针
    
    car_head = (Car_Node * )malloc(sizeof(Car_Node));
    q = car_head;
    
    fseek(fp, 108L, SEEK_CUR);//定位到第二行数据
    while ((row = fgets(buffer, sizeof(buffer), fp)) != NULL) {//取出来的数据不为NULL就写
        
        p = (Car_Node * )malloc(sizeof(Car_Node));//分配内存空间
        
        grid = strtok(row, ",");//分割一整行
        p->Info.Serial_Num = atoi(grid);//将char转换为int写入车辆编号
        grid = strtok(NULL, ",");
        strcpy(p->Info.Plate_Num, grid);//写入车牌号
        grid = strtok(NULL, ",");
        p->Info.Type_Num = atoi(grid);//写入类型编码
        grid = strtok(NULL, ",");
        strcpy(p->Info.Name, grid);//写入车辆名称
        grid = strtok(NULL, ",");
        strcpy(p->Info.Gear_Mode, grid);//写入排挡方式
        grid = strtok(NULL, ",");
        p->Info.Daily_Rent = atof(grid);//写入每日租金
        grid = strtok(NULL, ",");
        p->Info.Rental_Status = grid[0];//写入出租状态
        
        p->Order = NULL;//订单由于未写入，先初始化为NULL
        q->Next_Info = p;
        q = p;
    }
    q->Next_Info = NULL;
    printf("数据导入成功！！！\n");
    return (car_head);
}

//导入租车订单的csv文件🚚📃（已经没有BUG🛫️）
Car_Node * RentOrderInfo_CSV_Load(Car_Node * car_head, FILE * fp) {//指向要加载的文件
    
    if (fp == NULL) {
        printf("文件不存在！！！⚠️\n");
    }
    
    char buffer[300];//存放文件指针读出来的一行文本内容
    char * row;//存放取出来的整行数据
    char * grid;//存放取出来的一格一格的数据
    
    //基本信息
    char Order_Num[20];         //订单编号
    char ID_Num[20];            //身份证号
    char Client_Nam[20];        //客人姓名
    char Phone_Num[20];         //手机号码
    int Rent_Serial_Num;        //租用车辆编号
    char Pick_Time[18];         //取车时间
    char Promised_Ret_Time[18]; //预约还车时间
    float Deposit;              //押金
    char Actual_Ret_Time[18];   //实际还车时间
    float Promised_Fee;         //应缴费用
    float Actual_Fee;           //实缴费用
    
    Car_Node * p;//放数据的指针
    Order_Node * pp;//放数据的指针
    Order_Node * qq;//遍历指针
    
    fseek(fp, 186L, SEEK_CUR);//定位到第二行数据
    while ((row = fgets(buffer, sizeof(buffer), fp)) != NULL) {//取出来的数据不为NULL就写
        
        //暂存数据
        grid = strtok(row, ",");//分割一整行
        strcpy(Order_Num, grid);
        grid = strtok(NULL, ",");
        strcpy(ID_Num, grid);
        grid = strtok(NULL, ",");
        strcpy(Client_Nam, grid);
        grid = strtok(NULL, ",");
        strcpy(Phone_Num, grid);
        grid = strtok(NULL, ",");//为车辆编号
        Rent_Serial_Num = atoi(grid);
        grid = strtok(NULL, ",");
        strcpy(Pick_Time, grid);
        grid = strtok(NULL, ",");
        strcpy(Promised_Ret_Time, grid);
        grid = strtok(NULL, ",");
        Deposit = atof(grid);
        grid = strtok(NULL, ",");
        strcpy(Actual_Ret_Time, grid);
        grid = strtok(NULL, ",");
        Promised_Fee = atof(grid);
        grid = strtok(NULL, ",");
        Actual_Fee = atof(grid);
        
        p = car_head;
        while (p->Next_Info->Info.Serial_Num != Rent_Serial_Num && p->Next_Info->Next_Info != NULL) {
            p = p->Next_Info;
        }
        
        if (p->Next_Info->Info.Serial_Num != Rent_Serial_Num && p->Next_Info->Next_Info == NULL) {
            continue;
        }
        
        else{
            
            pp = p->Next_Info->Order;
            
            if (pp == NULL) {
                pp = (Order_Node * )malloc(sizeof(Order_Node));//分配内存空间
                
                strcpy(pp->OrderInfo.Order_Num, Order_Num);
                strcpy(pp->OrderInfo.ID_Num, ID_Num);
                strcpy(pp->OrderInfo.Client_Nam, Client_Nam);
                strcpy(pp->OrderInfo.Phone_Num, Phone_Num);
                pp->OrderInfo.Rent_Serial_Num = Rent_Serial_Num;
                strcpy(pp->OrderInfo.Pick_Time, Pick_Time);
                strcpy(pp->OrderInfo.Promised_Ret_Time, Promised_Ret_Time);
                pp->OrderInfo.Deposit = Deposit;
                strcpy(pp->OrderInfo.Actual_Ret_Time, Actual_Ret_Time);
                pp->OrderInfo.Promised_Fee = Promised_Fee;
                pp->OrderInfo.Actual_Fee = Actual_Fee;
                
                pp->Next_Order = NULL;
                p->Next_Info->Order = pp;
            }
            
            else{
                
                qq = p->Next_Info->Order;
                while (qq->Next_Order != NULL) {
                    qq = qq->Next_Order;
                }//移动到最后一个订单节点
                
                pp = (Order_Node * )malloc(sizeof(Order_Node));//分配内存空间
                
                strcpy(pp->OrderInfo.Order_Num, Order_Num);
                strcpy(pp->OrderInfo.ID_Num, ID_Num);
                strcpy(pp->OrderInfo.Client_Nam, Client_Nam);
                strcpy(pp->OrderInfo.Phone_Num, Phone_Num);
                pp->OrderInfo.Rent_Serial_Num = Rent_Serial_Num;
                strcpy(pp->OrderInfo.Pick_Time, Pick_Time);
                strcpy(pp->OrderInfo.Promised_Ret_Time, Promised_Ret_Time);
                pp->OrderInfo.Deposit = Deposit;
                strcpy(pp->OrderInfo.Actual_Ret_Time, Actual_Ret_Time);
                pp->OrderInfo.Promised_Fee = Promised_Fee;
                pp->OrderInfo.Actual_Fee = Actual_Fee;
                
                pp->Next_Order = NULL;
                
                qq->Next_Order = pp;
            }
            
        }
        
    }//写完
    printf("数据导入成功！！！\n");
    return (car_head);
}

//导出车辆分类的csv文件🏍📃（已经没有BUG🛫️）
void CarSortInfo_CSV_Output(Sort_Node * sort_head, FILE * fp) {//指向要加载的文件
    
    if (fp == NULL) {
        printf("文件不存在！！！⚠️\n");
    }
    
    Sort_Node * p;
    p = sort_head->Next_Sort;
    
    fseek(fp, 56L, SEEK_CUR);//定位到第二行数据
    while (p != NULL) {//取出来的数据不为NULL就写
        
        fprintf(fp, "%d,%s,%d\n", p->Sort.Sort_Num, p->Sort.Sort_Name, p->Sort.Stock_Num);
        p = p->Next_Sort;
    }
    
    printf("数据导出成功！！！\n");
    return ;
}

//导出车辆信息的csv文件🚙📃（已经没有BUG）
void CarBasicInfo_CSV_Output(Car_Node * car_head, FILE * fp) {//指向要加载的文件
    
    if (fp == NULL) {
        printf("文件不存在！！！⚠️\n");
    }
    
    Car_Node * p;
    p = car_head->Next_Info;
    
    fseek(fp, 108L, SEEK_CUR);//定位到第二行数据
    while (p != NULL) {//取出来的数据不为NULL就写
        
        fprintf(fp, "%d,%s,%d,%s,%s,%f,%c\n", p->Info.Serial_Num, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Daily_Rent, p->Info.Rental_Status);
        p = p->Next_Info;
        
    }
    
    printf("数据导出成功！！！\n");
    return ;
}

//导出租车订单的csv文件🚚📃（已经没有BUG）
void RentOrderInfo_CSV_Output(Car_Node * car_head, FILE *fp) {//指向要加载的文件
    
    if (fp == NULL) {
        printf("文件不存在！！！⚠️\n");
    }
    
    Car_Node * p;//放数据的指针
    p = car_head->Next_Info;//指向第一个节点
    
    Order_Node * pp;//放数据的指针
    
    fseek(fp, 186L, SEEK_CUR);//定位到第二行数据
    while (p != NULL) {
        
        //p指向的订单为空就到下一个节点
        if (p->Order == NULL) {
            p = p->Next_Info;
        }
        
        //指向的订单不为空了
        else{
            pp = p->Order;
            
            while (pp != NULL) {
                fprintf(fp, "%s,%s,%s,%s,%d,%s,%s,%f,%s,%f,%f\n", pp->OrderInfo.Order_Num, pp->OrderInfo.ID_Num, pp->OrderInfo.Client_Nam, pp->OrderInfo.Phone_Num, pp->OrderInfo.Rent_Serial_Num, pp->OrderInfo.Pick_Time, pp->OrderInfo.Promised_Ret_Time, pp->OrderInfo.Deposit, pp->OrderInfo.Actual_Ret_Time, pp->OrderInfo.Promised_Fee, pp->OrderInfo.Actual_Fee);
                pp = pp->Next_Order;
            }
            p = p->Next_Info;
        }
    }
    
    printf("数据导出成功！！！\n");
    return ;
}
