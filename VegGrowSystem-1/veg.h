#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <graphics.h>
#include <math.h>
#define LEN1 sizeof(struct veg1) //令LEN2代表veg1类型数据的长度
#define LEN2 sizeof(struct veg2) //令LEN1代表veg2类型数据的长度

typedef struct f_search//组合搜索结构体
{
    int year;//搜索年份
    int above;//收获重量最小值
    int kind;//搜索类型
}f_search;

typedef struct information1 //蔬菜基本信息
{
    int num1;			 //蔬菜排序编号
    int num2;			 //分类码
    char nutrition[100]; //营养成分
    char name[20];		 //蔬菜名字
} information1;

typedef struct information2 //蔬菜种植信息
{
    int kind;      //标记蔬菜种类
    int num2;      //蔬菜基本信息排序编号
    int num1;	   //蔬菜种植信息排序编号
    int area;	   //蔬菜种植面积
    int weight;	   //蔬菜收获重量
    int year;	   //收获年份
    char name[20]; //蔬菜名字
} information2;

typedef struct veg2 //用于蔬菜种植信息表的结构体
{
    struct information2 plant_info; //结构体蔬菜的数据域
    struct veg2 *next;
} veg2;

typedef struct veg1 //下属大类kind的蔬菜类型
{
    int flag;				  //用于标记该单元是否已经进行访问
    struct information1 info; //结构体蔬菜的数据域
    struct veg1 *next;
    struct veg2 head;       //种植信息链表头
} veg1;

typedef struct kind
{
    int num;
    char kind_name[20]; //类型名称
    int total_weight;//总重量
    struct kind *right; //并列大类
    struct veg1 *down;	//下属子类
} kind;


//导入三章主表操作
kind *creat_trunk();			 //创造大类主链
veg1 *sorting_line(FILE *);		 //添加一个排序主链，用于对蔬菜基本信息表中的蔬菜进行排序和导入大类主链
void insert_veg(kind *, FILE *); //往主链添加蔬菜
char *split(char *, char *);     //字符串分割函数
void search_main_list(veg1* [],veg1*);  //找到排序链对应主链节点进行输出
veg2* loading_grow_infolist(FILE*,veg1*);//导入植物种植信息表,并创建种植信息排序信息链


//保存修改操作
void search_sq_list_grow_1(veg1*,veg2*); //初始化时，找到当前遍历蔬菜种植信息节点所对应排序链节点进行输出
void search_sq_list_grow_2(veg1*,veg2*); //重新排序时，找到当前遍历蔬菜种植信息节点所对应排序链节点进行输出
void save_info1(veg1* [],veg1*,veg2*);//保存前三张表的信息
void reposition(veg1* [],veg1*,veg2*);//修改信息删除信息后序号的重排


//信息的新增，修改，删除
void add_veg(veg1*[],veg1* );//蔬菜种类和基本信息的加入
void adjust_veg(veg1*[],veg1* );//蔬菜种类和基本信息的修改
void del_veg(veg1* [],veg1*,veg2*); //删除蔬菜种类和基本信息
void add_grow_veg(veg1* [],veg1*,veg2*);//蔬菜种植信息的导入
void adjust_grow_veg(veg1* [],veg1*,veg2*);//蔬菜种植信息的修改
void del_grow_veg(veg1* [],veg1*,veg2*); //删除蔬菜种植信息


//信息的搜索操作
void kind_num_search(veg1* []);//按照分类码进行搜索
void keyword_basic_info_search(veg1* []);//按照关键词显示基本信息
void kind_nutrition_search(veg1* []);//按照种类和所含营养成分查询
void name_keyword_year_grow_search(veg1* []);//按照蔬菜名称关键词，和年份查询种植信息
void name_grow_search(veg1* []);//按蔬菜名称进行种植信息查询



//信息的统计
void count_kind_grow_info(veg1* []);//统计种植总面积，收获总重量，输出分类名称
void sort_total(veg2 [], int);//对统计数据进行降序排列
void count_year_name(veg1*, veg2*);//统计某个蔬菜一段时间内的总重量
void count_kind_veg_weight(veg1* []);//统计每个种类的蔬菜总重量
void count_kind_veg(veg1* []);//统计每个种类的蔬菜总数量
void nutrition_search(veg1* []);//按所含营养成分查询
void graph_show(veg2 []);//展示统计图

//数据导出
void output_grow_info(veg1* []);//统计并显示某个时间段的各类蔬菜种植信息
void latest_threeyear_grow_info(veg1* []);//统计最近三年内各个蔬菜的种植信息
void free_search(veg1* []);//自由组合年份，重量下限，类别

//其他功能
int max_mark(int maxn);
void put_in(veg1* [],veg1*);
int max_num(veg2 t[]);


void put_in(veg1* D_head1[],veg1* sort_head)
{
    veg1 *sq_p;       //sq_p为排序链操作指针
    sq_p = sort_head->next;
    while (sq_p != NULL)
    {
        search_main_list(D_head1, sq_p);
        sq_p = sq_p->next;
    }
}

//找到统计种植信息重量最大的函数33
int max_num(veg2 t[])
{
    int i,maxn;
    maxn=0;
    for(i=1; i<5; i++)
    {
        if(t[maxn].plant_info.weight<t[i].plant_info.weight)
        {
            maxn=i;
        }
    }
    return maxn;
}

//定义最高的柱状图的像素点个数32
int max_mark(int maxn)
{
    int high, cur, i=0;
    high=10;
    cur=maxn;
    while(cur>=10)
    {
        i++;
        cur=cur/high;
    }
    cur=3*cur*pow(10,i)/2;
    return cur;
}

