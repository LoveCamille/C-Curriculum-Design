//
//  DataSearch.c
//  汽车租凭信息管理系统
//
//  Created by 🌲 on 2020/6/2.
//  Copyright © 2020 🌲. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataSearch.h"
#include "CarRentSystem.h"

//函数声明
//查找类型
//综合查找子模块
void search_by_type(Sort_Node* sort_head, Car_Node* car_head,char *s) {
    Sort_Node* p1;
    Car_Node* p;
    p = car_head->Next_Info;
    p1 = sort_head->Next_Sort;
    while (p1 && strcmp(s, p1->Sort.Sort_Name) != 0)
    {
        p1 = p1->Next_Sort;
    }
    if (p1 != NULL)
    {
        while (p)
        {
            if (p->Info.Type_Num == p1->Sort.Sort_Num && p->Info.Rental_Status != 'y')
            {
                printf("%s\t%s\t%s\t%f\n", s, p->Info.Name, p->Info.Gear_Mode, p->Info.Daily_Rent);
                p = p->Next_Info;
            }
            else{
                p = p->Next_Info;
            }
        }
    }
    return ;
}

//综合查找
void Comprehensive_Search_by_Type(Car_Node* car_head, Sort_Node* sort_head) {
    char s[5][20];
    int i;
    printf("请输入要查找个数：");
    int len = 1;
    scanf("%d", &len);getchar();
    for (i = 0; i < len; i++)
    {
        printf("第%d个数据类型名字：", i + 1);
        scanf("%s", s[i]);
        search_by_type(sort_head, car_head, s[i]);
    }

}

//组合查找车辆（已经没有BUG🛫️）
int Car_FreeSearch(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }
    
    char Plate_Num[10];         //车牌号
    char Name[20];              //车辆名称
    char Rental_Status;         //出租状态
    
    printf("请输入车牌号 车辆名 出租状态（两个条件间用空格隔开，不需要的条件输入*）：\n");
    scanf("%s %s %c", Plate_Num, Name, &Rental_Status);
    getchar();
    
    Car_Node * p;
    p = car_head->Next_Info;
    
    while (p) {
        //先判断车牌号
        if (*Plate_Num != '*' && strstr(p->Info.Plate_Num, Plate_Num) == NULL) {
            p = p->Next_Info;
            continue;
        }
        if (*Name != '*' && strstr(p->Info.Name, Name) == NULL) {
            p = p->Next_Info;
            continue;
        }
        if (Rental_Status != '*' && p->Info.Rental_Status != Rental_Status) {
            p = p->Next_Info;
            continue;
        }
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
    return 0;
}

