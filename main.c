//
//  main.c
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/1/27.
//  Copyright © 2020 🌲. All rights reserved.
//

//预编译
#include <math.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarRentSystem.h"
#include "DataSearch.h"
#include "ExcelFunction.h"

//主函数
int main(void) {
    
    int op = 1;
    
    Sort_Node * sort_head = NULL;
    Car_Node * car_head = NULL;
    
    FILE * fp_sort = NULL;
    FILE * fp_car = NULL;
    FILE * fp_order = NULL;
    
    while (op != 0) {
        
        system("clear");
        
        Show_Menu();//展示菜单
        
        //功能选择
        printf("请输入要运行的功能[0～24]:\n");
        scanf("%d", &op);
        
        //处理非法输入
        if(op<0||op>24){
            printf("option非法，请重新输入！\n");
            getchar();
            getchar();
            continue;
        }
        
        switch (op) {
                
            //载入功能（1～3）（已经完成调试）
            case 1:
                //创建类型链表并导入
                fp_sort = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/车辆分类信息表.csv", "r");
                sort_head = CarSortInfo_CSV_Load(fp_sort);
                fclose(fp_sort);
                getchar();getchar();
                break;
            
            case 2:
                //创建车辆链表并导入
                fp_car = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/车辆基本信息表.csv", "r");
                car_head = CarBasicInfo_CSV_Load(fp_car);
                fclose(fp_car);
                getchar();getchar();
                break;
                
            case 3:
                //创建订单链表并导入
                fp_order = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/租车订单信息表.csv", "r");
                car_head = RentOrderInfo_CSV_Load(car_head, fp_order);
                fclose(fp_order);
                getchar();getchar();
                break;
            
                
            //输出功能（4～6）
            case 4:
                //操作类型链表进行输出
                CarSortInfo_Print(sort_head);
                getchar();getchar();
                break;
                
            case 5:
                //操作车辆链表输出车辆信息
                CarBasicInfo_Print(car_head);
                getchar();getchar();
                break;
                
            case 6:
                //操作车辆链表输出订单信息
                RentOrderInfo_Print(car_head);
                getchar();getchar();
                break;
                
                
            //信息修改（7～9）
            case 7:
                //操作分类链表进行信息修改
                CarSortInfo_Edit(sort_head);
                getchar();getchar();
                break;
                
            case 8:
                //操作车辆链表进行车辆信息修改
                CarBasicInfo_Edit(car_head);
                getchar();getchar();
                break;
            
            case 9:
                //操作车辆链表进行订单信息修改
                RentOrderInfo_Edit(car_head);
                getchar();getchar();
                break;
                
                
            //删除功能（10～12）
            case 10:
                //操作类型链表进行删除
                CarSortInfo_Delete(sort_head);
                getchar();getchar();
                break;
                
            case 11:
                //操作车辆链表进行删除
                CarBasicInfo_Delete(car_head);
                getchar();getchar();
                break;
                
            case 12:
                //操作车辆链表删除订单
                RentOrderInfo_Delete(car_head);
                getchar();getchar();
                break;
            
                
            //增加数据（13～15）
            case 13:
                //操作类型链表进行增加
                CarSortInfo_Add(sort_head);
                getchar();getchar();
                break;
                
            case 14:
                //操作车辆链表进行增加
                CarBasicInfo_Add(car_head);
                getchar();getchar();
                break;
            
            case 15:
                //操作车辆链表增加订单
                RentOrderInfo_Add(car_head);
                getchar();getchar();
                break;
            
                           
            //查询数据（16～18）
            case 16:
                //查询车辆类型
                Comprehensive_Search_by_Type(car_head, sort_head);
                getchar();getchar();
                break;
                
            case 17:
                //查询车辆信息
                fp_car = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/车辆基本信息查询结果.csv", "r+");
                printf("请选择查找方式：\n1.准确查找（ 可选择三个指标 ）\n2.组合查找（ 不需要的内容请输入# ）\n");
                scanf("%d", &op);getchar();
                switch (op) {
                    case 1:
                        if (Car_Search(car_head, fp_car) == 1) {
                            printf("未找到！！！");
                        }
                        fclose(fp_car);
                        getchar();getchar();
                        break;
                    case 2:
                        //自由查找
                        Car_FreeSearch(car_head);
                        getchar();getchar();
                        break;
                    default:
                        printf("输入错误！！！⚠️\n");
                        fclose(fp_car);
                        getchar();getchar();
                        break;
                }
                break;
                
            case 18:
                //查询订单信息
                printf("请选择查找方式：\n1.依据客人信息\n2.依据车辆信息\n3.依据时间范围\n");
                scanf("%d", &op);getchar();
                switch (op) {
                    case 1:
                        if (Order_Search_Client(car_head, fp_car) == 1) {
                            printf("未找到！！！");
                        }
                        getchar();getchar();
                        break;
                    case 2:
                        if (Order_Search_Car(car_head, fp_car) == 1) {
                            printf("未找到！！！");
                        }
                        getchar();getchar();
                        break;
                    case 3:
                        if (Order_Search_Time(car_head, fp_car) == 1) {
                            printf("未找到！！！");
                        }
                        getchar();getchar();
                        break;
                    default:
                        printf("输入错误！！！⚠️\n");
                        getchar();getchar();
                        break;
                }
                break;
                
                
            //数据统计（19～21）
            case 19:
                //统计车辆类型
                Calculate_Sort(sort_head, car_head);
                getchar();getchar();
                break;
            case 20:
                printf("请选择统计方式：\n1.按类型统计利润\n2.按车辆统计利润\n");
                scanf("%d", &op);
                switch (op) {
                    case 1:
                        Calculate_Profit(sort_head, car_head);
                        getchar();getchar();
                        break;
                      
                    case 2:
                        Calculate_Carprofit(car_head);
                        getchar();getchar();
                        break;
                        
                    default:
                        printf("输入错误！！！⚠️\n");
                        getchar();getchar();
                        break;
                }
                break;
            case 21:
                Calculate_mvp(car_head);
                getchar();getchar();
                break;
                
               
            //导出数据（22～24）（已经完成调试）
            case 22:
                //操作类型链表导出数据
                fp_sort = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/车辆分类信息表.csv", "r+");
                CarSortInfo_CSV_Output(sort_head, fp_sort);
                fclose(fp_sort);
                getchar();getchar();
                break;
                
            case 23:
                //操作车辆信息导出数据
                fp_car = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/车辆基本信息表.csv", "r+");
                CarBasicInfo_CSV_Output(car_head, fp_car);
                fclose(fp_car);
                getchar();getchar();
                break;
                
            case 24:
                //操作订单链表导出数据
                fp_order = fopen("/Users/jiangshuqi/Documents/C语言程序文件夹/汽车租凭信息管理系统/汽车租凭信息管理系统/Data/租车订单信息表.csv", "r+");
                RentOrderInfo_CSV_Output(car_head, fp_order);
                fclose(fp_order);
                getchar();getchar();
                break;
                
                
            //退出系统
            case 0:
                printf("欢迎下次使用！！！🎉\n");
                getchar();getchar();
                break;
    
        }//end of switch
        
    }
    return 0;
}