//自由组合年份，重量下限，类别31
void free_search(veg1* D_head1[])
{
    int i;
    FILE *fp;
    f_search goal;
    char str[40];
    char name[40];//文件名
    char route1[200]="C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\";
    veg1* p;
    veg2* pp;
    printf("    请输入所需要进行导出数据的文件名：\n");
    printf("    ");
    scanf("%s",name);
    strcat(route1,name);
    strcat(route1,".csv");
    fp = fopen(route1, "w");
    if (fp == NULL)
    {
        printf("    文件不存在或者被占用\n");
        fclose(fp);
        return ;
    }
    printf("    请输入搜索组合（以中文逗号为分隔，依次填入年份，重量下限，类别，若某类型条件不限请输入0）：\n    ");
    scanf("%d，%d，%s",&(goal.year),&(goal.above),str);
    if(strcmp(str,"根茎类")==0)
        goal.kind=1;
    else if(strcmp(str,"果菜类")==0)
        goal.kind=2;
    else if(strcmp(str,"瓜类")==0)
        goal.kind=3;
    else if(strcmp(str,"叶菜类")==0)
        goal.kind=4;
    else if(strcmp(str,"菌类")==0)
        goal.kind=5;
    else
        goal.kind=0;
    system("cls");
    printf("    年份\t蔬菜名称\t种植面积\t收获总重量\n");
    fprintf(fp,"    年份,蔬菜名称,种植面积,收获总重量\n");

    if(goal.kind<=5&&goal.kind>=1)
    {
        p=D_head1[goal.kind-1]->next;
        if(goal.above==0)
        {
            //限定种类，不限重量下限，不限时间
            if(goal.year==0)
            {
                while(p!=NULL)
                {
                    pp=p->head.next;
                    while(pp!=NULL)
                    {
                        printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                        fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                        pp=pp->next;
                    }
                    p=p->next;
                }
            }
            //限定种类，不限重量下限，限定时间
            else
            {
                while(p!=NULL)
                {
                    pp=p->head.next;
                    while(pp!=NULL)
                    {
                        if(goal.year==pp->plant_info.year)
                        {
                            printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            break;
                        }
                        pp=pp->next;
                    }
                    p=p->next;
                }
            }
        }
        else
        {
            //限定种类，限定重量下限，不限时间
            if(goal.year==0)
            {
                while(p!=NULL)
                {
                    pp=p->head.next;
                    while(pp!=NULL)
                    {
                        if(pp->plant_info.weight>=goal.above)
                        {
                            printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                        }
                        pp=pp->next;
                    }
                    p=p->next;
                }
            }
            //限定种类，限定重量下限，限定时间
            else
            {
                while(p!=NULL)
                {
                    pp=p->head.next;
                    while(pp!=NULL)
                    {
                        if(goal.year==pp->plant_info.year&&pp->plant_info.weight>=goal.above)
                        {
                            printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            break;
                        }
                        pp=pp->next;
                    }
                    p=p->next;
                }
            }
        }
    }
    else if(goal.kind==0)
    {
        for(i=0;i<5;i++)
        {
            p=D_head1[i]->next;
            if(goal.above==0)
            {
                //不限种类，不限重量下限，不限时间
                if(goal.year==0)
                {
                    while(p!=NULL)
                    {
                        pp=p->head.next;
                        while(pp!=NULL)
                        {
                            printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            pp=pp->next;
                        }
                        p=p->next;
                    }
                }
                //不限种类，不限重量下限，限定时间
                else
                {
                    while(p!=NULL)
                    {
                        pp=p->head.next;
                        while(pp!=NULL)
                        {
                            if(goal.year==pp->plant_info.year)
                            {
                                printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                                fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                                break;
                            }
                            pp=pp->next;
                        }
                        p=p->next;
                    }
                }
            }
            else
            {
                //不限种类，限定重量下限，不限时间
                if(goal.year==0)
                {
                    while(p!=NULL)
                    {
                        pp=p->head.next;
                        while(pp!=NULL)
                        {
                            if(pp->plant_info.weight>=goal.above)
                            {
                                printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                                fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                            }
                            pp=pp->next;
                        }
                        p=p->next;
                    }
                }
                //限定种类，限定重量下限，限定时间
                else
                {
                    while(p!=NULL)
                    {
                        pp=p->head.next;
                        while(pp!=NULL)
                        {
                            if(goal.year==pp->plant_info.year&&pp->plant_info.weight>=goal.above)
                            {
                                printf("    %d\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                                fprintf(fp,"    %d,%s,%d,%d\n",pp->plant_info.year,p->info.name,pp->plant_info.area,pp->plant_info.weight);
                                break;
                            }
                            pp=pp->next;
                        }
                        p=p->next;
                    }
                }
            }

            }
        }
        fclose(fp);

}

//统计最近三年内各个蔬菜的种植信息30
void latest_threeyear_grow_info(veg1* D_head1[])
{
    FILE* fp;
    veg1* p;
    veg2* pp;
    char str[40];
    int i,j;
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\按蔬菜名称统计信息表.csv", "w");
    if (fp == NULL)
    {
        printf("fail to open the file1!!!\n");
        fclose(fp);
        return ;
    }
    system("cls");
    printf("    年份\t蔬菜名称\t分类名称\t种植面积\t收获总重量\n");
    fprintf(fp,"    年份,蔬菜名称,分类名称,种植面积,收获总重量\n");
    for(i=0;i<5;i++)
    {
        if(i==0)
            strcpy(str,"根茎类");
        else if(i==1)
            strcpy(str,"果菜类");
        else if(i==2)
            strcpy(str,"瓜类");
        else if(i==3)
            strcpy(str,"叶菜类");
        else if(i==4)
            strcpy(str,"菌类");
        p=D_head1[i]->next;
        while(p!=NULL)
        {
            j=0;
            pp=p->head.next;
            while(pp!=NULL)
            {
                j++;
                printf("    %d\t%s\t\t%s\t\t%d\t\t%d\n",pp->plant_info.year,p->info.name,str,pp->plant_info.area,pp->plant_info.weight);
                fprintf(fp,"    %d,%s,%s,%d,%d\n",pp->plant_info.year,p->info.name,str,pp->plant_info.area,pp->plant_info.weight);
                pp=pp->next;
                if(j==3)
                    break;
            }
            p=p->next;
        }

    }
}

//统计并显示某时间段的各类蔬菜种植信息29
void output_grow_info(veg1* D_head1[])
{
    FILE *fp;
    int flag;
    flag=0;
    int begin_t,end_t;
    int num,i,j;//num用于记录需要创建数组的个数,goal用于查询序号对应的蔬菜名称
    veg1* p;
    veg2* pp;//找到蔬菜后操作查询种植信息子链

    //输入起止年限
    printf("    请输入需要统计蔬菜类种植信息的年份起止时间（格式：开始时间（空格）结束时间）：\n    ");
    scanf("%d %d",&begin_t,&end_t);
    num=end_t-begin_t+1;
    veg2 total[5][num];//第二维为起始年限间隔

    //文件指针初始化
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\按年份各类蔬菜信息统计表.csv", "w");
    if (fp == NULL)
    {
        printf("    fail to open the file1!!!\n");
        fclose(fp);
        return ;
    }

    //进行统计
    for(i=end_t;i>=begin_t;i--)
    {
        for(j=0;j<5;j++)
        {
            p=D_head1[j]->next;
            total[j][i-begin_t].plant_info.weight=0;
            total[j][i-begin_t].plant_info.area=0;
            while(p!=NULL)
            {
                pp=p->head.next;
                while(pp!=NULL)
                {
                    if(pp->plant_info.year==i)
                    {
                        flag=1;
                        total[j][i-begin_t].plant_info.weight += pp->plant_info.weight;
                        total[j][i-begin_t].plant_info.area += pp->plant_info.area;
                    }
                    pp=pp->next;
                }
                p=p->next;
            }
            //完成某年一条链上重量和种植面积统计
        }
    }

    if(flag==0)
    {
        printf("    该年份无任何种植信息");
        return;
    }

    //打印信息到屏幕和文件
    system("cls");
    printf("    年份\t分类名称\t种植面积\t收获总重量\n");
    fprintf(fp,"    年份,分类名称,种植面积,收获总重量\n");
    for(i=end_t;i>=begin_t;i--)
    {
        for(j=0;j<5;j++)
        {
            if(total[j][i-begin_t].plant_info.area==0)
            {
                continue;
            }
            if(j==0)
            {
                printf("    %d\t根茎类\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,根茎类,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==1)
            {
                printf("    %d\t果菜类\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,果菜类,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==2)
            {
                printf("    %d\t瓜类\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,瓜类,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==3)
            {
                printf("    %d\t叶菜类\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,叶菜类,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==4)
            {
                printf("    %d\t菌类\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,菌类,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
        }
    }
    fclose(fp);

}

//按所含营养成分查询28
void nutrition_search(veg1* D_head1[])
{
    char goal[40];
    int i,flag;
    flag=0;
    veg1* p;
    printf("    输入需要搜索营养成分（格式：营养成分）：\n   ");
    scanf("%s",goal);
    for(i=0;i<5;i++)
    {
        p=D_head1[i]->next;
        while(p!=NULL)
        {
            if(strstr(p->info.nutrition,goal)!=NULL)
            {
                flag=1;
                printf("    %d\t%s\t%d\t%s\n",p->info.num1,p->info.name,p->info.num2,p->info.nutrition);
            }
            p=p->next;
        }
    }
    if(flag==0)
        printf("    该营养成分关键词无对应蔬菜\n");
}

//统计每个种类的蔬菜总数量27
void count_kind_veg(veg1* D_head1[])
{
    int veg_kind[5];
    int i,vcount;//vcount为计数器
    veg1 *p;
    for(i=0;i<5;i++)
    {
        p=D_head1[i]->next;
        vcount=0;
        while(p!=NULL)
        {
            vcount++;
            p=p->next;
        }
        veg_kind[i]=vcount;
    }
    for(i=0;i<5;i++)
    {
        if(i==0)
        {
            printf("    根茎类\t蔬菜总数量：%d\n",veg_kind[i]);
        }
        else if(i==1)
        {
            printf("    果菜类\t蔬菜总数量：%d\n",veg_kind[i]);
        }
        else if(i==2)
        {
            printf("    瓜类\t蔬菜总数量：%d\n",veg_kind[i]);
        }
        else if(i==3)
        {
            printf("    叶菜类\t蔬菜总数量：%d\n",veg_kind[i]);
        }
        else if(i==4)
        {
            printf("    菌类\t蔬菜总数量：%d\n",veg_kind[i]);
        }
    }
}

//统计每个类别的蔬菜总重量26
void count_kind_veg_weight(veg1* D_head1[])
{
    int veg_kind[5];
    int i,vcount;//vcount为计数器
    veg1 *p;
    veg2 *pp;
    for(i=0;i<5;i++)
    {
        p=D_head1[i]->next;
        vcount=0;
        while(p!=NULL)
        {
            pp=p->head.next;
            while(pp!=NULL)
            {
                vcount+=pp->plant_info.weight;
                pp=pp->next;
            }
            p=p->next;
        }
        veg_kind[i]=vcount;
    }
    for(i=0;i<5;i++)
    {
        if(i==0)
        {
            printf("    根茎类\t蔬菜总重量：%d\n",veg_kind[i]);
        }
        else if(i==1)
        {
            printf("    果菜类\t蔬菜总重量：%d\n",veg_kind[i]);
        }
        else if(i==2)
        {
            printf("    瓜类\t蔬菜总重量：%d\n",veg_kind[i]);
        }
        else if(i==3)
        {
            printf("    叶菜类\t蔬菜总重量：%d\n",veg_kind[i]);
        }
        else if(i==4)
        {
            printf("    菌类\t蔬菜总重量：%d\n",veg_kind[i]);
        }
    }
}

//统计一段时间内的总重量25
void count_year_name(veg1* sort_head, veg2* gr_head)
{
    int begin_t,end_t;
    int cur_end_t;//由于某些蔬菜在某些年份是缺少信息的，cur_end_t从当前蔬菜的最大年份算起，进行数据统计
    int num,i,j;//num用于记录需要创建数组的个数,goal用于查询序号对应的蔬菜名称
    veg1* p;
    veg2* pp;//找到蔬菜后操作查询种植信息子链
    //创建存放统计信息的数组
    num=0;
    p=sort_head->next;
    while(p!=NULL)
    {
        num++;
        p=p->next;
    }
    veg2 total[num];

    //输入起止年限
    printf("    输入需要查询的年份起止时间：（格式：开始时间（空格）结束时间）\n    ");
    scanf("%d %d",&begin_t,&end_t);

    //进行统计
    p=sort_head->next;
    i=0;
    while(p!=NULL)
    {
        strcpy(total[i].plant_info.name,p->info.name);
        total[i].plant_info.area=0;
        total[i].plant_info.weight=0;
        pp=p->head.next;

        //我的种植信息链按年份降序排序，因此我可以先找到终止年份
        while(pp!=NULL)
        {
            if(pp->plant_info.year <= end_t)
            {
                cur_end_t=pp->plant_info.year;
                break;
            }
            pp=pp->next;
        }

        //由终止年份判断起始年份之间的年份是否存在信息有则加入total[i]中
        for(j=cur_end_t;j>=begin_t;j--)
        {
            if(pp==NULL)
                break;
            if(pp->plant_info.year==j)
            {
                total[i].plant_info.area += pp->plant_info.area;
                total[i].plant_info.weight += pp->plant_info.weight;
            }
            pp=pp->next;
        }
        i++;
        p=p->next;
    }
    sort_total(total,num);
    system("cls");
    printf("    %d-%d蔬菜的种植信息统计如下\n",begin_t,end_t);
    for(i=0;i<num;i++)
    {
        if(strcmp(total[i].plant_info.name,"蒜")==0)
        {
            printf("    %s \t\t总重量：%d\t 总面积：%d\n",total[i].plant_info.name,total[i].plant_info.weight,total[i].plant_info.area);
        }
        else
        {
            printf("    %s \t总重量：%d\t 总面积：%d\n",total[i].plant_info.name,total[i].plant_info.weight,total[i].plant_info.area);
        }
    }
}

//展示统计图24
void graph_show(veg2 t[])
{
    initgraph(1000, 800, 0);
    setcolor(BLACK);
    setbkcolor(WHITE);
    setfillcolor(GREEN);
    //(字体高度,字体宽度(为0即为自适应),字形)设置字体为25,幼圆字体

    float f;
    int i,tt[5], b,maxn,tt_max,gap;//t为每个类别蔬菜的总重量，tt为坐标放缩后的坐标值，b为柱体左下x坐标，maxn为总重量中最大的值
                                    //tt_max为坐标轴最大的刻度，gap为刻度之间的差值w
    gap=80;
    for(i=0; i<5; i++)
    {
        tt[i]=t[i].plant_info.weight;
    }
    maxn=max_num(t);
    if(t[maxn].plant_info.weight>400)
    {
        for(i=0;i<5;i++)
        {
            tt_max=max_mark(t[maxn].plant_info.weight);
            gap=tt_max/5;
            tt[i]=(t[i].plant_info.weight*80)/gap;
        }
    }

    line(60,500,650,500);
    line(60,500,60,80);
    line(60,80,55,90);
    line(60,80,65,90);
    line(650,500,640,495);
    line(650,500,640,505);

    b=80;
    for(i=0; i<5; i++)
    {
        f=(t[i].plant_info.weight*80)/(1.0*gap);
        if((tt[i]%gap==0)&&(fmodf(f,1.0*gap)<0.00001))
        {
            bar(b,500-tt[i],b+80,500);
        }
        else
        {
            bar(b,503-tt[i],b+80,500);
        }
        setfont(15,0,"幼圆");
        xyprintf(b+25,480-tt[i],"%d",t[i].plant_info.weight);
        if(t[i].plant_info.kind==1)
        {
            setfont(25,0,"幼圆");
            outtextxy(b,510,"根茎类");
        }
        else if(t[i].plant_info.kind==2)
        {
            setfont(25,0,"幼圆");
            outtextxy(b,510,"果菜类");
        }
        else if(t[i].plant_info.kind==3)
        {
            setfont(25,0,"幼圆");
            outtextxy(b+12,510,"瓜类");
        }
        else if(t[i].plant_info.kind==4)
        {
            setfont(25,0,"幼圆");
            outtextxy(b,510,"叶菜类");
        }
        else if(t[i].plant_info.kind==5)
        {
            setfont(25,0,"幼圆");
            outtextxy(b+12,510,"菌类");
        }
        b += 110;
    }
    setfont(15,0,"幼圆");
    outtextxy(660,495,"蔬菜种类");
    outtextxy(30,60,"重量单位：kg");
    b=500;
    int a=0;

    //打印坐标轴刻度
    for(i=1; i<=5; i++)
    {
        a+=gap;
        b-=80;
        line(60,b,65,b);
        xyprintf(25,b,"%d",a);
    }
    getch();
    closegraph();
}

//对统计数据进行降序排列23
void sort_total(veg2 total[],int num)
{
    int i,j,maxn;
    veg2 temp;
    for(i=0;i<num;i++)
    {
        maxn=i;
        for(j=i+1;j<num;j++)
        {
            if(total[maxn].plant_info.weight<total[j].plant_info.weight)
                maxn=j;
        }
        temp.plant_info=total[i].plant_info;
        total[i].plant_info=total[maxn].plant_info;
        total[maxn].plant_info=temp.plant_info;
    }

}

//统计种植总面积，收获总重量，输出分类名称22
void count_kind_grow_info(veg1* D_head1[])
{
    veg2 total[5];//用于记录各个分类的种植总面积，收获总重量
    veg2* pp;      //用于遍历每个蔬菜的种植信息链
    veg1* p;      //用于遍历大类下属的分链
    int i;
    int goal;
    printf("    输入需要统计的年份（格式：年份）：\n    ");
    scanf("%d",&goal);
    for(i=0;i<5;i++)
    {
        total[i].plant_info.kind=i+1;
        p=D_head1[i]->next;
        total[i].plant_info.area=0;
        total[i].plant_info.weight=0;
        while(p!=NULL)
        {
            pp=p->head.next;
            while(pp!=NULL)
            {
                if(goal==pp->plant_info.year)
                {
                    total[i].plant_info.area += pp->plant_info.area;
                    total[i].plant_info.weight += pp->plant_info.weight;
                }
                pp=pp->next;
            }
            p=p->next;
        }
    }
    sort_total(total,5);
    for(i=0;i<5;i++)
    {
        if(total[i].plant_info.kind==1)
        {
            printf("    根茎类\t总重量：%d\t 总面积：%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==2)
        {
            printf("    果菜类\t总重量：%d\t 总面积：%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==3)
        {
            printf("    瓜类\t总重量：%d\t 总面积：%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==4)
        {
            printf("    叶菜类\t总重量：%d\t 总面积：%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==5)
        {
            printf("    菌类\t总重量：%d\t 总面积：%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
    }
    graph_show(total);
}

//主链的添加 1
kind *creat_trunk()
{
    int i;
    struct kind *head;
    struct kind *p1, *p2;
    head = (struct kind *)malloc(sizeof(kind)); //表头空节点，可以不赋值，或者赋值一个用不到的值
    p2 = head;
    for (i = 1; i < 6; i++)
    {
        p1 = (struct kind *)malloc(sizeof(kind));
        p1->num = i;
        p1->total_weight=0;
        p1->right = NULL;
        p1->down = NULL;
        if (i == 1)
            strcpy(p1->kind_name, "根茎类");
        else if (i == 2)
            strcpy(p1->kind_name, "果菜类");
        else if (i == 3)
            strcpy(p1->kind_name, "瓜类");
        else if (i == 4)
            strcpy(p1->kind_name, "叶菜类");
        else if (i == 5)
            strcpy(p1->kind_name, "菌类");
        p2->right = p1;
        p2 = p1;
    }
    p2->right = NULL;
    return (head); //返回头指针
}

//植物的插入 2
void insert_veg(kind *head, FILE *fp) //creat函数 ：返回值是一个指向student结构体的指针
{
    kind *p;
    int i;
    char buffer[40];
    char *token, *str; //str是从buffer中取出的整行数据，token用来暂存信息;
    char delim[2] = ",";
    veg1 *p1, *p2[6]; //p1用于创造新结点，p2用于记录每个大类遍历到的当前节点;
    p = head->right;
    for (i = 1; i < 6; i++)
    {
        p2[i] = (struct veg1 *)malloc(LEN1); //每一列都有一个表头空节点;
        p2[i]->next = NULL;
        p->down = p2[i];
        p = p->right;
    }
    fseek(fp, 20L, SEEK_CUR); //从表格的第二行开始进行读入
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        p = head->right;
        token = split(str, delim); //第一格不取
        for (i = 1; i < 6; i++)
        {
            token = split(NULL, delim);
            if (token[0] != '\0')
            {
                p1 = (struct veg1 *)malloc(LEN1);
                strcpy(p1->info.name, token);
                p1->flag = 0;
                p1->next = NULL;
                p2[i]->next = p1;
                p2[i] = p1;
            }
        }
        p = p->right;
    }
}

//字符串分割函数类似于strtok，注意若有n个分割符即n+1个数据，此函数将可以有n+2个输出，最后一个输出为NULL 3
char *split(char *strToken, char *strDelimit)
{
    char *p;
    char *pd;
    static char *ps;
    if (strToken != NULL)
    {
        ps = strToken;
        while ((*ps != '\0') && (*ps != '\n'))
        {
            ps++;
        }
        *ps = 'X'; //X为标识符，帮助循环结束
        ps++;
        *ps = '\0';
        ps = strToken;
    }
    p = ps;
    while (*ps != '\0')
    {
        pd = strDelimit;
        while ((*pd != '\0') && (*pd != *ps))
            pd++;
        if (*pd == *ps)
        {
            *ps = '\0';
            ps++;
            return p;
        }
        else
            ps++;
    }
    if (*(ps - 1) == 'X')
    {
        *(ps - 1) = '\0';
        return p;
    }
    return NULL;
}

//添加一个排序主链，用于对蔬菜基本信息表中的蔬菜进行排序和导入大类主链 4
veg1 *sorting_line(FILE *fp)
{
    veg1 *head, *cur, *p;
    char buffer[500];
    char *token, *str; //str是从buffer中取出的整行数据，token用来暂存信息;
    char delim[2] = ",";
    head = (struct veg1 *)malloc(LEN1); //表头空节点;
    cur = head;
    fseek(fp, 35L, SEEK_CUR); //从表格的第二行开始进行读入
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        p = (struct veg1 *)malloc(LEN1);
        token = split(str, delim); //导入总排序号
        p->info.num1 = atoi(token);
        token = split(NULL, delim); //导入蔬菜名称
        strcpy(p->info.name, token);
        token = split(NULL, delim); //导入蔬菜分类码
        p->info.num2 = atoi(token); //字符串转整型函数atoi
        token = split(NULL, delim); //导入营养成分
        strcpy(p->info.nutrition, token);
        cur->next = p;
        cur = p;
        p->next = NULL;
        p->head.next=NULL;
    }
    return head;
}

//找到排序链对应主链节点进行输出 8
void search_main_list(veg1* D_HEAD1[],veg1* p)
{
    int goal;
    veg1* pp;//pp为操作当前p所指向信息的分类下属链的指针；
    goal=p->info.num2;
    pp=D_HEAD1[goal-1]->next;//D_HEAD由0开始编码。
    while(1)
    {
        if(strcmp((pp->info.name),(p->info.name))==0)
        {
            pp->info=p->info;
            pp->head=p->head;
            break;
        }
        else
            pp=pp->next;
    }
}

//初始化时，找到当前遍历蔬菜种植信息节点所对应排序链节点进行输出 6
void search_sq_list_grow_1(veg1* sort_head,veg2* p)
{
    veg1* pp;
    veg2 *gp,*pnew,*cur;
    pp=sort_head->next;
    while(1)
    {
        if(pp->info.num1==p->plant_info.num2)
        {
            strcpy(p->plant_info.name,pp->info.name);
            cur=&(pp->head);
            gp=cur->next;
            while((gp!=NULL)&&(gp->plant_info.year>p->plant_info.year))
            {
                cur=gp;
                gp=gp->next;
            }
            pnew=(struct veg2*)malloc(LEN2);
            pnew->next=NULL;
            pnew->plant_info=p->plant_info;
            pnew->next=cur->next;
            cur->next=pnew;
            break;
        }
        else
            pp=pp->next;
    }
}

//重新排序时，找到当前遍历蔬菜种植信息节点所对应排序链节点进行输出 7
void search_sq_list_grow_2(veg1* sort_head,veg2* p)
{
    veg1* pp;
    veg2 *gp,*pnew,*cur;
    pp=sort_head->next;
    while(1)
    {
        if(strcmp((pp->info.name),(p->plant_info.name))==0)
        {
            p->plant_info.num2=pp->info.num1;
            cur=&(pp->head);
            gp=cur->next;
            while((gp!=NULL)&&(gp->plant_info.year>p->plant_info.year))//数据年份降序排列
            {
                cur=gp;
                gp=gp->next;
            }
            pnew=(struct veg2*)malloc(LEN2);
            pnew->next=NULL;
            pnew->plant_info=p->plant_info;
            pnew->next=cur->next;
            cur->next=pnew;
            break;
        }
        else
            pp=pp->next;
    }
}

//导入植物种植信息表 5
veg2* loading_grow_infolist(FILE* fp,veg1* sort_head)
{
    int i=1;
    veg2 *p,*cur,*head;
    char *str,*token;
    char buffer[200];
    char delim[2] = ",";
    head = (struct veg2 *)malloc(LEN2);
    cur=head;
    fseek(fp, 42L, SEEK_CUR); //从表格的第二行开始进行读入
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        p = (struct veg2 *)malloc(LEN2);
        token = split(str, delim); //导入蔬菜种植信息排序号
        p->plant_info.num1=i;
        token = split(NULL, delim); //蔬菜基本信息排序号
        p->plant_info.num2 = atoi(token);
        token = split(NULL, delim); //导入蔬菜种植面积
        p->plant_info.area = atoi(token); //字符串转整型函数atoi
        token = split(NULL, delim); //导入收获重量
        p->plant_info.weight=atoi(token);
        token = split(NULL, delim); //导入种植年份
        p->plant_info.year=atoi(token);
        cur->next = p;
        cur = p;
        p->next = NULL;
        search_sq_list_grow_1(sort_head,p);
        i++;
    }
    return head;
}

//保存前三张表 9
void save_info1(veg1* D_head1[5],veg1* sort_head,veg2* gr_head)
{
    veg1 *pp[6];//用于控制主链下属的分链
    int i;//flag用于控制第一章表第一行的特殊情况
    FILE* fp;
    veg1* p1;//操控基本信息排序主链
    veg2* p2;//操控种植信息排序主链

    //第一张表格保存
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\蔬菜种类信息表.csv", "w");
    if (fp == NULL)
    {
        printf("fail to open the file1!!!\n");
        fclose(fp);
        return;
    }
    fprintf(fp,"分类编号,1,2,3,4,5\n分类名称");
    for(i=1; i<=5; i++)
    {
        pp[i]=D_head1[i-1]->next;
    }
    while(pp[1]!=NULL||pp[2]!=NULL||pp[3]!=NULL||pp[4]!=NULL||pp[5]!=NULL)
    {
        fprintf(fp,",");
        if(pp[1]!=NULL)
        {
            fprintf(fp,"%s,",pp[1]->info.name);
            pp[1]=pp[1]->next;
        }
        else
            fprintf(fp,",");
        if(pp[2]!=NULL)
        {
            fprintf(fp,"%s,",pp[2]->info.name);
            pp[2]=pp[2]->next;
        }
        else
            fprintf(fp,",");
        if(pp[3]!=NULL)
        {
            fprintf(fp,"%s,",pp[3]->info.name);
            pp[3]=pp[3]->next;
        }
        else
            fprintf(fp,",");
        if(pp[4]!=NULL)
        {
            fprintf(fp,"%s,",pp[4]->info.name);
            pp[4]=pp[4]->next;
        }
        else
            fprintf(fp,",");
        if(pp[5]!=NULL)
        {
            fprintf(fp,"%s\n",pp[5]->info.name);
            pp[5]=pp[5]->next;
        }
        else
            fprintf(fp,"\n");
    }
    fclose(fp);

    //第二张表格保存
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\蔬菜基本信息表.csv", "w");
    if (fp == NULL)
    {
        printf("    fail to open the file2!!!\n");
        fclose(fp);
        return;
    }
    p1=sort_head->next;
    fprintf(fp,"蔬菜编号,蔬菜名称,分类码,营养成分\n");
    while(p1!=NULL)
    {
        fprintf(fp,"%d,",p1->info.num1);
        fprintf(fp,"%s,",p1->info.name);
        fprintf(fp,"%d,",p1->info.num2);
        fprintf(fp,"%s\n",p1->info.nutrition);
        p1=p1->next;
    }
    fclose(fp);

    //第三张表格的保存
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\菜农种植信息表.csv", "w");
    if (fp == NULL)
    {
        printf("fail to open the file3!!!\n");
        fclose(fp);
        return;
    }
    p2=gr_head->next;
    fprintf(fp,"编号,蔬菜编号,种植面积,收获重量,种植年份\n");
    while(p2!=NULL)
    {
        fprintf(fp,"%d,",p2->plant_info.num1);
        fprintf(fp,"%d,",p2->plant_info.num2);
        fprintf(fp,"%d,",p2->plant_info.area);
        fprintf(fp,"%d,",p2->plant_info.weight);
        fprintf(fp,"%d\n",p2->plant_info.year);
        p2=p2->next;
    }
    fclose(fp);
}

//修改信息删除信息后序号的重排10
void reposition(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    int i;//常数循环用
    veg2 *gp,*F;//gp修改种植信息链,F用于放生蔬菜基本信息链的种植信息链
    veg1* pp;//操作基本信息排序主链

    //将主链的元素全部放生
    for(i=0; i<5; i++)
    {
        pp=D_head1[i]->next;
        while(pp!=NULL)
        {
            F=pp->head.next;
            if(F!=NULL)
            {
                free(F);
            }
            pp->head.next=NULL;
            pp=pp->next;
        }
    }

    //重排种植信息链的序号
    i=1;
    gp=gr_head->next;
    while(gp!=NULL)
    {
        gp->plant_info.num1=i;
        i++;
        gp=gp->next;
    }

    //重排蔬菜基本信息链，并将每个节点的种植信息链放生
    i=1;
    pp=sort_head->next;
    while(pp!=NULL)
    {
        pp->info.num1=i;
        i++;
        pp->head.next=NULL;
        pp=pp->next;
    }

    //将种植信息链导入蔬菜基本信息链
    gp=gr_head->next;
    while(gp!=NULL)
    {
        search_sq_list_grow_2(sort_head,gp);
        gp=gp->next;
    }

    //将基本信息排序链导入主链
    pp=sort_head->next;
    while(pp!=NULL)
    {
        search_main_list(D_head1,pp);
        pp=pp->next;
    }
}

//加入新的蔬菜11
void add_veg(veg1* D_head1[5],veg1* sort_head)
{
    veg1 *pp;//用于控制主链下属的分链
    veg1 *sp;//用于控制排序主链
    veg1 *pnew;//产生新节点
    int k_num,i;
    char v_name[20],v_nutrition[100];
    sp=sort_head->next;
    i=1;
    printf("    请依次输入蔬菜名称，蔬菜分类码，营养成分（以空格进行分隔）\n    ");
    scanf("%s %d %s",v_name,&k_num,v_nutrition);
    pp=D_head1[k_num-1]->next;//定位到录入蔬菜所处的位置
    while(pp->next!=NULL)
    {
        pp=pp->next;
    }
    while(sp->next!=NULL)
    {
        sp=sp->next;
        i++;
    }
    i++;
    pnew=(struct veg1*)malloc(LEN1);
    pnew->info.num1=i;
    pnew->info.num2=k_num;
    strcpy(pnew->info.name,v_name);
    strcpy(pnew->info.nutrition,v_nutrition);
    sp->next=pnew;
    pp->next=pnew;
    pnew->next=NULL;
    printf("    添加成功\n");
}

//蔬菜种类和基本信息的修改12
void adjust_veg(veg1* D_head1[5],veg1* sort_head)
{
    char goal[40];
    int af_kind,bf_kind,flag;//bf_kind保存蔬菜未修改之前的分类,af_kind保存蔬菜修改之后的分类,flag表示是否找到对应节点。
    veg1 *pp,*cur;//操作主链,cur为pp的上一个节点
    veg1* sp;//操作排序链
    veg1* pnew;//生成新节点
    veg2 head;//用于存放删除节点的head
    printf("    请输入需要修改信息的蔬菜名称：\n    ");
    scanf("%s",goal);
    sp=sort_head->next;
    flag=0;
    while(sp!=NULL)
    {
        if(strcmp(goal,sp->info.name)==0)
        {
            flag=1;
            break;
        }
        else
            sp=sp->next;
    }
    if(flag==0)
    {
        printf("    未找到所需要修改的蔬菜\n");
        return;
    }
    else
    {
        printf("    重新输入蔬菜的基本信息：蔬菜名称，分类码，营养成分（以空格分隔）：\n    ");
        bf_kind=sp->info.num2;//修改之前蔬菜所属类型
        scanf("%s %d %s",sp->info.name,&(sp->info.num2),sp->info.nutrition);
        af_kind=sp->info.num2;
    }
    //找到主链中对应节点
    if(bf_kind==af_kind)
    {
        pp=D_head1[bf_kind-1]->next;
        while(strcmp(pp->info.name,goal)!=0)
            pp=pp->next;
        pp->info=sp->info;

    }
    //若种类改变则先执行删除操作之后再进行添加操作
    else
    {
        cur=D_head1[bf_kind-1];
        pp=cur->next;
        while(strcmp(pp->info.name,goal)!=0)
        {
            cur=pp;
            pp=pp->next;
        }
        cur->next=pp->next;
        head=pp->head;
        free(pp);
        pp=D_head1[af_kind-1]->next;//修改后的分类加到新类型主链分链的最后
        while(pp->next!=NULL)
            pp=pp->next;
        pnew=(struct veg1*)malloc(LEN1);
        pnew->info=sp->info;
        pnew->next=NULL;
        pnew->head=head;
        pp->next=pnew;
    }
    printf("修改成功\n");
}

//删除蔬菜种类和基本信息13
void del_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag,kind,sq;//flag用来标志是否找到需要删除节点,kind用于表示该节点种类,sq表示当前删除节点的次序
    veg1 *pp,*cur;//操作主链,cur为pp的上一个节点
    veg1* sp;//操作排序链
    veg2 *gp,*g_cur;//操作种植信息链,F用于保存需要释放的空间
    printf("    请输入需要删除信息的蔬菜名称：\n    "    );
    scanf("%s",goal);
    sp=sort_head->next;
    cur=sort_head;
    flag=0;
    while(sp!=NULL)
    {
        if(strcmp(goal,sp->info.name)==0)
        {
            flag=1;
            break;
        }
        else
        {
            cur=sp;
            sp=sp->next;
        }
    }
    if(flag==0)
    {
        printf("    未找到所需要删除的蔬菜\n");
        return;
    }
    else
    {
        kind=sp->info.num2;//该节点种类
        cur->next=sp->next;
        free(sp);
    }
    //删除主链中该节点
    cur=D_head1[kind-1];
    pp=cur->next;
    while(pp!=NULL)
    {
        if(strcmp(goal,pp->info.name)==0)
            break;
        else
        {
            cur=pp;
            pp=pp->next;
        }
    }
    sq=pp->info.num1;
    cur->next=pp->next;
    free(pp);
    //删除种植信息链中的与该植物相关节点
    gp=gr_head->next;
    g_cur=gr_head;
    while(gp!=NULL)
    {
        if(sq==gp->plant_info.num2)
        {
            g_cur->next=gp->next;
            gp=g_cur->next;
        }
        else
        {
            g_cur=gp;
            gp=gp->next;
        }
    }
    reposition(D_head1,sort_head,gr_head);
    printf("    删除成功\n");
}

//蔬菜种植信息的添加14
void add_grow_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag;//flag用来标志是否找到需要导入种植信息节点
    veg1 *sp;//操作排序链
    veg2 *pnew;//生成新节点保存信息
    veg2 *gp;//操作种植信息链
    printf("    请输入需要导入种植信息的蔬菜名称（格式：蔬菜名称）：\n    ");
    scanf("%s",goal);
    sp=sort_head->next;
    flag=0;
    while(sp!=NULL)
    {
        if(strcmp(goal,sp->info.name)==0)
        {
            flag=1;
            break;
        }
        else
        {
            sp=sp->next;
        }
    }
    if(flag==0)
    {
        printf("    未找到需要导入种植信息的蔬菜\n");
        return;
    }
    //输入添加节点的信息
    printf(    "输入种植信息：种植面积，收获重量，种植年份（以空格分隔）：\n"    );
    pnew=(struct veg2*)malloc(LEN2);
    scanf("%d %d %d",&(pnew->plant_info.area),&(pnew->plant_info.weight),&(pnew->plant_info.year));
    strcpy(pnew->plant_info.name,goal);

    //找到序列末尾添加新的节点，并在遍历过程中判断所给蔬菜，与输入年份是否已存在种植信息链之中；
    gp=gr_head->next;
    while(gp->next!=NULL)
    {
        if((strcmp(pnew->plant_info.name,gp->plant_info.name)==0)&&(pnew->plant_info.year==gp->plant_info.year))
        {
            free(gp);
            printf("    当前蔬菜，该时间已存在种植信息，请重新输入时间");
            break;
        }
        else
            gp=gp->next;
    }
    gp->next=pnew;

    //更新主链中信息
    reposition(D_head1,sort_head,gr_head);
    printf("    添加成功\n");
}

//蔬菜种植信息的修改15
void adjust_grow_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag,g_year,af_year,af_area,af_weight;//flag用来标志是否找到需要修改种植信息节点,g_year为修改种植信息的年份
    veg1 *sp;//操作排序链
    veg2 *gp,*gp_D;//gp操作种植信息链,gp_D用于确定修改信息是否和已有信息冲突
    printf("    请输入需要修改种植信息的蔬菜名称，以及修改信息的年份（格式：蔬菜名称（空格）修改信息年份）：\n    ");
    scanf("%s %d",goal,&g_year);
    sp=sort_head->next;
    flag=0;
    while(sp!=NULL)
    {
        if(strcmp(goal,sp->info.name)==0)
        {
            flag=1;
            break;
        }
        else
        {
            sp=sp->next;
        }
    }
    if(flag==0)
    {
        printf("    未找到需要修改种植信息的蔬菜\n");
        return;
    }

    //查找该蔬菜该年份是否存在种植信息
    gp=gr_head->next;
    while((strcmp(goal,gp->plant_info.name)!=0)&&(g_year!=gp->plant_info.year))
    {
        if(gp==NULL)
        {
            printf("    未找到该蔬菜在所输入年份下的种植信息，请新建该年份下的种植信息\n");
        }
        gp=gp->next;
    }

    //输入修改节点的信息
    printf(    "输入修改后的种植信息：种植面积，收获重量，种植年份（以空格分隔）：\n    ");
    scanf("%d %d %d",&af_area,&af_weight,&af_year);
    gp_D=gr_head->next;
    while(gp_D!=NULL)
    {
        if((strcmp(goal,gp_D->plant_info.name)==0)&&(g_year==af_year))
        {
            printf("    当前修改蔬菜，所输入种植年份已存在信息，请修改输入年份\n");
            return;
        }
        else
            gp_D=gp_D->next;
    }

    gp->plant_info.weight=af_weight;
    gp->plant_info.area=af_area;
    gp->plant_info.year=af_year;
    //更新主链中信息
    reposition(D_head1,sort_head,gr_head);
    printf("    修改成功\n");
}

//删除蔬菜种植信息16
void del_grow_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag,g_year;//flag用来标志是否找到需要删除种植信息节点,g_year为删除种植信息的年份
    veg1 *sp;//操作排序链
    veg2 *gp, *cur;//gp操作种植信息链,cur为gp的上一个节点
    printf("    请输入需要删除种植信息的蔬菜名称，以及删除信息的年份（以空格分隔）：\n    ");
    scanf("%s %d",goal,&g_year);
    sp=sort_head->next;
    flag=0;
    while(sp!=NULL)
    {
        if(strcmp(goal,sp->info.name)==0)
        {
            flag=1;
            break;
        }
        else
        {
            sp=sp->next;
        }
    }
    if(flag==0)
    {
        printf("    未找到需要删除种植信息的蔬菜\n");
        return;
    }

    //查找该蔬菜该年份是否存在种植信息,存在则删除
    cur=gr_head;
    gp=gr_head->next;
    while((strcmp(goal,gp->plant_info.name)!=0)&&(g_year!=gp->plant_info.year))
    {
        if(gp==NULL)
        {
            printf("    未找到该蔬菜在所输入年份下的种植信息，请新建该年份下的种植信息\n");
        }
        cur=gp;
        gp=gp->next;
    }
    cur->next=gp->next;
    free(gp);
    gp=NULL;

    //更新主链中信息
    reposition(D_head1,sort_head,gr_head);
    printf("    删除成功\n");
}

//按照分类码进行搜索17
void kind_num_search(veg1* D_head1[])
{
    int num;
    printf("    输入你需要查询的蔬菜类别（格式：按照蔬菜分类码输入）：\n    ");
    scanf("%d",&num);
    veg1* p;
    p=D_head1[num-1]->next;
    if(num>5)
    {
        printf("    无该分类\n");
        return;
    }
    while(p!=NULL)
    {
        printf("    %s\n",p->info.name);
        p=p->next;
    }
}

//按照关键词显示基本信息18
void keyword_basic_info_search(veg1* D_head1[])
{
    char goal[40];//goal为查询关键词
    int i,flag=0;
    veg1 *p;//p用于操作分链
    printf("    输入搜索关键词（格式：蔬菜关键字）：\n    ");
    scanf("%s",goal);
    for(i=0;i<5;i++)
    {
        p=(D_head1[i]->next);
        while(p!=NULL)
        {
            if(strstr(p->info.name,goal)!=NULL)
            {
                flag=1;
                printf("    %d\t%s\t%d\t%s\n",p->info.num1,p->info.name,p->info.num2,p->info.nutrition);
            }
            p=p->next;
        }
    }
    if(flag==0)
        printf("    该关键词无对应蔬菜");

}

//按照种类和所含营养成分查询19
void kind_nutrition_search(veg1* D_head1[])
{
    char goal[40];
    int num,flag;
    flag=0;
    veg1* p;
    printf("    输入需要搜索的分类，营养成分（空格分隔）：\n    ");
    scanf("%d %s",&num,goal);
    p=D_head1[num-1]->next;
    while(p!=NULL)
    {
        if(strstr(p->info.nutrition,goal)!=NULL)
        {
            flag=1;
            printf("    %d\t%s\t%d\t%s\n",p->info.num1,p->info.name,p->info.num2,p->info.nutrition);
        }
        p=p->next;
    }
    if(flag==0)
        printf("    该营养成分关键词在该分类下无对应蔬菜\n");
}

//按照蔬菜名称关键词，和年份查询种植信息20
void name_keyword_year_grow_search(veg1* D_head1[])
{
    char goal[40];//蔬菜名称关键词
    int num,flag;
    int i;
    flag=0;
    veg1* p;
    veg2* pp;//用于搜索当前符合蔬菜部分名称的veg1节点的下属种植信息链是否有符合种植年份要求的节点
    printf("    输入需要搜索种植信息蔬菜部分名称，种植信息年份（空格分隔）：\n    ");
    scanf("%s %d",goal,&num);
    for(i=0;i<5;i++)
    {
        p=D_head1[i]->next;
        while(p!=NULL)
        {
            if(strstr(p->info.name,goal)!=NULL)
            {
                pp=p->head.next;
                while(pp!=NULL)
                {
                    if(num==pp->plant_info.year)
                    {
                        flag=1;
                        printf("    %s\t%d\t%d\t%d\t%d\t%d\n",p->info.name,pp->plant_info.num1,pp->plant_info.num2,pp->plant_info.area,pp->plant_info.weight,pp->plant_info.year);
                    }
                    pp=pp->next;
                }
            }
            p=p->next;
        }
    }
    if(flag==0)
        printf("    找不到这样的种植信息\n");
}

//按蔬菜名称进行种植信息查询21
void name_grow_search(veg1* D_head1[])
{
    char goal[40];
    int flag,i;
    flag=0;
    veg1* p;
    veg2* pp;
    printf("    输入需要搜索种植信息的蔬菜名称（格式：蔬菜名称）：\n    ");
    scanf("%s",goal);
    for(i=0;i<5;i++)
    {
        p=D_head1[i]->next;
        while(p!=NULL)
        {
            if(strcmp(p->info.name,goal)==0)
            {
                flag=1;
                pp=p->head.next;
                while(pp!=NULL)
                {
                    printf("    %s\t%d\t%d\t%d\t%d\t%d\n",p->info.name,pp->plant_info.num1,pp->plant_info.num2,pp->plant_info.area,pp->plant_info.weight,pp->plant_info.year);
                    pp=pp->next;
                }
            }
            p=p->next;
        }
    }
    if(flag==0)
        printf("    该蔬菜不存在\n");
}