//查找车辆（已经没有BUG🛫️）
int Car_Search(Car_Node * car_head, FILE * fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }
    
    int op;
    int s = 1;
    char Plate_Num[10];         //车牌号
    char Name[20];              //车辆名称
    char Rental_Status;         //出租状态
    
    Car_Node * p;
    p = car_head;
    
    printf("请选择查找方式：\n1.依据车牌号查找（ char Plate_Num[10] ）\n2.依据车辆名称查找（ char Name[20] ）\n3.依据出租状态查找（ char Rental_Status ）\n");
    scanf("%d", &op);
    getchar();
    
    fseek(fp, 73L, SEEK_CUR);//定位到第二行数据
    switch (op) {
            
        case 1:
            printf("请输入车牌号（ char Plate_Num[10] ）：\n");
            scanf("%s", Plate_Num);
            
            while (p->Next_Info != NULL) {
                while (strstr(p->Next_Info->Info.Plate_Num, Plate_Num) == NULL && p->Next_Info->Next_Info != NULL) {
                    p = p->Next_Info;
                }
                
                if (strstr(p->Next_Info->Info.Plate_Num, Plate_Num) == NULL && p->Next_Info->Next_Info == NULL) {
                    //printf("未找到相关车辆！！！⚠️\n");
                    return 1;
                }
                
                else{
                    printf("车辆编号：%2d\t，"\
                    "车牌号：%s\t，"\
                    "类型编码：%2d  ，"\
                    "车辆名称：%s，"\
                    "排挡方式：%s，"\
                    "每日租金：%.2f¥，"\
                    "出租状态：%c 。\n",
                    p->Next_Info->Info.Serial_Num,
                    p->Next_Info->Info.Plate_Num,
                    p->Next_Info->Info.Type_Num,
                    p->Next_Info->Info.Name,
                    p->Next_Info->Info.Gear_Mode,
                    p->Next_Info->Info.Daily_Rent,
                    p->Next_Info->Info.Rental_Status);
                    
                    p = p->Next_Info;
                    //将结果写入文件
                    fprintf(fp, "%d,%s,%d,%s,%s,%c\n", s, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Rental_Status);
                    s++;
                }
            }
            break;
            
        case 2:
            printf("请输入车辆名（ char Name[20] ）：\n");
            scanf("%s", Name);
            
            while (p->Next_Info != NULL) {
                while (strstr(p->Next_Info->Info.Name, Name) == NULL && p->Next_Info->Next_Info != NULL) {
                    p = p->Next_Info;
                }
                
                if (strstr(p->Next_Info->Info.Name, Name) == NULL && p->Next_Info->Next_Info == NULL) {
                    //printf("未找到相关车辆！！！⚠️\n");
                    return 1;
                }
                
                else{
                    printf("车辆编号：%2d\t，"\
                    "车牌号：%s\t，"\
                    "类型编码：%2d  ，"\
                    "车辆名称：%s，"\
                    "排挡方式：%s，"\
                    "每日租金：%.2f¥，"\
                    "出租状态：%c 。\n",
                    p->Next_Info->Info.Serial_Num,
                    p->Next_Info->Info.Plate_Num,
                    p->Next_Info->Info.Type_Num,
                    p->Next_Info->Info.Name,
                    p->Next_Info->Info.Gear_Mode,
                    p->Next_Info->Info.Daily_Rent,
                    p->Next_Info->Info.Rental_Status);
                    
                    p = p->Next_Info;
                    fprintf(fp, "%d,%s,%d,%s,%s,%c\n", s, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Rental_Status);
                    s++;
                }
            }
            break;
            
        case 3:
            printf("请输入出租状态（ char Rental_Status ）：\n");
            scanf("%c", &Rental_Status);
            
            while (p->Next_Info != NULL) {
                while (p->Next_Info->Info.Rental_Status != Rental_Status && p->Next_Info->Next_Info != NULL) {
                    p = p->Next_Info;
                }
                
                if (p->Next_Info->Info.Rental_Status != Rental_Status && p->Next_Info->Next_Info == NULL) {
                    //printf("未找到相关车辆！！！⚠️\n");
                    return 1;
                }
                
                else{
                    printf("车辆编号：%2d\t，"\
                    "车牌号：%s\t，"\
                    "类型编码：%2d  ，"\
                    "车辆名称：%s，"\
                    "排挡方式：%s，"\
                    "每日租金：%.2f¥，"\
                    "出租状态：%c 。\n",
                    p->Next_Info->Info.Serial_Num,
                    p->Next_Info->Info.Plate_Num,
                    p->Next_Info->Info.Type_Num,
                    p->Next_Info->Info.Name,
                    p->Next_Info->Info.Gear_Mode,
                    p->Next_Info->Info.Daily_Rent,
                    p->Next_Info->Info.Rental_Status);
                    
                    p = p->Next_Info;
                    fprintf(fp, "%d,%s,%d,%s,%s,%c\n", s, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Rental_Status);
                    s++;
                }
            }
            break;
            
        default:
            printf("输入错误！！！⚠️\n");
            break;
    }
    return 0;
}

