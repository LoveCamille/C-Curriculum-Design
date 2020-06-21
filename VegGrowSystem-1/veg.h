#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <graphics.h>
#include <math.h>
#define LEN1 sizeof(struct veg1) //��LEN2����veg1�������ݵĳ���
#define LEN2 sizeof(struct veg2) //��LEN1����veg2�������ݵĳ���

typedef struct f_search//��������ṹ��
{
    int year;//�������
    int above;//�ջ�������Сֵ
    int kind;//��������
}f_search;

typedef struct information1 //�߲˻�����Ϣ
{
    int num1;			 //�߲�������
    int num2;			 //������
    char nutrition[100]; //Ӫ���ɷ�
    char name[20];		 //�߲�����
} information1;

typedef struct information2 //�߲���ֲ��Ϣ
{
    int kind;      //����߲�����
    int num2;      //�߲˻�����Ϣ������
    int num1;	   //�߲���ֲ��Ϣ������
    int area;	   //�߲���ֲ���
    int weight;	   //�߲��ջ�����
    int year;	   //�ջ����
    char name[20]; //�߲�����
} information2;

typedef struct veg2 //�����߲���ֲ��Ϣ��Ľṹ��
{
    struct information2 plant_info; //�ṹ���߲˵�������
    struct veg2 *next;
} veg2;

typedef struct veg1 //��������kind���߲�����
{
    int flag;				  //���ڱ�Ǹõ�Ԫ�Ƿ��Ѿ����з���
    struct information1 info; //�ṹ���߲˵�������
    struct veg1 *next;
    struct veg2 head;       //��ֲ��Ϣ����ͷ
} veg1;

typedef struct kind
{
    int num;
    char kind_name[20]; //��������
    int total_weight;//������
    struct kind *right; //���д���
    struct veg1 *down;	//��������
} kind;


//���������������
kind *creat_trunk();			 //�����������
veg1 *sorting_line(FILE *);		 //���һ���������������ڶ��߲˻�����Ϣ���е��߲˽�������͵����������
void insert_veg(kind *, FILE *); //����������߲�
char *split(char *, char *);     //�ַ����ָ��
void search_main_list(veg1* [],veg1*);  //�ҵ���������Ӧ�����ڵ�������
veg2* loading_grow_infolist(FILE*,veg1*);//����ֲ����ֲ��Ϣ��,��������ֲ��Ϣ������Ϣ��


//�����޸Ĳ���
void search_sq_list_grow_1(veg1*,veg2*); //��ʼ��ʱ���ҵ���ǰ�����߲���ֲ��Ϣ�ڵ�����Ӧ�������ڵ�������
void search_sq_list_grow_2(veg1*,veg2*); //��������ʱ���ҵ���ǰ�����߲���ֲ��Ϣ�ڵ�����Ӧ�������ڵ�������
void save_info1(veg1* [],veg1*,veg2*);//����ǰ���ű����Ϣ
void reposition(veg1* [],veg1*,veg2*);//�޸���Ϣɾ����Ϣ����ŵ�����


//��Ϣ���������޸ģ�ɾ��
void add_veg(veg1*[],veg1* );//�߲�����ͻ�����Ϣ�ļ���
void adjust_veg(veg1*[],veg1* );//�߲�����ͻ�����Ϣ���޸�
void del_veg(veg1* [],veg1*,veg2*); //ɾ���߲�����ͻ�����Ϣ
void add_grow_veg(veg1* [],veg1*,veg2*);//�߲���ֲ��Ϣ�ĵ���
void adjust_grow_veg(veg1* [],veg1*,veg2*);//�߲���ֲ��Ϣ���޸�
void del_grow_veg(veg1* [],veg1*,veg2*); //ɾ���߲���ֲ��Ϣ


//��Ϣ����������
void kind_num_search(veg1* []);//���շ������������
void keyword_basic_info_search(veg1* []);//���չؼ�����ʾ������Ϣ
void kind_nutrition_search(veg1* []);//�������������Ӫ���ɷֲ�ѯ
void name_keyword_year_grow_search(veg1* []);//�����߲����ƹؼ��ʣ�����ݲ�ѯ��ֲ��Ϣ
void name_grow_search(veg1* []);//���߲����ƽ�����ֲ��Ϣ��ѯ



//��Ϣ��ͳ��
void count_kind_grow_info(veg1* []);//ͳ����ֲ��������ջ��������������������
void sort_total(veg2 [], int);//��ͳ�����ݽ��н�������
void count_year_name(veg1*, veg2*);//ͳ��ĳ���߲�һ��ʱ���ڵ�������
void count_kind_veg_weight(veg1* []);//ͳ��ÿ��������߲�������
void count_kind_veg(veg1* []);//ͳ��ÿ��������߲�������
void nutrition_search(veg1* []);//������Ӫ���ɷֲ�ѯ
void graph_show(veg2 []);//չʾͳ��ͼ

