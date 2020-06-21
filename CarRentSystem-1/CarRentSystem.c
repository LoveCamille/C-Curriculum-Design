//
//  CarRentSystem.c
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/2/4.
//  Copyright © 2020 🌲. All rights reserved.
//

//预编译
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarRentSystem.h"

//函数定义
//画统计图（已经没有BUG🛫️）
void draw(float p) {
    int q = p/20;
    while (q) {
        printf("🀫");
        q--;
    }
    printf(" %.2f元", p);
    printf("\n\n");
}

//展示菜单（已经没有BUG🛫️）
void Show_Menu(void) {
    printf("\n                                      汽车租凭信息管理系统🖥\n\n");
    printf(" 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 \n");
    printf("🚘                                                                                           🚘\n");
    printf("🚘       数据加载功能如下♻️  ( 1⃣️ ～ 3⃣️ )                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │    1.加载车辆类型🏍     │      │    2.加载车辆信息🚙    │       │    3.加载订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据查看功能如下👀  ( 4⃣️ ～ 6⃣️ )                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │    4.查看车辆类型🏍     │      │    5.查看车辆信息🚙    │       │    6.查看订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据修改功能如下📝  ( 7⃣️ ～ 9⃣️ )                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │    7.修改车辆类型🏍     │      │    8.修改车辆信息🚙    │       │    9.修改订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据删除功能如下⚠️  (1⃣️0⃣️～1⃣️2⃣️)                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │   10.删除车辆类型🏍     │      │   11.删除车辆信息🚙    │       │   12.删除订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据增加功能如下➕  (1⃣️3⃣️～1⃣️5⃣️)                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │   13.增加车辆类型🏍     │      │   14.增加车辆信息🚙    │       │   15.增加订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据查询功能如下🔍  (1⃣️6⃣️～1⃣️8⃣️)                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │   16.查询车辆类型🏍     │      │   17.查询车辆信息🚙    │       │   18.查询订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据统计功能如下🧮  (1⃣️9⃣️～2⃣️1⃣️)                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │   19.统计车辆类型🏍     │      │   20.统计车辆信息🚙    │       │   21.统计订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘       数据导出功能如下⌚️  (2⃣️2⃣️～2⃣️4⃣️)                                                       🚘\n");
    printf("🚘   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘  │   22.导出车辆类型🏍     │      │   23.导出车辆信息🚙    │       │   24.导出订单信息🚚    │   🚘\n");
    printf("🚘   ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣        ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘                                                                                           🚘\n");
    printf("🚘                   Created by  🌲 .                             ＿＿＿＿＿＿＿＿＿＿＿＿＿＿    🚘\n");
    printf("🚘                   Copyright © 2020  🌲 .                      │    0.退出租车系统♿️     │   🚘\n");
    printf("🚘                   All rights reserved.                         ￣￣￣￣￣￣￣￣￣￣￣￣￣￣    🚘\n");
    printf("🚘                                                                                           🚘\n");
    printf(" 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 🚘 \n");
}