//按照车牌号查找（已经没有BUG🛫️）
int Car_Search_PlateNum(Car_Node * car_head, FILE * fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }

    char Plate_Num[10];         //车牌号
    
    int s = 1;
    Car_Node * p;
    p = car_head;
    
    fseek(fp, 73L, SEEK_CUR);//定位到第二行数据
    printf("请输入车牌号（ char Plate_Num[10] ）：\n");
    scanf("%s", Plate_Num);
    getchar();
    while (p->Next_Info != NULL) {
        while (strstr(p->Next_Info->Info.Plate_Num, Plate_Num) == NULL && p->Next_Info->Next_Info != NULL) {
            p = p->Next_Info;
        }
                
        if (strstr(p->Next_Info->Info.Plate_Num, Plate_Num) == NULL && p->Next_Info->Next_Info == NULL) {
            //printf("未找到相关车辆！！！⚠️\n");
            return 1;
        }
                
        else{
                    printf("车辆编号：%2d\t，"\
                    "车牌号：%s\t，"\
                    "类型编码：%2d  ，"\
                    "车辆名称：%s，"\
                    "排挡方式：%s，"\
                    "每日租金：%.2f¥，"\
                    "出租状态：%c 。\n",
                    p->Next_Info->Info.Serial_Num,
                    p->Next_Info->Info.Plate_Num,
                    p->Next_Info->Info.Type_Num,
                    p->Next_Info->Info.Name,
                    p->Next_Info->Info.Gear_Mode,
                    p->Next_Info->Info.Daily_Rent,
                    p->Next_Info->Info.Rental_Status);
                    
                    p = p->Next_Info;
                    //将结果写入文件
                    fprintf(fp, "%d,%s,%d,%s,%s,%c\n", s, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Rental_Status);
                    s++;
        }
    }
    return 0;
}

//按照出租状态查找（已经没有BUG🛫️）
int Car_Search_RentalStatus(Car_Node * car_head, FILE * fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }

    char Rental_Status;         //车牌号
    
    int s = 1;
    Car_Node * p;
    p = car_head;
    
    fseek(fp, 73L, SEEK_CUR);//定位到第二行数据
    printf("请输入出租状态（ char Rental_Status ）：\n");
    scanf("%c", &Rental_Status);
    getchar();
    while (p->Next_Info != NULL) {
        
        while (p->Next_Info->Info.Rental_Status != Rental_Status && p->Next_Info->Next_Info != NULL) {
            p = p->Next_Info;
        }
        
        if (p->Next_Info->Info.Rental_Status != Rental_Status && p->Next_Info->Next_Info == NULL) {
            //printf("未找到相关车辆！！！⚠️\n");
            return 1;
        }
                
        else{
                    printf("车辆编号：%2d\t，"\
                    "车牌号：%s\t，"\
                    "类型编码：%2d  ，"\
                    "车辆名称：%s，"\
                    "排挡方式：%s，"\
                    "每日租金：%.2f¥，"\
                    "出租状态：%c 。\n",
                    p->Next_Info->Info.Serial_Num,
                    p->Next_Info->Info.Plate_Num,
                    p->Next_Info->Info.Type_Num,
                    p->Next_Info->Info.Name,
                    p->Next_Info->Info.Gear_Mode,
                    p->Next_Info->Info.Daily_Rent,
                    p->Next_Info->Info.Rental_Status);
                    
                    p = p->Next_Info;
                    //将结果写入文件
                    fprintf(fp, "%d,%s,%d,%s,%s,%c\n", s, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Rental_Status);
                    s++;
        }
    }
    return 0;
}

//按照车辆名称查找（已经没有BUG🛫️）
int Car_Search_Name(Car_Node * car_head, FILE * fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }

    char Name[20];
    
    int s = 1;
    Car_Node * p;
    p = car_head;
    
    fseek(fp, 73L, SEEK_CUR);//定位到第二行数据
    printf("请输入车辆名（ char Name[20] ）：\n");
    scanf("%s", Name);
    getchar();
    while (p->Next_Info != NULL) {
        while (strstr(p->Next_Info->Info.Name, Name) == NULL && p->Next_Info->Next_Info != NULL) {
            p = p->Next_Info;
        }
                
        if (strstr(p->Next_Info->Info.Name, Name) == NULL && p->Next_Info->Next_Info == NULL) {
            //printf("未找到相关车辆！！！⚠️\n");
            return 1;
        }
                
        else{
                    printf("车辆编号：%2d\t，"\
                    "车牌号：%s\t，"\
                    "类型编码：%2d  ，"\
                    "车辆名称：%s，"\
                    "排挡方式：%s，"\
                    "每日租金：%.2f¥，"\
                    "出租状态：%c 。\n",
                    p->Next_Info->Info.Serial_Num,
                    p->Next_Info->Info.Plate_Num,
                    p->Next_Info->Info.Type_Num,
                    p->Next_Info->Info.Name,
                    p->Next_Info->Info.Gear_Mode,
                    p->Next_Info->Info.Daily_Rent,
                    p->Next_Info->Info.Rental_Status);
                    
                    p = p->Next_Info;
                    //将结果写入文件
                    fprintf(fp, "%d,%s,%d,%s,%s,%c\n", s, p->Info.Plate_Num, p->Info.Type_Num, p->Info.Name, p->Info.Gear_Mode, p->Info.Rental_Status);
                    s++;
        }
    }
    return 0;
}