//���ݵ���
void output_grow_info(veg1* []);//ͳ�Ʋ���ʾĳ��ʱ��εĸ����߲���ֲ��Ϣ
void latest_threeyear_grow_info(veg1* []);//ͳ����������ڸ����߲˵���ֲ��Ϣ
void free_search(veg1* []);//���������ݣ��������ޣ����

//��������
int max_mark(int maxn);
void put_in(veg1* [],veg1*);
int max_num(veg2 t[]);


void put_in(veg1* D_head1[],veg1* sort_head)
{
    veg1 *sq_p;       //sq_pΪ����������ָ��
    sq_p = sort_head->next;
    while (sq_p != NULL)
    {
        search_main_list(D_head1, sq_p);
        sq_p = sq_p->next;
    }
}

//�ҵ�ͳ����ֲ��Ϣ�������ĺ���33
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

//������ߵ���״ͼ�����ص����32
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

//���������ݣ��������ޣ����31
void free_search(veg1* D_head1[])
{
    int i;
    FILE *fp;
    f_search goal;
    char str[40];
    char name[40];//�ļ���
    char route1[200]="C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\";
    veg1* p;
    veg2* pp;
    printf("    ����������Ҫ���е������ݵ��ļ�����\n");
    printf("    ");
    scanf("%s",name);
    strcat(route1,name);
    strcat(route1,".csv");
    fp = fopen(route1, "w");
    if (fp == NULL)
    {
        printf("    �ļ������ڻ��߱�ռ��\n");
        fclose(fp);
        return ;
    }
    printf("    ������������ϣ������Ķ���Ϊ�ָ�������������ݣ��������ޣ������ĳ������������������0����\n    ");
    scanf("%d��%d��%s",&(goal.year),&(goal.above),str);
    if(strcmp(str,"������")==0)
        goal.kind=1;
    else if(strcmp(str,"������")==0)
        goal.kind=2;
    else if(strcmp(str,"����")==0)
        goal.kind=3;
    else if(strcmp(str,"Ҷ����")==0)
        goal.kind=4;
    else if(strcmp(str,"����")==0)
        goal.kind=5;
    else
        goal.kind=0;
    system("cls");
    printf("    ���\t�߲�����\t��ֲ���\t�ջ�������\n");
    fprintf(fp,"    ���,�߲�����,��ֲ���,�ջ�������\n");

    if(goal.kind<=5&&goal.kind>=1)
    {
        p=D_head1[goal.kind-1]->next;
        if(goal.above==0)
        {
            //�޶����࣬�����������ޣ�����ʱ��
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
            //�޶����࣬�����������ޣ��޶�ʱ��
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
            //�޶����࣬�޶��������ޣ�����ʱ��
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
            //�޶����࣬�޶��������ޣ��޶�ʱ��
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
                //�������࣬�����������ޣ�����ʱ��
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
                //�������࣬�����������ޣ��޶�ʱ��
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
                //�������࣬�޶��������ޣ�����ʱ��
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
                //�޶����࣬�޶��������ޣ��޶�ʱ��
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

//ͳ����������ڸ����߲˵���ֲ��Ϣ30
void latest_threeyear_grow_info(veg1* D_head1[])
{
    FILE* fp;
    veg1* p;
    veg2* pp;
    char str[40];
    int i,j;
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\���߲�����ͳ����Ϣ��.csv", "w");
    if (fp == NULL)
    {
        printf("fail to open the file1!!!\n");
        fclose(fp);
        return ;
    }
    system("cls");
    printf("    ���\t�߲�����\t��������\t��ֲ���\t�ջ�������\n");
    fprintf(fp,"    ���,�߲�����,��������,��ֲ���,�ջ�������\n");
    for(i=0;i<5;i++)
    {
        if(i==0)
            strcpy(str,"������");
        else if(i==1)
            strcpy(str,"������");
        else if(i==2)
            strcpy(str,"����");
        else if(i==3)
            strcpy(str,"Ҷ����");
        else if(i==4)
            strcpy(str,"����");
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

//ͳ�Ʋ���ʾĳʱ��εĸ����߲���ֲ��Ϣ29
void output_grow_info(veg1* D_head1[])
{
    FILE *fp;
    int flag;
    flag=0;
    int begin_t,end_t;
    int num,i,j;//num���ڼ�¼��Ҫ��������ĸ���,goal���ڲ�ѯ��Ŷ�Ӧ���߲�����
    veg1* p;
    veg2* pp;//�ҵ��߲˺������ѯ��ֲ��Ϣ����

    //������ֹ����
    printf("    ��������Ҫͳ���߲�����ֲ��Ϣ�������ֹʱ�䣨��ʽ����ʼʱ�䣨�ո񣩽���ʱ�䣩��\n    ");
    scanf("%d %d",&begin_t,&end_t);
    num=end_t-begin_t+1;
    veg2 total[5][num];//�ڶ�άΪ��ʼ���޼��

    //�ļ�ָ���ʼ��
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\����ݸ����߲���Ϣͳ�Ʊ�.csv", "w");
    if (fp == NULL)
    {
        printf("    fail to open the file1!!!\n");
        fclose(fp);
        return ;
    }

    //����ͳ��
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
            //���ĳ��һ��������������ֲ���ͳ��
        }
    }

    if(flag==0)
    {
        printf("    ��������κ���ֲ��Ϣ");
        return;
    }

    //��ӡ��Ϣ����Ļ���ļ�
    system("cls");
    printf("    ���\t��������\t��ֲ���\t�ջ�������\n");
    fprintf(fp,"    ���,��������,��ֲ���,�ջ�������\n");
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
                printf("    %d\t������\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,������,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==1)
            {
                printf("    %d\t������\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,������,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==2)
            {
                printf("    %d\t����\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,����,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==3)
            {
                printf("    %d\tҶ����\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,Ҷ����,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
            else if(j==4)
            {
                printf("    %d\t����\t\t%d\t\t%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
                fprintf(fp,"    %d,����,%d,%d\n",i,total[j][i-begin_t].plant_info.area,total[j][i-begin_t].plant_info.weight);
            }
        }
    }
    fclose(fp);

}

//������Ӫ���ɷֲ�ѯ28
void nutrition_search(veg1* D_head1[])
{
    char goal[40];
    int i,flag;
    flag=0;
    veg1* p;
    printf("    ������Ҫ����Ӫ���ɷ֣���ʽ��Ӫ���ɷ֣���\n   ");
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
        printf("    ��Ӫ���ɷֹؼ����޶�Ӧ�߲�\n");
}

//ͳ��ÿ��������߲�������27
void count_kind_veg(veg1* D_head1[])
{
    int veg_kind[5];
    int i,vcount;//vcountΪ������
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
            printf("    ������\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==1)
        {
            printf("    ������\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==2)
        {
            printf("    ����\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==3)
        {
            printf("    Ҷ����\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==4)
        {
            printf("    ����\t�߲���������%d\n",veg_kind[i]);
        }
    }
}

//ͳ��ÿ�������߲�������26
void count_kind_veg_weight(veg1* D_head1[])
{
    int veg_kind[5];
    int i,vcount;//vcountΪ������
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
            printf("    ������\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==1)
        {
            printf("    ������\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==2)
        {
            printf("    ����\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==3)
        {
            printf("    Ҷ����\t�߲���������%d\n",veg_kind[i]);
        }
        else if(i==4)
        {
            printf("    ����\t�߲���������%d\n",veg_kind[i]);
        }
    }
}

//ͳ��һ��ʱ���ڵ�������25
void count_year_name(veg1* sort_head, veg2* gr_head)
{
    int begin_t,end_t;
    int cur_end_t;//����ĳЩ�߲���ĳЩ�����ȱ����Ϣ�ģ�cur_end_t�ӵ�ǰ�߲˵����������𣬽�������ͳ��
    int num,i,j;//num���ڼ�¼��Ҫ��������ĸ���,goal���ڲ�ѯ��Ŷ�Ӧ���߲�����
    veg1* p;
    veg2* pp;//�ҵ��߲˺������ѯ��ֲ��Ϣ����
    //�������ͳ����Ϣ������
    num=0;
    p=sort_head->next;
    while(p!=NULL)
    {
        num++;
        p=p->next;
    }
    veg2 total[num];

    //������ֹ����
    printf("    ������Ҫ��ѯ�������ֹʱ�䣺����ʽ����ʼʱ�䣨�ո񣩽���ʱ�䣩\n    ");
    scanf("%d %d",&begin_t,&end_t);

    //����ͳ��
    p=sort_head->next;
    i=0;
    while(p!=NULL)
    {
        strcpy(total[i].plant_info.name,p->info.name);
        total[i].plant_info.area=0;
        total[i].plant_info.weight=0;
        pp=p->head.next;

        //�ҵ���ֲ��Ϣ������ݽ�����������ҿ������ҵ���ֹ���
        while(pp!=NULL)
        {
            if(pp->plant_info.year <= end_t)
            {
                cur_end_t=pp->plant_info.year;
                break;
            }
            pp=pp->next;
        }

        //����ֹ����ж���ʼ���֮�������Ƿ������Ϣ�������total[i]��
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
    printf("    %d-%d�߲˵���ֲ��Ϣͳ������\n",begin_t,end_t);
    for(i=0;i<num;i++)
    {
        if(strcmp(total[i].plant_info.name,"��")==0)
        {
            printf("    %s \t\t��������%d\t �������%d\n",total[i].plant_info.name,total[i].plant_info.weight,total[i].plant_info.area);
        }
        else
        {
            printf("    %s \t��������%d\t �������%d\n",total[i].plant_info.name,total[i].plant_info.weight,total[i].plant_info.area);
        }
    }
}

//չʾͳ��ͼ24
void graph_show(veg2 t[])
{
    initgraph(1000, 800, 0);
    setcolor(BLACK);
    setbkcolor(WHITE);
    setfillcolor(GREEN);
    //(����߶�,������(Ϊ0��Ϊ����Ӧ),����)��������Ϊ25,��Բ����

    float f;
    int i,tt[5], b,maxn,tt_max,gap;//tΪÿ������߲˵���������ttΪ��������������ֵ��bΪ��������x���꣬maxnΪ������������ֵ
                                    //tt_maxΪ���������Ŀ̶ȣ�gapΪ�̶�֮��Ĳ�ֵw
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
        setfont(15,0,"��Բ");
        xyprintf(b+25,480-tt[i],"%d",t[i].plant_info.weight);
        if(t[i].plant_info.kind==1)
        {
            setfont(25,0,"��Բ");
            outtextxy(b,510,"������");
        }
        else if(t[i].plant_info.kind==2)
        {
            setfont(25,0,"��Բ");
            outtextxy(b,510,"������");
        }
        else if(t[i].plant_info.kind==3)
        {
            setfont(25,0,"��Բ");
            outtextxy(b+12,510,"����");
        }
        else if(t[i].plant_info.kind==4)
        {
            setfont(25,0,"��Բ");
            outtextxy(b,510,"Ҷ����");
        }
        else if(t[i].plant_info.kind==5)
        {
            setfont(25,0,"��Բ");
            outtextxy(b+12,510,"����");
        }
        b += 110;
    }
    setfont(15,0,"��Բ");
    outtextxy(660,495,"�߲�����");
    outtextxy(30,60,"������λ��kg");
    b=500;
    int a=0;

    //��ӡ������̶�
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

//��ͳ�����ݽ��н�������23
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

//ͳ����ֲ��������ջ��������������������22
void count_kind_grow_info(veg1* D_head1[])
{
    veg2 total[5];//���ڼ�¼�����������ֲ��������ջ�������
    veg2* pp;      //���ڱ���ÿ���߲˵���ֲ��Ϣ��
    veg1* p;      //���ڱ������������ķ���
    int i;
    int goal;
    printf("    ������Ҫͳ�Ƶ���ݣ���ʽ����ݣ���\n    ");
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
            printf("    ������\t��������%d\t �������%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==2)
        {
            printf("    ������\t��������%d\t �������%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==3)
        {
            printf("    ����\t��������%d\t �������%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==4)
        {
            printf("    Ҷ����\t��������%d\t �������%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
        else if(total[i].plant_info.kind==5)
        {
            printf("    ����\t��������%d\t �������%d\n",total[i].plant_info.weight,total[i].plant_info.area);
        }
    }
    graph_show(total);
}

//��������� 1
kind *creat_trunk()
{
    int i;
    struct kind *head;
    struct kind *p1, *p2;
    head = (struct kind *)malloc(sizeof(kind)); //��ͷ�սڵ㣬���Բ���ֵ�����߸�ֵһ���ò�����ֵ
    p2 = head;
    for (i = 1; i < 6; i++)
    {
        p1 = (struct kind *)malloc(sizeof(kind));
        p1->num = i;
        p1->total_weight=0;
        p1->right = NULL;
        p1->down = NULL;
        if (i == 1)
            strcpy(p1->kind_name, "������");
        else if (i == 2)
            strcpy(p1->kind_name, "������");
        else if (i == 3)
            strcpy(p1->kind_name, "����");
        else if (i == 4)
            strcpy(p1->kind_name, "Ҷ����");
        else if (i == 5)
            strcpy(p1->kind_name, "����");
        p2->right = p1;
        p2 = p1;
    }
    p2->right = NULL;
    return (head); //����ͷָ��
}

//ֲ��Ĳ��� 2
void insert_veg(kind *head, FILE *fp) //creat���� ������ֵ��һ��ָ��student�ṹ���ָ��
{
    kind *p;
    int i;
    char buffer[40];
    char *token, *str; //str�Ǵ�buffer��ȡ�����������ݣ�token�����ݴ���Ϣ;
    char delim[2] = ",";
    veg1 *p1, *p2[6]; //p1���ڴ����½�㣬p2���ڼ�¼ÿ������������ĵ�ǰ�ڵ�;
    p = head->right;
    for (i = 1; i < 6; i++)
    {
        p2[i] = (struct veg1 *)malloc(LEN1); //ÿһ�ж���һ����ͷ�սڵ�;
        p2[i]->next = NULL;
        p->down = p2[i];
        p = p->right;
    }
    fseek(fp, 20L, SEEK_CUR); //�ӱ��ĵڶ��п�ʼ���ж���
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        p = head->right;
        token = split(str, delim); //��һ��ȡ
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

//�ַ����ָ��������strtok��ע������n���ָ����n+1�����ݣ��˺�����������n+2����������һ�����ΪNULL 3
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
        *ps = 'X'; //XΪ��ʶ��������ѭ������
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

//���һ���������������ڶ��߲˻�����Ϣ���е��߲˽�������͵���������� 4
veg1 *sorting_line(FILE *fp)
{
    veg1 *head, *cur, *p;
    char buffer[500];
    char *token, *str; //str�Ǵ�buffer��ȡ�����������ݣ�token�����ݴ���Ϣ;
    char delim[2] = ",";
    head = (struct veg1 *)malloc(LEN1); //��ͷ�սڵ�;
    cur = head;
    fseek(fp, 35L, SEEK_CUR); //�ӱ��ĵڶ��п�ʼ���ж���
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        p = (struct veg1 *)malloc(LEN1);
        token = split(str, delim); //�����������
        p->info.num1 = atoi(token);
        token = split(NULL, delim); //�����߲�����
        strcpy(p->info.name, token);
        token = split(NULL, delim); //�����߲˷�����
        p->info.num2 = atoi(token); //�ַ���ת���ͺ���atoi
        token = split(NULL, delim); //����Ӫ���ɷ�
        strcpy(p->info.nutrition, token);
        cur->next = p;
        cur = p;
        p->next = NULL;
        p->head.next=NULL;
    }
    return head;
}

//�ҵ���������Ӧ�����ڵ������� 8
void search_main_list(veg1* D_HEAD1[],veg1* p)
{
    int goal;
    veg1* pp;//ppΪ������ǰp��ָ����Ϣ�ķ�����������ָ�룻
    goal=p->info.num2;
    pp=D_HEAD1[goal-1]->next;//D_HEAD��0��ʼ���롣
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

//��ʼ��ʱ���ҵ���ǰ�����߲���ֲ��Ϣ�ڵ�����Ӧ�������ڵ������� 6
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

//��������ʱ���ҵ���ǰ�����߲���ֲ��Ϣ�ڵ�����Ӧ�������ڵ������� 7
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
            while((gp!=NULL)&&(gp->plant_info.year>p->plant_info.year))//������ݽ�������
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

//����ֲ����ֲ��Ϣ�� 5
veg2* loading_grow_infolist(FILE* fp,veg1* sort_head)
{
    int i=1;
    veg2 *p,*cur,*head;
    char *str,*token;
    char buffer[200];
    char delim[2] = ",";
    head = (struct veg2 *)malloc(LEN2);
    cur=head;
    fseek(fp, 42L, SEEK_CUR); //�ӱ��ĵڶ��п�ʼ���ж���
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        p = (struct veg2 *)malloc(LEN2);
        token = split(str, delim); //�����߲���ֲ��Ϣ�����
        p->plant_info.num1=i;
        token = split(NULL, delim); //�߲˻�����Ϣ�����
        p->plant_info.num2 = atoi(token);
        token = split(NULL, delim); //�����߲���ֲ���
        p->plant_info.area = atoi(token); //�ַ���ת���ͺ���atoi
        token = split(NULL, delim); //�����ջ�����
        p->plant_info.weight=atoi(token);
        token = split(NULL, delim); //������ֲ���
        p->plant_info.year=atoi(token);
        cur->next = p;
        cur = p;
        p->next = NULL;
        search_sq_list_grow_1(sort_head,p);
        i++;
    }
    return head;
}

//����ǰ���ű� 9
void save_info1(veg1* D_head1[5],veg1* sort_head,veg2* gr_head)
{
    veg1 *pp[6];//���ڿ������������ķ���
    int i;//flag���ڿ��Ƶ�һ�±��һ�е��������
    FILE* fp;
    veg1* p1;//�ٿػ�����Ϣ��������
    veg2* p2;//�ٿ���ֲ��Ϣ��������

    //��һ�ű�񱣴�
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\�߲�������Ϣ��.csv", "w");
    if (fp == NULL)
    {
        printf("fail to open the file1!!!\n");
        fclose(fp);
        return;
    }
    fprintf(fp,"������,1,2,3,4,5\n��������");
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

    //�ڶ��ű�񱣴�
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\�߲˻�����Ϣ��.csv", "w");
    if (fp == NULL)
    {
        printf("    fail to open the file2!!!\n");
        fclose(fp);
        return;
    }
    p1=sort_head->next;
    fprintf(fp,"�߲˱��,�߲�����,������,Ӫ���ɷ�\n");
    while(p1!=NULL)
    {
        fprintf(fp,"%d,",p1->info.num1);
        fprintf(fp,"%s,",p1->info.name);
        fprintf(fp,"%d,",p1->info.num2);
        fprintf(fp,"%s\n",p1->info.nutrition);
        p1=p1->next;
    }
    fclose(fp);

    //�����ű��ı���
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\��ũ��ֲ��Ϣ��.csv", "w");
    if (fp == NULL)
    {
        printf("fail to open the file3!!!\n");
        fclose(fp);
        return;
    }
    p2=gr_head->next;
    fprintf(fp,"���,�߲˱��,��ֲ���,�ջ�����,��ֲ���\n");
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

//�޸���Ϣɾ����Ϣ����ŵ�����10
void reposition(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    int i;//����ѭ����
    veg2 *gp,*F;//gp�޸���ֲ��Ϣ��,F���ڷ����߲˻�����Ϣ������ֲ��Ϣ��
    veg1* pp;//����������Ϣ��������

    //��������Ԫ��ȫ������
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

    //������ֲ��Ϣ�������
    i=1;
    gp=gr_head->next;
    while(gp!=NULL)
    {
        gp->plant_info.num1=i;
        i++;
        gp=gp->next;
    }

    //�����߲˻�����Ϣ��������ÿ���ڵ����ֲ��Ϣ������
    i=1;
    pp=sort_head->next;
    while(pp!=NULL)
    {
        pp->info.num1=i;
        i++;
        pp->head.next=NULL;
        pp=pp->next;
    }

    //����ֲ��Ϣ�������߲˻�����Ϣ��
    gp=gr_head->next;
    while(gp!=NULL)
    {
        search_sq_list_grow_2(sort_head,gp);
        gp=gp->next;
    }

    //��������Ϣ��������������
    pp=sort_head->next;
    while(pp!=NULL)
    {
        search_main_list(D_head1,pp);
        pp=pp->next;
    }
}

//�����µ��߲�11
void add_veg(veg1* D_head1[5],veg1* sort_head)
{
    veg1 *pp;//���ڿ������������ķ���
    veg1 *sp;//���ڿ�����������
    veg1 *pnew;//�����½ڵ�
    int k_num,i;
    char v_name[20],v_nutrition[100];
    sp=sort_head->next;
    i=1;
    printf("    �����������߲����ƣ��߲˷����룬Ӫ���ɷ֣��Կո���зָ���\n    ");
    scanf("%s %d %s",v_name,&k_num,v_nutrition);
    pp=D_head1[k_num-1]->next;//��λ��¼���߲�������λ��
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
    printf("    ��ӳɹ�\n");
}

//�߲�����ͻ�����Ϣ���޸�12
void adjust_veg(veg1* D_head1[5],veg1* sort_head)
{
    char goal[40];
    int af_kind,bf_kind,flag;//bf_kind�����߲�δ�޸�֮ǰ�ķ���,af_kind�����߲��޸�֮��ķ���,flag��ʾ�Ƿ��ҵ���Ӧ�ڵ㡣
    veg1 *pp,*cur;//��������,curΪpp����һ���ڵ�
    veg1* sp;//����������
    veg1* pnew;//�����½ڵ�
    veg2 head;//���ڴ��ɾ���ڵ��head
    printf("    ��������Ҫ�޸���Ϣ���߲����ƣ�\n    ");
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
        printf("    δ�ҵ�����Ҫ�޸ĵ��߲�\n");
        return;
    }
    else
    {
        printf("    ���������߲˵Ļ�����Ϣ���߲����ƣ������룬Ӫ���ɷ֣��Կո�ָ�����\n    ");
        bf_kind=sp->info.num2;//�޸�֮ǰ�߲���������
        scanf("%s %d %s",sp->info.name,&(sp->info.num2),sp->info.nutrition);
        af_kind=sp->info.num2;
    }
    //�ҵ������ж�Ӧ�ڵ�
    if(bf_kind==af_kind)
    {
        pp=D_head1[bf_kind-1]->next;
        while(strcmp(pp->info.name,goal)!=0)
            pp=pp->next;
        pp->info=sp->info;

    }
    //������ı�����ִ��ɾ������֮���ٽ�����Ӳ���
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
        pp=D_head1[af_kind-1]->next;//�޸ĺ�ķ���ӵ��������������������
        while(pp->next!=NULL)
            pp=pp->next;
        pnew=(struct veg1*)malloc(LEN1);
        pnew->info=sp->info;
        pnew->next=NULL;
        pnew->head=head;
        pp->next=pnew;
    }
    printf("�޸ĳɹ�\n");
}

//ɾ���߲�����ͻ�����Ϣ13
void del_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag,kind,sq;//flag������־�Ƿ��ҵ���Ҫɾ���ڵ�,kind���ڱ�ʾ�ýڵ�����,sq��ʾ��ǰɾ���ڵ�Ĵ���
    veg1 *pp,*cur;//��������,curΪpp����һ���ڵ�
    veg1* sp;//����������
    veg2 *gp,*g_cur;//������ֲ��Ϣ��,F���ڱ�����Ҫ�ͷŵĿռ�
    printf("    ��������Ҫɾ����Ϣ���߲����ƣ�\n    "    );
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
        printf("    δ�ҵ�����Ҫɾ�����߲�\n");
        return;
    }
    else
    {
        kind=sp->info.num2;//�ýڵ�����
        cur->next=sp->next;
        free(sp);
    }
    //ɾ�������иýڵ�
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
    //ɾ����ֲ��Ϣ���е����ֲ����ؽڵ�
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
    printf("    ɾ���ɹ�\n");
}

//�߲���ֲ��Ϣ�����14
void add_grow_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag;//flag������־�Ƿ��ҵ���Ҫ������ֲ��Ϣ�ڵ�
    veg1 *sp;//����������
    veg2 *pnew;//�����½ڵ㱣����Ϣ
    veg2 *gp;//������ֲ��Ϣ��
    printf("    ��������Ҫ������ֲ��Ϣ���߲����ƣ���ʽ���߲����ƣ���\n    ");
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
        printf("    δ�ҵ���Ҫ������ֲ��Ϣ���߲�\n");
        return;
    }
    //������ӽڵ����Ϣ
    printf(    "������ֲ��Ϣ����ֲ������ջ���������ֲ��ݣ��Կո�ָ�����\n"    );
    pnew=(struct veg2*)malloc(LEN2);
    scanf("%d %d %d",&(pnew->plant_info.area),&(pnew->plant_info.weight),&(pnew->plant_info.year));
    strcpy(pnew->plant_info.name,goal);

    //�ҵ�����ĩβ����µĽڵ㣬���ڱ����������ж������߲ˣ�����������Ƿ��Ѵ�����ֲ��Ϣ��֮�У�
    gp=gr_head->next;
    while(gp->next!=NULL)
    {
        if((strcmp(pnew->plant_info.name,gp->plant_info.name)==0)&&(pnew->plant_info.year==gp->plant_info.year))
        {
            free(gp);
            printf("    ��ǰ�߲ˣ���ʱ���Ѵ�����ֲ��Ϣ������������ʱ��");
            break;
        }
        else
            gp=gp->next;
    }
    gp->next=pnew;

    //������������Ϣ
    reposition(D_head1,sort_head,gr_head);
    printf("    ��ӳɹ�\n");
}

//�߲���ֲ��Ϣ���޸�15
void adjust_grow_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag,g_year,af_year,af_area,af_weight;//flag������־�Ƿ��ҵ���Ҫ�޸���ֲ��Ϣ�ڵ�,g_yearΪ�޸���ֲ��Ϣ�����
    veg1 *sp;//����������
    veg2 *gp,*gp_D;//gp������ֲ��Ϣ��,gp_D����ȷ���޸���Ϣ�Ƿ��������Ϣ��ͻ
    printf("    ��������Ҫ�޸���ֲ��Ϣ���߲����ƣ��Լ��޸���Ϣ����ݣ���ʽ���߲����ƣ��ո��޸���Ϣ��ݣ���\n    ");
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
        printf("    δ�ҵ���Ҫ�޸���ֲ��Ϣ���߲�\n");
        return;
    }

    //���Ҹ��߲˸�����Ƿ������ֲ��Ϣ
    gp=gr_head->next;
    while((strcmp(goal,gp->plant_info.name)!=0)&&(g_year!=gp->plant_info.year))
    {
        if(gp==NULL)
        {
            printf("    δ�ҵ����߲�������������µ���ֲ��Ϣ�����½�������µ���ֲ��Ϣ\n");
        }
        gp=gp->next;
    }

    //�����޸Ľڵ����Ϣ
    printf(    "�����޸ĺ����ֲ��Ϣ����ֲ������ջ���������ֲ��ݣ��Կո�ָ�����\n    ");
    scanf("%d %d %d",&af_area,&af_weight,&af_year);
    gp_D=gr_head->next;
    while(gp_D!=NULL)
    {
        if((strcmp(goal,gp_D->plant_info.name)==0)&&(g_year==af_year))
        {
            printf("    ��ǰ�޸��߲ˣ���������ֲ����Ѵ�����Ϣ�����޸��������\n");
            return;
        }
        else
            gp_D=gp_D->next;
    }

    gp->plant_info.weight=af_weight;
    gp->plant_info.area=af_area;
    gp->plant_info.year=af_year;
    //������������Ϣ
    reposition(D_head1,sort_head,gr_head);
    printf("    �޸ĳɹ�\n");
}

//ɾ���߲���ֲ��Ϣ16
void del_grow_veg(veg1* D_head1[],veg1* sort_head,veg2* gr_head)
{
    char goal[40];
    int flag,g_year;//flag������־�Ƿ��ҵ���Ҫɾ����ֲ��Ϣ�ڵ�,g_yearΪɾ����ֲ��Ϣ�����
    veg1 *sp;//����������
    veg2 *gp, *cur;//gp������ֲ��Ϣ��,curΪgp����һ���ڵ�
    printf("    ��������Ҫɾ����ֲ��Ϣ���߲����ƣ��Լ�ɾ����Ϣ����ݣ��Կո�ָ�����\n    ");
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
        printf("    δ�ҵ���Ҫɾ����ֲ��Ϣ���߲�\n");
        return;
    }

    //���Ҹ��߲˸�����Ƿ������ֲ��Ϣ,������ɾ��
    cur=gr_head;
    gp=gr_head->next;
    while((strcmp(goal,gp->plant_info.name)!=0)&&(g_year!=gp->plant_info.year))
    {
        if(gp==NULL)
        {
            printf("    δ�ҵ����߲�������������µ���ֲ��Ϣ�����½�������µ���ֲ��Ϣ\n");
        }
        cur=gp;
        gp=gp->next;
    }
    cur->next=gp->next;
    free(gp);
    gp=NULL;

    //������������Ϣ
    reposition(D_head1,sort_head,gr_head);
    printf("    ɾ���ɹ�\n");
}

//���շ������������17
void kind_num_search(veg1* D_head1[])
{
    int num;
    printf("    ��������Ҫ��ѯ���߲���𣨸�ʽ�������߲˷��������룩��\n    ");
    scanf("%d",&num);
    veg1* p;
    p=D_head1[num-1]->next;
    if(num>5)
    {
        printf("    �޸÷���\n");
        return;
    }
    while(p!=NULL)
    {
        printf("    %s\n",p->info.name);
        p=p->next;
    }
}

//���չؼ�����ʾ������Ϣ18
void keyword_basic_info_search(veg1* D_head1[])
{
    char goal[40];//goalΪ��ѯ�ؼ���
    int i,flag=0;
    veg1 *p;//p���ڲ�������
    printf("    ���������ؼ��ʣ���ʽ���߲˹ؼ��֣���\n    ");
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
        printf("    �ùؼ����޶�Ӧ�߲�");

}

//�������������Ӫ���ɷֲ�ѯ19
void kind_nutrition_search(veg1* D_head1[])
{
    char goal[40];
    int num,flag;
    flag=0;
    veg1* p;
    printf("    ������Ҫ�����ķ��࣬Ӫ���ɷ֣��ո�ָ�����\n    ");
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
        printf("    ��Ӫ���ɷֹؼ����ڸ÷������޶�Ӧ�߲�\n");
}

//�����߲����ƹؼ��ʣ�����ݲ�ѯ��ֲ��Ϣ20
void name_keyword_year_grow_search(veg1* D_head1[])
{
    char goal[40];//�߲����ƹؼ���
    int num,flag;
    int i;
    flag=0;
    veg1* p;
    veg2* pp;//����������ǰ�����߲˲������Ƶ�veg1�ڵ��������ֲ��Ϣ���Ƿ��з�����ֲ���Ҫ��Ľڵ�
    printf("    ������Ҫ������ֲ��Ϣ�߲˲������ƣ���ֲ��Ϣ��ݣ��ո�ָ�����\n    ");
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
        printf("    �Ҳ�����������ֲ��Ϣ\n");
}

//���߲����ƽ�����ֲ��Ϣ��ѯ21
void name_grow_search(veg1* D_head1[])
{
    char goal[40];
    int flag,i;
    flag=0;
    veg1* p;
    veg2* pp;
    printf("    ������Ҫ������ֲ��Ϣ���߲����ƣ���ʽ���߲����ƣ���\n    ");
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
        printf("    ���߲˲�����\n");
}