//输出车辆类型信息（已经没有BUG🛫️）
void CarSortInfo_Print(Sort_Node * sort_head) {
    
    if (sort_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    Sort_Node * p;//遍历指针
    p = sort_head->Next_Sort;//指向第一个节点
    
    while (p != NULL) {
        
        printf("类型编码：%2d\t，"\
               "类型名称：%s\t，"\
               "该类型库存数量：%2d  。\n",
               p->Sort.Sort_Num,
               p->Sort.Sort_Name,
               p->Sort.Stock_Num);
        
        p = p->Next_Sort;
    }
    printf("车辆 分类信息 遍历结果如上⬆️\n\n");
    return ;
}

//输出车辆基本信息（已经没有BUG🛫️）
void CarBasicInfo_Print(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    Car_Node * p;//遍历指针
    p = car_head->Next_Info;//指向第一个节点
    
    while (p != NULL) {
        
        printf("车辆编号：%2d\t，"\
               "车牌号：%s\t，"\
               "类型编码：%2d  ，"\
               "车辆名称：%s，"\
               "排挡方式：%s，"\
               "每日租金：%.2f¥，"\
               "出租状态：%c 。\n",
               p->Info.Serial_Num,
               p->Info.Plate_Num,
               p->Info.Type_Num,
               p->Info.Name,
               p->Info.Gear_Mode,
               p->Info.Daily_Rent,
               p->Info.Rental_Status);
        
        p = p->Next_Info;
    }
    printf("车辆 基本信息 遍历结果如上⬆️\n\n");
    return ;
}

//输出订单信息（已经没有BUG🛫️）
void RentOrderInfo_Print(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    Car_Node * p;//遍历指针
    p = car_head->Next_Info;//指向第一个节点
    
    while (p != NULL) {
        
        printf("车辆编号为%2d的相关订单如下：⬇️\n",p->Info.Serial_Num);
        
        if (p->Order == NULL) {
            printf("暂无相关订单！！！⚠️\n");
        }
        
        else{
            Order_Node * q;
            q = p->Order;
        while (q != NULL) {
            
            printf("订单编号：%s，"\
            "身份证号：%s，"\
            "客人姓名：%s，"\
            "手机号码：%s，"\
            "租用车辆编号：%d，"\
            "取车时间：%s，"\
            "预约还车时间：%s，"\
            "押金：%.2f¥，"\
            "实际还车时间：%s，"\
            "应缴费用：%.2f¥，"\
            "实缴费用：%.2f¥。\n",
            q->OrderInfo.Order_Num,
            q->OrderInfo.ID_Num,
            q->OrderInfo.Client_Nam,
            q->OrderInfo.Phone_Num,
            q->OrderInfo.Rent_Serial_Num,
            q->OrderInfo.Pick_Time,
            q->OrderInfo.Promised_Ret_Time,
            q->OrderInfo.Deposit,
            q->OrderInfo.Actual_Ret_Time,
            q->OrderInfo.Promised_Fee,
            q->OrderInfo.Actual_Fee);
            
            q = q->Next_Order;
        }
    
        p = p->Next_Info;
        }
        p = p->Next_Info;
    }
    printf("车辆 租用订单 遍历结果如上⬆️\n\n");
    return ;
}

//车辆类型添加（已经没有BUG🛫️）
void CarSortInfo_Add(Sort_Node * sort_head) {
    
    if (sort_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    int Stock_Num;
    char Sort_Name[20];
    
    printf("请输入新的类型名（ char Sort_Name[20] ）：\n");
    scanf("%s",Sort_Name);
    printf("请输入新类型的库存数量（ int Stock_Num ）：\n");
    scanf("%d", &Stock_Num);
    
    Sort_Node * p;
    p = sort_head->Next_Sort;//指向第一个节点
    
    while (p->Next_Sort != NULL) {
        p = p->Next_Sort;
    }//移动到最后一个节点
    
    p->Next_Sort = (Sort_Node * )malloc(sizeof(Sort_Node));//分配新节点的内存空间
    
    p->Next_Sort->Sort.Sort_Num = p->Sort.Sort_Num + 1;//类型编码不断累加
    strcpy(p->Next_Sort->Sort.Sort_Name, Sort_Name);//类型名字赋值
    p->Next_Sort->Sort.Stock_Num = Stock_Num;//库存数量赋值
    p->Next_Sort->Next_Sort = NULL;//新节点连接的下个车辆类型节点赋值为NULL
    
    printf("增加成功！！！\n");
    return ;
}

//车辆类型删除（已经没有BUG🛫️）
void CarSortInfo_Delete(Sort_Node * sort_head) {
    
    if (sort_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    int op;
    int Sort_Num;
    char Sort_Name[20];
    
    printf("请选择删除方式：\n1.依据类型名删除（ char Sort_Name[20] ）\n2.依据类型编码删除（ char Sort_Num ）\n");
    scanf("%d", &op);

    Sort_Node * p;
    p = sort_head;//指向头节点
    
    switch (op) {
            
        case 1:
            printf("请输入类型名（ char Sort_Name[20] ）：\n");
            scanf("%s",Sort_Name);
            
            while (strcmp(p->Next_Sort->Sort.Sort_Name, Sort_Name) != 0 && p->Next_Sort->Next_Sort != NULL) {
                p = p->Next_Sort;
            }
            
            if (strcmp(p->Next_Sort->Sort.Sort_Name, Sort_Name) != 0 && p->Next_Sort->Next_Sort == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                p->Next_Sort = p->Next_Sort->Next_Sort;
            }
            
            printf("删除成功！！！\n");
            break;
         
        case 2:
            getchar();
            printf("请输入类型编码（ char Sort_Num ）：\n");
            scanf("%d", &Sort_Num);
            while (p->Next_Sort->Sort.Sort_Num != Sort_Num != 0 && p->Next_Sort->Next_Sort != NULL) {
                p = p->Next_Sort;
            }
            
            if (p->Next_Sort->Sort.Sort_Num != Sort_Num && p->Next_Sort->Next_Sort == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                p->Next_Sort = p->Next_Sort->Next_Sort;
            }
            
            printf("删除成功！！！\n");
            break;
            
        default:
            printf("输入错误！！！⚠️\n");
            break;
    }
    return ;
}

//车辆类型修改（已经没有BUG🛫️）
void CarSortInfo_Edit(Sort_Node * sort_head) {
    
    if (sort_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    int op;
    //定位参数
    int Sort_Num;
    char Sort_Name[20];
    //修改参数
    int Stock_Num;              //该类型库存数量
    char New_Name[20];          //类型名称
    
    printf("请选择修改方式：\n1.依据类型名修改（ char Sort_Name[20] ）\n2.依据类型编码修改（ char Sort_Num ）\n");
    scanf("%d", &op);
    
    Sort_Node * p;
    p = sort_head;//指向头节点
    
    switch (op) {
            
        case 1:
            
            printf("请输入类型名（ char Sort_Name[20] ）：\n");
            scanf("%s",Sort_Name);
            
            while (strcmp(p->Next_Sort->Sort.Sort_Name, Sort_Name) != 0 && p->Next_Sort->Next_Sort != NULL) {
                p = p->Next_Sort;
            }
            
            if (strcmp(p->Next_Sort->Sort.Sort_Name, Sort_Name) != 0 && p->Next_Sort->Next_Sort == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                
                printf("请输入新的类型名（ char Sort_Name[20] ）：\n");
                scanf("%s",New_Name);
                printf("请输入更新后的库存数量（ int Stock_Num ）：\n");
                scanf("%d", &Stock_Num);
                
                strcpy(p->Next_Sort->Sort.Sort_Name, New_Name);//更改类型名称
                p->Next_Sort->Sort.Stock_Num = Stock_Num;//修改库存数量
            }
            
            printf("修改成功！！！\n");
            break;
         
        case 2:
            
            getchar();
            printf("请输入类型编码（ char Sort_Num ）：\n");
            scanf("%d", &Sort_Num);
            
            while (p->Next_Sort->Sort.Sort_Num != Sort_Num != 0 && p->Next_Sort->Next_Sort != NULL) {
                p = p->Next_Sort;
            }
            
            if (p->Next_Sort->Sort.Sort_Num != Sort_Num && p->Next_Sort->Next_Sort == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                
                printf("请输入新的类型名（ char Sort_Name[20] ）：\n");
                scanf("%s",New_Name);
                printf("请输入更新后的库存数量（ int Stock_Num ）：\n");
                scanf("%d", &Stock_Num);
                
                strcpy(p->Next_Sort->Sort.Sort_Name, New_Name);//更改类型名称
                p->Next_Sort->Sort.Stock_Num = Stock_Num;//修改库存数量
            }
            
            printf("修改成功！！！\n");
            break;
            
        default:
            printf("输入错误！！！⚠️\n");
            break;
    }
    return ;
}

//车辆基本信息添加（已经没有BUG🛫️）
void CarBasicInfo_Add(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    //新增信息
    char Plate_Num[10];
    int Type_Num;
    char Name[20];
    char Gear_Mode[12];
    float Daily_Rent;
    char Rental_Status;
    
    printf("请输入新车的车牌号（ char Plate_Num[10] ）：\n");
    scanf("%s", Plate_Num);
    printf("请输入新车的类型编码（ char Type_Num ）：\n");
    scanf("%d", &Type_Num);
    printf("请输入新车的车辆名称（ char Name[20] ）：\n");
    scanf("%s", Name);
    printf("请输入新车的排挡方式（ char Gear_Mode[12] ）：\n");
    scanf("%s", Gear_Mode);
    printf("请输入新车的每日租金（ float Daily_Rent ）：\n");
    scanf("%f", &Daily_Rent);
    getchar();//吸收回车
    printf("请输入新车的出租状态（ char Rental_Status ）：\n");
    scanf("%c", &Rental_Status);
    
    Car_Node * p;
    p = car_head->Next_Info;//指向第一个节点
    
    while (p->Next_Info != NULL) {
        p = p->Next_Info;
    }//移动到最后一个节点
    
    p->Next_Info = (Car_Node * )malloc(sizeof(Car_Node));//分配新节点的内存空间
    
    p->Next_Info->Info.Serial_Num = p->Info.Serial_Num + 1;//车辆编号不断累加
    strcpy(p->Next_Info->Info.Plate_Num, Plate_Num);
    p->Next_Info->Info.Type_Num = Type_Num;
    strcpy(p->Next_Info->Info.Name, Name);
    strcpy(p->Next_Info->Info.Gear_Mode, Gear_Mode);
    p->Next_Info->Info.Daily_Rent = Daily_Rent;
    p->Next_Info->Info.Rental_Status = Rental_Status;
    p->Next_Info->Next_Info = NULL;//新节点连接的下个车辆信息节点赋值为NULL
    
    printf("增加成功！！！\n");
    return ;
}

//车辆基本信息删除（已经没有BUG🛫️）
void CarBasicInfo_Delete(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    int op;
    int Serial_Num;
    char Plate_Num[10];
    char Name[20];
       
    printf("请选择删除方式：\n1.依据车辆编号删除（ int Serial_Num ）\n2.依据车牌号删除（ char Plate_Num[10] ）\n3.依据车辆名称删除（ char Name[20] ）\n");
    scanf("%d", &op);
    
    Car_Node * p;
    p = car_head;
    
    switch (op) {
            
        case 1:
            printf("请输入车辆编号（ int Serial_Num ）：\n");
            scanf("%d", &Serial_Num);
            
            while (p->Next_Info->Info.Serial_Num != Serial_Num && p->Next_Info->Next_Info != NULL) {
                p = p->Next_Info;
            }
            
            if (p->Next_Info->Info.Serial_Num != Serial_Num && p->Next_Info->Next_Info == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                p->Next_Info = p->Next_Info->Next_Info;
            }
            
            printf("删除成功！！！\n");
            break;
         
        case 2:
            printf("请输入车牌号（ char Plate_Num[10] ）：\n");
            scanf("%s", Plate_Num);
            
            while (strcmp(p->Next_Info->Info.Plate_Num, Plate_Num) != 0 && p->Next_Info->Next_Info != NULL) {
                p = p->Next_Info;
            }
            
            if (strcmp(p->Next_Info->Info.Plate_Num, Plate_Num) != 0 && p->Next_Info->Next_Info == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                p->Next_Info = p->Next_Info->Next_Info;
            }
            
            printf("删除成功！！！\n");
            break;
            
        case 3:
            printf("请输入车辆名称（ char Name[20] ）：\n");
            scanf("%s", Name);
            
            while (strcmp(p->Next_Info->Info.Name, Name) != 0 && p->Next_Info->Next_Info != NULL) {
                p = p->Next_Info;
            }
            
            if (strcmp(p->Next_Info->Info.Name, Name) != 0 && p->Next_Info->Next_Info == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                p->Next_Info = p->Next_Info->Next_Info;
            }
            
            printf("删除成功！！！\n");
            break;
            
        default:
            printf("输入错误！！！⚠️\n");
            break;
    }
    return ;
}

//车辆基本信息修改（已经没有BUG🛫️）
void CarBasicInfo_Edit(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    int op;
    //定位参数
    int Serial_Num;
    char Plate_Num[10];
    char Name[20];
    //修改参数
    char New_Plate_Num[10];     //车牌号
    int Type_Num;              //车辆类型编码
    char New_Name[20];          //车辆名称
    char Gear_Mode[12];         //排挡方式
    float Daily_Rent;           //每日租金
    char Rental_Status;         //出租状态
    
    printf("请选择修改方式：\n1.依据车辆编号修改（ int Serial_Num ）\n2.依据车牌号修改（ char Plate_Num[10] ）\n3.依据车辆名称修改（ char Name[20] ）\n");
    scanf("%d", &op);
    
    Car_Node * p;
    p = car_head;//指向头节点
    
    switch (op) {
            
        case 1:
            
            printf("请输入车辆编号（ int Serial_Num ）：\n");
            scanf("%d", &Serial_Num);
            
            while (p->Next_Info->Info.Serial_Num != Serial_Num && p->Next_Info->Next_Info != NULL) {
                p = p->Next_Info;
            }
            
            if (p->Next_Info->Info.Serial_Num != Serial_Num && p->Next_Info->Next_Info == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                printf("请选择你要修改的车辆基本信息：\n");
                printf("1.车牌号（ char Plate_Num[10] ) \n");
                printf("2.车辆类型编码（ char Type_Num ）\n");
                printf("3.车辆名称（ char Name[20] ）\n");
                printf("4.排挡方式（ char Gear_Mode[10] ）\n");
                printf("5.每日租金（ float Daily_Rent ）\n");
                printf("6.出租状态（ char Rental_Status ）\n");
                int choice;
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        printf("请输入新的车牌号（ char Plate_Num[10] ) ：\n");
                        scanf("%s", New_Plate_Num);
                        strcpy(p->Next_Info->Info.Plate_Num, New_Plate_Num);
                        break;
                    case 2:
                        printf("请输入新的车辆类型编码（ char Type_Num ）：\n");
                        scanf("%d", &Type_Num);
                        p->Next_Info->Info.Type_Num = Type_Num;
                        break;
                    case 3:
                        printf("请输入新的车辆名称（ char Name[20] ）：\n");
                        scanf("%s", New_Name);
                        strcpy(p->Next_Info->Info.Name, New_Name);
                        break;
                    case 4:
                        printf("请输入新的排挡方式（ char Gear_Mode[10] ）：\n");
                        scanf("%s", Gear_Mode);
                        strcpy(p->Next_Info->Info.Gear_Mode, Gear_Mode);
                        break;
                    case 5:
                        printf("请输入新的每日租金（ float Daily_Rent ）：\n");
                        scanf("%f", &Daily_Rent);
                        p->Next_Info->Info.Daily_Rent = Daily_Rent;
                        break;
                    case 6:
                        printf("请输入新的出租状态（ char Rental_Status ）：\n");
                        scanf("%c", &Rental_Status);
                        p->Next_Info->Info.Rental_Status = Rental_Status;
                        break;
                        
                    default:
                        printf("输入错误！！！⚠️\n");
                        break;
            }
            }
            printf("修改成功！！！\n");
            break;
            
        case 2:
            
            printf("请输入车牌号（ char Plate_Num[10] ）：\n");
            scanf("%s", Plate_Num);
            
            while (strcmp(p->Next_Info->Info.Plate_Num, Plate_Num) != 0 && p->Next_Info->Next_Info != NULL) {
                p = p->Next_Info;
            }
            
            if (strcmp(p->Next_Info->Info.Plate_Num, Plate_Num) != 0 && p->Next_Info->Next_Info == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                printf("请选择你要修改的车辆基本信息：\n");
                printf("1.车牌号（ char Plate_Num[10] ) \n");
                printf("2.车辆类型编码（ char Type_Num ）\n");
                printf("3.车辆名称（ char Name[20] ）\n");
                printf("4.排挡方式（ char Gear_Mode[10] ）\n");
                printf("5.每日租金（ float Daily_Rent ）\n");
                printf("6.出租状态（ char Rental_Status ）\n");
                int choice;
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        printf("请输入新的车牌号（ char Plate_Num[10] ) ：\n");
                        scanf("%s", New_Plate_Num);
                        strcpy(p->Next_Info->Info.Plate_Num, New_Plate_Num);
                        break;
                    case 2:
                        printf("请输入新的车辆类型编码（ char Type_Num ）：\n");
                        scanf("%d", &Type_Num);
                        p->Next_Info->Info.Type_Num = Type_Num;
                        break;
                    case 3:
                        printf("请输入新的车辆名称（ char Name[20] ）：\n");
                        scanf("%s", New_Name);
                        strcpy(p->Next_Info->Info.Name, New_Name);
                        break;
                    case 4:
                        printf("请输入新的排挡方式（ char Gear_Mode[10] ）：\n");
                        scanf("%s", Gear_Mode);
                        strcpy(p->Next_Info->Info.Gear_Mode, Gear_Mode);
                        break;
                    case 5:
                        printf("请输入新的每日租金（ float Daily_Rent ）：\n");
                        scanf("%f", &Daily_Rent);
                        p->Next_Info->Info.Daily_Rent = Daily_Rent;
                        break;
                    case 6:
                        printf("请输入新的出租状态（ char Rental_Status ）：\n");
                        scanf("%c", &Rental_Status);
                        p->Next_Info->Info.Rental_Status = Rental_Status;
                        break;
                        
                    default:
                        printf("输入错误！！！⚠️\n");
                        break;
            }
            }
            printf("修改成功！！！\n");
            break;
            
        case 3:
            
            printf("请输入车辆名称（ char Name[20] ）：\n");
            scanf("%s", Name);
            
            while (strcmp(p->Next_Info->Info.Name, Name) != 0 && p->Next_Info->Next_Info != NULL) {
                p = p->Next_Info;
            }
            
            if (strcmp(p->Next_Info->Info.Name, Name) != 0 && p->Next_Info->Next_Info == NULL) {
                printf("未找到该车辆类型！！！⚠️\n");
                return ;
            }
            
            else{
                printf("请选择你要修改的车辆基本信息：\n");
                printf("1.车牌号（ char Plate_Num[10] ) \n");
                printf("2.车辆类型编码（ char Type_Num ）\n");
                printf("3.车辆名称（ char Name[20] ）\n");
                printf("4.排挡方式（ char Gear_Mode[10] ）\n");
                printf("5.每日租金（ float Daily_Rent ）\n");
                printf("6.出租状态（ char Rental_Status ）\n");
                int choice;
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        printf("请输入新的车牌号（ char Plate_Num[10] ) ：\n");
                        scanf("%s", New_Plate_Num);
                        strcpy(p->Next_Info->Info.Plate_Num, New_Plate_Num);
                        break;
                    case 2:
                        printf("请输入新的车辆类型编码（ char Type_Num ）：\n");
                        scanf("%d", &Type_Num);
                        p->Next_Info->Info.Type_Num = Type_Num;
                        break;
                    case 3:
                        printf("请输入新的车辆名称（ char Name[20] ）：\n");
                        scanf("%s", New_Name);
                        strcpy(p->Next_Info->Info.Name, New_Name);
                        break;
                    case 4:
                        printf("请输入新的排挡方式（ char Gear_Mode[10] ）：\n");
                        scanf("%s", Gear_Mode);
                        strcpy(p->Next_Info->Info.Gear_Mode, Gear_Mode);
                        break;
                    case 5:
                        printf("请输入新的每日租金（ float Daily_Rent ）：\n");
                        scanf("%f", &Daily_Rent);
                        p->Next_Info->Info.Daily_Rent = Daily_Rent;
                        break;
                    case 6:
                        printf("请输入新的出租状态（ char Rental_Status ）：\n");
                        scanf("%c", &Rental_Status);
                        p->Next_Info->Info.Rental_Status = Rental_Status;
                        break;
                        
                    default:
                        printf("输入错误！！！⚠️\n");
                        break;
                }
            }
            printf("修改成功！！！\n");
            break;
            
        default:
            printf("输入错误！！！⚠️\n");
            break;
    }
    return ;
}

//增加租车订单（已经没有BUG🛫️）
void RentOrderInfo_Add(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    //查找对应车辆使用的变量
    Car_Node * p;
    p = car_head;
    int Serial_Num;
    printf("请输入与该订单相关车辆的车辆编号（ int Serial_Num ）：\n");
    scanf("%d", &Serial_Num);
    
    //新订单的参数
    Order_Node * pp;
    Order_Node * qq;
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
    
    while (p->Next_Info->Info.Serial_Num != Serial_Num && p->Next_Info->Next_Info != NULL) {
        p = p->Next_Info;
    }
    
    if (p->Next_Info->Info.Serial_Num != Serial_Num && p->Next_Info->Next_Info == NULL) {
        printf("未找到该车辆类型！！！⚠️\n");
        return ;
    }
    
    else{
        
        pp = p->Next_Info->Order;
        
        if (pp == NULL) {
            pp = (Order_Node * )malloc(sizeof(Order_Node));//分配内存空间
            
            printf("请输入新订单的编号（ char Order_Num[20] ）：\n");
            scanf("%s", Order_Num);
            strcpy(pp->OrderInfo.Order_Num, Order_Num);
            printf("请输入新订单的客人身份证号（ char ID_Num[20] ）：\n");
            scanf("%s", ID_Num);
            strcpy(pp->OrderInfo.ID_Num, ID_Num);
            printf("请输入新订单的客人姓名（ char Client_Nam[20] ）：\n");
            scanf("%s", Client_Nam);
            strcpy(pp->OrderInfo.Client_Nam, Client_Nam);
            printf("请输入新订单的客人手机号（ char Phone_Num[20] ）：\n");
            scanf("%s", Phone_Num);
            strcpy(pp->OrderInfo.Phone_Num, Phone_Num);
            printf("请输入新订单租用的车辆编号（ char Rent_Serial_Num[4] ）：\n");
            scanf("%d", &Rent_Serial_Num);
            pp->OrderInfo.Rent_Serial_Num = Rent_Serial_Num;
            printf("请输入新订单的取车时间（ char Pick_Time[18] ）：\n");
            scanf("%s", Pick_Time);
            strcpy(pp->OrderInfo.Pick_Time, Pick_Time);
            printf("请输入新订单的预约还车时间（ char Promised_Ret_Time[18] ）：\n");
            scanf("%s", Promised_Ret_Time);
            strcpy(pp->OrderInfo.Promised_Ret_Time, Promised_Ret_Time);
            printf("请输入新订单的押金（ float Deposit ）：\n");
            scanf("%f", &Deposit);
            pp->OrderInfo.Deposit = Deposit;
            printf("请输入新订单的实际还车时间（ char Actual_Ret_Time[18] ）：\n");
            scanf("%s", Actual_Ret_Time);
            strcpy(pp->OrderInfo.Actual_Ret_Time, Actual_Ret_Time);
            printf("请输入新订单的应缴费用（ float Promised_Fee ）\n");
            scanf("%f", &Promised_Fee);
            pp->OrderInfo.Promised_Fee = Promised_Fee;
            printf("请输入新订单的实缴费用（ float Actual_Fee ）\n");
            scanf("%f", &Actual_Fee);
            pp->OrderInfo.Actual_Fee = Actual_Fee;
            
            p->Next_Info->Order = pp;
            pp->Next_Order = NULL;
        }
        
        else{
            
        qq = p->Next_Info->Order;
            
        while (qq->Next_Order != NULL) {
            qq = qq->Next_Order;
        }//移动到最后一个订单节点
        
        pp = (Order_Node * )malloc(sizeof(Order_Node));//分配内存空间
        
        printf("请输入新订单的编号（ char Order_Num[20] ）：\n");
        scanf("%s", Order_Num);
        strcpy(pp->OrderInfo.Order_Num, Order_Num);
        printf("请输入新订单的客人身份证号（ char ID_Num[20] ）：\n");
        scanf("%s", ID_Num);
        strcpy(pp->OrderInfo.ID_Num, ID_Num);
        printf("请输入新订单的客人姓名（ char Client_Nam[20] ）：\n");
        scanf("%s", Client_Nam);
        strcpy(pp->OrderInfo.Client_Nam, Client_Nam);
        printf("请输入新订单的客人手机号（ char Phone_Num[20] ）：\n");
        scanf("%s", Phone_Num);
        strcpy(pp->OrderInfo.Phone_Num, Phone_Num);
        printf("请输入新订单租用的车辆编号（ char Rent_Serial_Num[4] ）：\n");
        scanf("%d", &Rent_Serial_Num);
        pp->OrderInfo.Rent_Serial_Num = Rent_Serial_Num;
        printf("请输入新订单的取车时间（ char Pick_Time[18] ）：\n");
        scanf("%s", Pick_Time);
        strcpy(pp->OrderInfo.Pick_Time, Pick_Time);
        printf("请输入新订单的预约还车时间（ char Promised_Ret_Time[18] ）：\n");
        scanf("%s", Promised_Ret_Time);
        strcpy(pp->OrderInfo.Pick_Time, Promised_Ret_Time);
        printf("请输入新订单的押金（ float Deposit ）：\n");
        scanf("%f", &Deposit);
        pp->OrderInfo.Deposit = Deposit;
        printf("请输入新订单的实际还车时间（ char Actual_Ret_Time[18] ）：\n");
        scanf("%s", Actual_Ret_Time);
        strcpy(pp->OrderInfo.Actual_Ret_Time, Actual_Ret_Time);
        printf("请输入新订单的应缴费用（ float Promised_Fee ）\n");
        scanf("%f", &Promised_Fee);
        pp->OrderInfo.Promised_Fee = Promised_Fee;
        printf("请输入新订单的实缴费用（ float Actual_Fee ）\n");
        scanf("%f", &Actual_Fee);
        pp->OrderInfo.Actual_Fee = Actual_Fee;
        pp->Next_Order = NULL;
            
        qq->Next_Order = pp;
        }
    }
    return ;
}

//删除租车订单（已经没有BUG🛫️）
void RentOrderInfo_Delete(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    char Order_Num[20];
    printf("请输入要删除订单的编号（ char Order_Num[20] ）：\n");
    scanf("%s", Order_Num);
    Car_Node *p = car_head->Next_Info;
    Order_Node * pp = (Order_Node * )malloc(sizeof(Order_Node));
    
    while (p != NULL) {
        
        pp = p->Order;
        if (pp == NULL) {
            p = p->Next_Info;
            continue;
        }
        
        if (!strcmp(pp->OrderInfo.Order_Num, Order_Num)) {
            p->Order = NULL;
            printf("删除成功！！！\n");
            return;
        }//第一个如果就找到了节点就直接结束
        
        else{//第一个订单节点不是
            
            while (pp->Next_Order != NULL && strcmp(pp->Next_Order->OrderInfo.Order_Num, Order_Num) != 0) {
                pp = pp->Next_Order;
            }
        
            if (pp->Next_Order != NULL) {
                pp->Next_Order = pp->Next_Order->Next_Order;
                printf("修改成功！！！\n");
                return;
            }
            
            p = p->Next_Info;
        }
    }
    printf("未找到该订单！！！⚠️\n");
    return ;
}

//修改租车订单（已经没有BUG🛫️）
void RentOrderInfo_Edit(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return ;
    }
    
    char New_Order_Num[20];     //订单编号
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
    char Order_Num[20];
    
    printf("请输入要修改订单的编号（ char Order_Num[20] ）：\n");
    scanf("%s", Order_Num);
    Car_Node *p = car_head->Next_Info;
    Order_Node * pp = (Order_Node * )malloc(sizeof(Order_Node));
    int op = 0;
    
    while (p != NULL) {
        
        pp = p->Order;
        if (pp == NULL) {
            p = p->Next_Info;
            continue;
        }
        
        if (!strcmp(pp->OrderInfo.Order_Num, Order_Num)) {
            
            printf("请输⼊需要编辑的订单内容：\n1.订单编号\n 2.身份证号\n 3.客⼈姓名\n 4.⼿机号码\n 5.租⽤⻋辆编号\n 6.取⻋时间\n 7.预约还⻋时间\n 8.押⾦\n 9.实际还⻋时间\n 10.应缴费⽤\n 11.实缴费⽤\n 0.终止修改\n");
            while (scanf("%d", &op)&&op != 0) {
                switch (op) {
                    
                    case 1:
                        printf("请输入新订单的编号（ char Order_Num[20] ）：\n");
                        scanf("%s", New_Order_Num);
                        strcpy(pp->OrderInfo.Order_Num, New_Order_Num);
                        break;
                    case 2:
                        printf("请输入新订单的客人身份证号（ char ID_Num[20] ）：\n");
                        scanf("%s", ID_Num);
                        strcpy(pp->OrderInfo.ID_Num, ID_Num);
                        break;
                    case 3:
                        printf("请输入新订单的客人姓名（ char Client_Nam[20] ）：\n");
                        scanf("%s", Client_Nam);
                        strcpy(pp->OrderInfo.Client_Nam, Client_Nam);
                        break;
                    case 4:
                        printf("请输入新订单的客人手机号（ char Phone_Num[20] ）：\n");
                        scanf("%s", Phone_Num);
                        strcpy(pp->OrderInfo.Phone_Num, Phone_Num);
                        break;
                    case 5:
                        printf("请输入新订单租用的车辆编号（ char Rent_Serial_Num[4] ）：\n");
                        scanf("%d", &Rent_Serial_Num);
                        pp->OrderInfo.Rent_Serial_Num = Rent_Serial_Num;
                        break;
                    case 6:
                        printf("请输入新订单的取车时间（ char Pick_Time[18] ）：\n");
                        scanf("%s", Pick_Time);
                        strcpy(pp->OrderInfo.Pick_Time, Pick_Time);
                        break;
                    case 7:
                        printf("请输入新订单的预约还车时间（ char Promised_Ret_Time[18] ）：\n");
                        scanf("%s", Promised_Ret_Time);
                        strcpy(pp->OrderInfo.Pick_Time, Promised_Ret_Time);
                        break;
                    case 8:
                        printf("请输入新订单的押金（ float Deposit ）：\n");
                        scanf("%f", &Deposit);
                        pp->OrderInfo.Deposit = Deposit;
                        break;
                    case 9:
                        printf("请输入新订单的实际还车时间（ char Actual_Ret_Time[18] ）：\n");
                        scanf("%s", Actual_Ret_Time);
                        strcpy(pp->OrderInfo.Actual_Ret_Time, Actual_Ret_Time);
                        break;
                    case 10:
                        printf("请输入新订单的应缴费用（ float Promised_Fee ）\n");
                        scanf("%f", &Promised_Fee);
                        pp->OrderInfo.Promised_Fee = Promised_Fee;
                        break;
                    case 11:
                        printf("请输入新订单的实缴费用（ float Actual_Fee ）\n");
                        scanf("%f", &Actual_Fee);
                        pp->OrderInfo.Actual_Fee = Actual_Fee;
                        break;
                    default:
                        printf("输入错误！！！⚠️\n");
                        break;
                }
                printf("请输⼊需要编辑的订单内容：\n1.订单编号\n 2.身份证号\n 3.客⼈姓名\n 4.⼿机号码\n 5.租⽤⻋辆编号\n 6.取⻋时间\n 7.预约还⻋时间\n 8.押⾦\n 9.实际还⻋时间\n 10.应缴费⽤\n 11.实缴费⽤\n 0.终止修改\n");
            }
            printf("修改成功！！！\n");
            return;
        }//第一个如果就找到了节点就直接结束
        
        else{//第一个订单节点不是
            
            while (pp->Next_Order != NULL && strcmp(pp->Next_Order->OrderInfo.Order_Num, Order_Num) != 0) {
                pp = pp->Next_Order;
            }
        
            if (pp->Next_Order != NULL) {
                printf("请输⼊需要编辑的订单内容：\n1.订单编号\n 2.身份证号\n 3.客⼈姓名\n 4.⼿机号码\n 5.租⽤⻋辆编号\n 6.取⻋时间\n 7.预约还⻋时间\n 8.押⾦\n 9.实际还⻋时间\n 10.应缴费⽤\n 11.实缴费⽤\n 0.终止修改\n");
                while (scanf("%d", &op)&&op != 0) {
                    
                    switch (op) {
                        
                        case 1:
                            printf("请输入新订单的编号（ char Order_Num[20] ）：\n");
                            scanf("%s", New_Order_Num);
                            strcpy(pp->Next_Order->OrderInfo.Order_Num, New_Order_Num);
                            break;
                        case 2:
                            printf("请输入新订单的客人身份证号（ char ID_Num[20] ）：\n");
                            scanf("%s", ID_Num);
                            strcpy(pp->Next_Order->OrderInfo.ID_Num, ID_Num);
                            break;
                        case 3:
                            printf("请输入新订单的客人姓名（ char Client_Nam[20] ）：\n");
                            scanf("%s", Client_Nam);
                            strcpy(pp->Next_Order->OrderInfo.Client_Nam, Client_Nam);
                            break;
                        case 4:
                            printf("请输入新订单的客人手机号（ char Phone_Num[20] ）：\n");
                            scanf("%s", Phone_Num);
                            strcpy(pp->Next_Order->OrderInfo.Phone_Num, Phone_Num);
                            break;
                        case 5:
                            printf("请输入新订单租用的车辆编号（ char Rent_Serial_Num[4] ）：\n");
                            scanf("%d", &Rent_Serial_Num);
                            pp->Next_Order->OrderInfo.Rent_Serial_Num = Rent_Serial_Num;
                            break;
                        case 6:
                            printf("请输入新订单的取车时间（ char Pick_Time[18] ）：\n");
                            scanf("%s", Pick_Time);
                            strcpy(pp->Next_Order->OrderInfo.Pick_Time, Pick_Time);
                            break;
                        case 7:
                            printf("请输入新订单的预约还车时间（ char Promised_Ret_Time[18] ）：\n");
                            scanf("%s", Promised_Ret_Time);
                            strcpy(pp->Next_Order->OrderInfo.Pick_Time, Promised_Ret_Time);
                            break;
                        case 8:
                            printf("请输入新订单的押金（ float Deposit ）：\n");
                            scanf("%f", &Deposit);
                            pp->Next_Order->OrderInfo.Deposit = Deposit;
                            break;
                        case 9:
                            printf("请输入新订单的实际还车时间（ char Actual_Ret_Time[18] ）：\n");
                            scanf("%s", Actual_Ret_Time);
                            strcpy(pp->Next_Order->OrderInfo.Actual_Ret_Time, Actual_Ret_Time);
                            break;
                        case 10:
                            printf("请输入新订单的应缴费用（ float Promised_Fee ）\n");
                            scanf("%f", &Promised_Fee);
                            pp->Next_Order->OrderInfo.Promised_Fee = Promised_Fee;
                            break;
                        case 11:
                            printf("请输入新订单的实缴费用（ float Actual_Fee ）\n");
                            scanf("%f", &Actual_Fee);
                            pp->Next_Order->OrderInfo.Actual_Fee = Actual_Fee;
                            break;
                        default:
                            printf("输入错误！！！⚠️\n");
                            break;
                    }
                    printf("请输⼊需要编辑的订单内容：\n1.订单编号\n 2.身份证号\n 3.客⼈姓名\n 4.⼿机号码\n 5.租⽤⻋辆编号\n 6.取⻋时间\n 7.预约还⻋时间\n 8.押⾦\n 9.实际还⻋时间\n 10.应缴费⽤\n 11.实缴费⽤\n 0.终止修改\n");
                    
                }
                printf("修改成功！！！\n");
                return;
            }
            
            p = p->Next_Info;
        }
    }
    printf("未找到该订单！！！⚠️\n");
    return ;
}