//以客人信息查找订单（已经没有BUG🛫️）
int Order_Search_Client(Car_Node * car_head, FILE *fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }
    
    int i = 1;
    int op = 0;
    char ID_Num[20];            //身份证号
    char Phone_Num[20];         //手机号码
    
    Car_Node * p = car_head->Next_Info;
    Order_Node * pp;
    
    printf("按照：\n1.身份证号\n2.手机号\n");
    scanf("%d", &op);getchar();
    switch (op) {
            case 1:
                printf("请输入身份证号：\n");
                scanf("%s", ID_Num);
                while (p != NULL) {
                    pp = p->Order;
                    if (pp == NULL) {
                        p = p->Next_Info;
                        continue;
                    }
                    
                    while (pp != NULL) {
                        if (strstr(pp->OrderInfo.ID_Num, ID_Num) != NULL) {
                            
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
                            pp->OrderInfo.Order_Num,
                            pp->OrderInfo.ID_Num,
                            pp->OrderInfo.Client_Nam,
                            pp->OrderInfo.Phone_Num,
                            pp->OrderInfo.Rent_Serial_Num,
                            pp->OrderInfo.Pick_Time,
                            pp->OrderInfo.Promised_Ret_Time,
                            pp->OrderInfo.Deposit,
                            pp->OrderInfo.Actual_Ret_Time,
                            pp->OrderInfo.Promised_Fee,
                            pp->OrderInfo.Actual_Fee);
                            i = 0;
                            pp = pp->Next_Order;
                        }//第一个如果就找到了节点就直接结束
                        
                        else{//第一个订单节点不是
                            pp = pp->Next_Order;
                            /*while (pp->Next_Order != NULL && strstr(pp->OrderInfo.ID_Num, ID_Num) == NULL) {
                                pp = pp->Next_Order;
                            }
                        
                            if (pp->Next_Order != NULL) {
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
                                pp->OrderInfo.Order_Num,
                                pp->OrderInfo.ID_Num,
                                pp->OrderInfo.Client_Nam,
                                pp->OrderInfo.Phone_Num,
                                pp->OrderInfo.Rent_Serial_Num,
                                pp->OrderInfo.Pick_Time,
                                pp->OrderInfo.Promised_Ret_Time,
                                pp->OrderInfo.Deposit,
                                pp->OrderInfo.Actual_Ret_Time,
                                pp->OrderInfo.Promised_Fee,
                                pp->OrderInfo.Actual_Fee);
                                
                                pp = pp->Next_Order;
                            }*/
                            
                        }
                    }
                    p = p->Next_Info;
                    
                }
                break;
            
            case 2:
                printf("请输入手机号：\n");
                scanf("%s", Phone_Num);
                while (p != NULL) {
                    pp = p->Order;
                    if (pp == NULL) {
                        p = p->Next_Info;
                        continue;
                    }
                    
                    while (pp != NULL) {
                        if (strstr(pp->OrderInfo.Phone_Num, Phone_Num) != NULL) {
                            
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
                            pp->OrderInfo.Order_Num,
                            pp->OrderInfo.ID_Num,
                            pp->OrderInfo.Client_Nam,
                            pp->OrderInfo.Phone_Num,
                            pp->OrderInfo.Rent_Serial_Num,
                            pp->OrderInfo.Pick_Time,
                            pp->OrderInfo.Promised_Ret_Time,
                            pp->OrderInfo.Deposit,
                            pp->OrderInfo.Actual_Ret_Time,
                            pp->OrderInfo.Promised_Fee,
                            pp->OrderInfo.Actual_Fee);
                            i = 0;
                            pp = pp->Next_Order;
                        }//第一个如果就找到了节点就直接结束
                        
                        else{//第一个订单节点不是
                            pp = pp->Next_Order;
                            /*pp = pp->Next_Order;
                            while (pp->Next_Order != NULL && strstr(pp->OrderInfo.Phone_Num, Phone_Num) == NULL) {
                                pp = pp->Next_Order;
                            }
                        
                            if (pp->Next_Order != NULL) {
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
                                pp->OrderInfo.Order_Num,
                                pp->OrderInfo.ID_Num,
                                pp->OrderInfo.Client_Nam,
                                pp->OrderInfo.Phone_Num,
                                pp->OrderInfo.Rent_Serial_Num,
                                pp->OrderInfo.Pick_Time,
                                pp->OrderInfo.Promised_Ret_Time,
                                pp->OrderInfo.Deposit,
                                pp->OrderInfo.Actual_Ret_Time,
                                pp->OrderInfo.Promised_Fee,
                                pp->OrderInfo.Actual_Fee);
                                
                                pp = pp->Next_Order;
                            }*/
                            
                        }
                    }
                    p = p->Next_Info;
                    
                }
                break;
                
            default:
                printf("输入错误！！！⚠️\n");
                break;
        }

    return i;
}

//以车辆信息查找订单（已经没有BUG🛫️）
int Order_Search_Car(Car_Node * car_head, FILE *fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }
    
    int i = 1;
    int op = 0;
    char Plate_Num[10];
    char Name[20];

    Order_Node * pp;
    Car_Node * p;
    p = car_head;
    
    printf("按照：\n1.车牌号\n2.车辆名称\n");
    scanf("%d", &op);getchar();
    
    switch (op) {
        case 1:
            printf("请输入车牌号（ char Plate_Num[10] ）：\n");
            scanf("%s", Plate_Num);
            while (p->Next_Info != NULL) {
                while (strstr(p->Next_Info->Info.Plate_Num, Plate_Num) == NULL && p->Next_Info->Next_Info != NULL) {
                    p = p->Next_Info;
                }
                        
                if (strstr(p->Next_Info->Info.Plate_Num, Plate_Num) == NULL && p->Next_Info->Next_Info == NULL) {
                    //printf("未找到相关车辆！！！⚠️\n");
                    return 1;
                }
                        
                else{
                    pp = p->Next_Info->Order;
                    while (pp) {
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
                        pp->OrderInfo.Order_Num,
                        pp->OrderInfo.ID_Num,
                        pp->OrderInfo.Client_Nam,
                        pp->OrderInfo.Phone_Num,
                        pp->OrderInfo.Rent_Serial_Num,
                        pp->OrderInfo.Pick_Time,
                        pp->OrderInfo.Promised_Ret_Time,
                        pp->OrderInfo.Deposit,
                        pp->OrderInfo.Actual_Ret_Time,
                        pp->OrderInfo.Promised_Fee,
                        pp->OrderInfo.Actual_Fee);
                        i = 0;
                        pp = pp->Next_Order;
                    }
                    p = p->Next_Info;
                }
            }
            break;
        
        case 2:
            while (p->Next_Info != NULL) {
                while (strstr(p->Next_Info->Info.Name, Name) == NULL && p->Next_Info->Next_Info != NULL) {
                    p = p->Next_Info;
                }
                        
                if (strstr(p->Next_Info->Info.Name, Name) == NULL && p->Next_Info->Next_Info == NULL) {
                    //printf("未找到相关车辆！！！⚠️\n");
                    return 1;
                }
                        
                else{
                    pp = p->Next_Info->Order;
                    while (pp) {
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
                        pp->OrderInfo.Order_Num,
                        pp->OrderInfo.ID_Num,
                        pp->OrderInfo.Client_Nam,
                        pp->OrderInfo.Phone_Num,
                        pp->OrderInfo.Rent_Serial_Num,
                        pp->OrderInfo.Pick_Time,
                        pp->OrderInfo.Promised_Ret_Time,
                        pp->OrderInfo.Deposit,
                        pp->OrderInfo.Actual_Ret_Time,
                        pp->OrderInfo.Promised_Fee,
                        pp->OrderInfo.Actual_Fee);
                        i = 0;
                        pp = pp->Next_Order;
                    }
                    p = p->Next_Info;
                }
            }
            break;
            
        default:
            printf("输入错误！！！⚠️\n");
            break;
    }

    return i;
}

//以时间范围查找订单（已经没有BUG🛫️）
int Order_Search_Time(Car_Node * car_head, FILE *fp) {//返回1就是没找到
    
    if (car_head == NULL) {
        printf("未载入数据！！！⚠️\n");
        return 0;
    }
    
    char Start[20];       //身份证号
    char End[20];         //手机号码
    int i = 1;
    
    Car_Node *p = car_head->Next_Info;
    Order_Node * pp;
    
    printf("按照：XXXX/XX/XX的方式输入日期\n");
    printf("输入起始日期\n");
    scanf("%s", Start);
    printf("输入终止日期\n");
    scanf("%s", End);
   
                while (p != NULL) {
                    pp = p->Order;
                    if (pp == NULL) {
                        p = p->Next_Info;
                        continue;
                    }
                    //strstr(pp->OrderInfo.ID_Num, ID_Num) != NULL
                    while (pp != NULL) {
                        pp->OrderInfo.Actual_Ret_Time[10] = '\0';
                        if (strcmp(pp->OrderInfo.Actual_Ret_Time, Start) >= 0 && strcmp(pp->OrderInfo.Actual_Ret_Time, End) <= 0) {//符合条件
                            
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
                            pp->OrderInfo.Order_Num,
                            pp->OrderInfo.ID_Num,
                            pp->OrderInfo.Client_Nam,
                            pp->OrderInfo.Phone_Num,
                            pp->OrderInfo.Rent_Serial_Num,
                            pp->OrderInfo.Pick_Time,
                            pp->OrderInfo.Promised_Ret_Time,
                            pp->OrderInfo.Deposit,
                            pp->OrderInfo.Actual_Ret_Time,
                            pp->OrderInfo.Promised_Fee,
                            pp->OrderInfo.Actual_Fee);
                            
                            i = 0;
                            pp = pp->Next_Order;
                            
                        }//第一个如果就找到了节点就直接结束
                        
                        else{//第一个订单节点不是
                            pp = pp->Next_Order;
                            /*while (pp->Next_Order != NULL && (strcmp(pp->OrderInfo.Actual_Ret_Time, Start) >= 0 && strcmp(pp->OrderInfo.Actual_Ret_Time, End) <= 0) == 0) {
                                pp = pp->Next_Order;
                            }
                        
                            if (pp->Next_Order != NULL) {
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
                                pp->OrderInfo.Order_Num,
                                pp->OrderInfo.ID_Num,
                                pp->OrderInfo.Client_Nam,
                                pp->OrderInfo.Phone_Num,
                                pp->OrderInfo.Rent_Serial_Num,
                                pp->OrderInfo.Pick_Time,
                                pp->OrderInfo.Promised_Ret_Time,
                                pp->OrderInfo.Deposit,
                                pp->OrderInfo.Actual_Ret_Time,
                                pp->OrderInfo.Promised_Fee,
                                pp->OrderInfo.Actual_Fee);
                                
                                pp = pp->Next_Order;
                            }*/
                            
                        }
                    }
                    p = p->Next_Info;
                    
                }
    return i;
}

//统计车辆类型（已经没有BUG🛫️）
void Calculate_Sort(Sort_Node * sort_head,Car_Node * car_head){
    
    if (car_head == NULL) {
        printf("未导入数据！！！\n");
        return ;
    }
    
    if (sort_head->Next_Sort == NULL) {
        printf("未导入数据！！！\n");
        return ;
    }
    
    Sort_Node *p = sort_head->Next_Sort;
    Car_Node *q = car_head->Next_Info;
    
    int usable = 0, unusable = 0;
    
    printf("车辆类型       车辆总数    已出租数    未出租数\n");
    while(p != NULL)
    {
        while(q != NULL) {
            
            if(q->Info.Type_Num == p->Sort.Sort_Num && q->Info.Rental_Status == 'n')
                usable += 1;
            if(q->Info.Type_Num == p->Sort.Sort_Num && q->Info.Rental_Status== 'y')
                unusable += 1;
            q=q->Next_Info;
            
        }
        printf("%-10s%10d%10d%10d\n", p->Sort.Sort_Name, usable+unusable, unusable,usable);
        
        p = p->Next_Sort;
        q = car_head->Next_Info;
        
        usable=0;
        unusable=0;
    }
    return ;
}

//统计各类型营业额（已经没有BUG🛫️）
void Calculate_Profit(Sort_Node * sort_head, Car_Node * car_head){

    float profit = 0;
    char month[20]="";
    printf("请输入月份 ( 格式XXXX/XX ):\n");
    scanf("%s",month);getchar();
    
    Sort_Node * p = sort_head->Next_Sort;
    Car_Node * q = car_head->Next_Info;
    Order_Node * m = NULL;

    while(p!=NULL) {
        
        while(q!=NULL) {
            
            if(q->Info.Type_Num == p->Sort.Sort_Num) {
                
                m = q->Order;
                while(m != NULL) {
                    
                if(strstr(m->OrderInfo.Actual_Ret_Time,month))
                    profit+=m->OrderInfo.Actual_Fee;
                    
                m=m->Next_Order;
                    
                }
            }
            q=q->Next_Info;
        }
        
        printf("%s:⬇️\n\n", p->Sort.Sort_Name);
        draw(profit);
        
        p=p->Next_Sort;
        q=car_head->Next_Info;
        profit=0;
    }
    printf("——————————————————————————————————————————————————————————————————————————————————————————> 20.0元/格\n");
    return;
}

//计算每辆车的营业额（已经没有BUG🛫️）
void Calculate_Carprofit(Car_Node * car_head){
    
    if (car_head == NULL) {
        printf("未导入数据！！！\n");
        return ;
    }
    
        Car_Node * p = car_head->Next_Info;
        Order_Node * q = NULL;
    
        float profit=0;
        float rate=0;
        char year[10]="";
    
        printf("请输入年份\n");
        scanf("%s", year);getchar();
    
        printf("车牌号              车辆名称       营业额       租用率\n");

        while(p != NULL) {
            q = p->Order;
            while(q!=NULL)
            {
                if(strstr(q->OrderInfo.Actual_Ret_Time, year))
                profit+=q->OrderInfo.Actual_Fee;
                
                q=q->Next_Order;
            }
            rate=(profit/p->Info.Daily_Rent)/365;
            printf("%-20s%-10s\t%7g    %10g\n",p->Info.Plate_Num,p->Info.Name,profit,rate);
            p=p->Next_Info;profit=0;rate=0;
        }
    
    return;
}

//计算前十的车辆（已经没有BUG🛫️）
void Calculate_mvp(Car_Node * car_head) {
    
    if (car_head == NULL) {
        printf("未导入数据！！！\n");
        return ;
    }
    
    //声明前十的车辆结构体
    typedef struct mvp{
        char carname[20];
        char carnumber[10];
        float profit;
        int day;
        float rate;
        float fare;
        struct mvp *next_mvp;
    }mvp;
    
    mvp *head1=(mvp*)malloc(sizeof(mvp));
    head1->next_mvp=NULL;
    mvp *interval=head1;
    mvp *m=(mvp*)malloc(sizeof(mvp));
    Car_Node * p = car_head->Next_Info;
    Order_Node * q = NULL;
    char year[10]="";
    printf("请输入年份\n");
    scanf("%s",year);getchar();
    printf("车牌号      车辆名称      累计出租天数      营业额      租用率\n");
    float profit = 0;
    int day = 0;
    while(p!=NULL)
    {   q=p->Order;
        while(q!=NULL)
        {
            if(strstr(q->OrderInfo.Actual_Ret_Time,year))
                profit+=q->OrderInfo.Actual_Fee;
            q = q->Next_Order;
        }
        day=profit/p->Info.Daily_Rent;
        m->fare=p->Info.Daily_Rent;
        m->profit=profit;
        m->next_mvp=NULL;
        m->day=day;
        m->rate=1.0*day/365;
        strcpy(m->carname,p->Info.Name);
        strcpy(m->carnumber,p->Info.Plate_Num);
        while(interval->next_mvp!=NULL&&interval->next_mvp->day>m->day)
            interval=interval->next_mvp;
        m->next_mvp=interval->next_mvp;
        interval->next_mvp=m;
        p=p->Next_Info;
        profit=0;day=0;
        interval=head1;
        m=(mvp*)malloc(sizeof(mvp));
    }
    //节点排序
    for(int i=0;i<10&&head1->next_mvp!=NULL&&head1->next_mvp->day!=0;i++)
    {printf("%s\t\t%s\t\t%d\t%f\t%f\n",head1->next_mvp->carnumber,head1->next_mvp->carname,head1->next_mvp->day,head1->next_mvp->profit,head1->next_mvp->rate);
        head1=head1->next_mvp;}
}
