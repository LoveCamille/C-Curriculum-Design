#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct vkindinfo
{
    int kind;
    char info[100];
} vkindinfo;

typedef struct vname
{
    char name[100];
    struct vname *pn;
} vname;

typedef struct vkind
{
    struct vkindinfo a;
    struct vkind *next;
    struct vname *pk;
    } vkind;

typedef struct ginfo
{
    int a;
    int h;
    int y;
} ginfo;

typedef struct growinfo
{
    struct ginfo i;
    struct growinfo *pg;
} growinfo;

typedef struct vnumberinfo
{
    int kind;
    char n[10];
    char u[100];
} vnumberinfo;

typedef struct vnumber
{
    struct vnumberinfo a;
    struct vnumber *next;
    struct growinfo *pb;
} vnumber;

char* lit(char *s, const char *delim);
char* ctail(char *s);
struct vkind *loadvkind(FILE *fp);
struct vnumber *loadvnumber(FILE *fp);
int loadgrowinfo(FILE *fp, struct vnumber *head);
int savevkind(FILE *fp, struct vkind *head);
int savevnumber(FILE *fp, struct vnumber *head);
int savegrowinfo(FILE *fp, struct vnumber *head);
int inputvkind(struct vkind *head, char *v);
int inputvnumber(struct vkind *head1, struct vnumber *head2, struct vnumber *v);
int inputgrowinfo(struct vnumber *head, char *name, struct growinfo *g);
int changevkind(struct vkind *head, char *name);
int changevnumber(struct vkind *head1, struct vnumber *head2, char *name);
int changegrowinfo(struct vnumber *head, char *name, int year);
int devkind(struct vkind *head1, struct vnumber *head2, char *name);
int devnumber(struct vkind *head1, struct vnumber *head2, char *name);
int degrowinfo(struct vnumber *head, char *name, int year);
void freevkind(struct vkind *p);
void freevnumber(struct vnumber *p);
int printvkind(struct vkind *head);
int printvnumber(struct vnumber *head);
int printgrowinfo(struct vnumber *head);
int svkind(struct vkind *head, int t);
int svnumber1(struct vnumber *head, char *n);
int svnumber2(struct vnumber *head, int t, char *u);
int sgrowinfo1(struct vnumber *head, int year, char *n);
int sgrowinfo2(struct vnumber *head, char  *name);
int cvkind(struct vkind *head1, struct vnumber *head2, int year);
int cyear(struct vnumber *head, int start, int end);
int cnumber(struct vkind *head, char *name);
int cnurtrion(struct vnumber *head, char *n);
int cname(struct vkind *head1, vnumber *head2, char *name, int start, int end);
int freesearch(struct vkind *head1, struct vnumber *head2, char *kindname, int kind, char *name, char *u, int y1, int y2, int a1, int a2, int h1, int h2);

char* lit(char *s, const char *delim)
{
    const char *spanp;
    int c, sc;
    char *tok;
    static char *last;

    if (s == NULL && (s = last) == NULL)
    {
        return (NULL);
    }
    c = *s++;
    for (spanp = delim; (sc = *spanp++) != 0;)
    {
        if (c == sc)
        {
            last = s;
            return (NULL);
        }
    }
    if (c == 0)
    {
        last = NULL;
        return (NULL);
    }
    tok = s - 1;
    for (;;)
    {
        c = *s++;
        spanp = delim;
        do
        {
            if ((sc = *spanp++) == c)
            {
                if (c == 0)
                    s = NULL;
                else
                    s[-1] = 0;
                last = s;
                return (tok);
            }
        }
        while (sc != 0);
    }
}

char *ctail(char *s)
{
    int i;
    i = strlen(s);
    char *p;
    p = s;
    int j;
    for (j=0; j<i-1; j++)
    {
        p++;
    }
    if (*(p) == '\n')
    {
        *(p) = '\0';
    }
    return s;
}

struct vkind *loadvkind(FILE *fp)
{
    char buffer[100];
    char *str, *token;
    char delim[2]=",";
    struct vkind *head;
    struct vkind *p1,*p2;
    struct vname *p4,*p5;
    struct vname *p3[50]={NULL};
    int i,j;
    head = (struct vkind *)malloc(sizeof(struct vkind));
    fseek(fp,8L,SEEK_CUR);
    p2 = head;
    str = fgets( buffer, sizeof(buffer), fp);
    str = ctail(str);
    p1 = (struct vkind *)malloc(sizeof(struct vkind));
    token = strtok(str, delim);
    p1->a.kind = atoi(token);
    p2->next = p1;
    p1->next = NULL;
    p1->pk = NULL;
    p2 = p1;
    i = 1;
    token = strtok(NULL, delim);
    while(token != NULL)
    {
        p1 = (struct vkind *)malloc(sizeof(struct vkind));
        p1->a.kind = atoi(token);
        p2->next = p1;
        p1->next = NULL;
        p1->pk = NULL;
        p2 = p1;
        i++;
        token = strtok(NULL, delim);
    }
    j = i;
    fseek(fp,8L,SEEK_CUR);
    str = fgets( buffer, sizeof(buffer), fp);
    str = ctail(str);
    token = strtok(str, delim);
    p1 = head->next;
    strcpy(p1->a.info, token);
    for(i=0; i<j-1; i++)
    {
        p1 = p1->next;
        token = strtok(NULL, delim);
        strcpy(p1->a.info, token);
    }
    fseek(fp,9L,SEEK_CUR);
    str = fgets( buffer, sizeof(buffer), fp);
    str = ctail(str);
    token = lit(str, delim);
    p1 = head->next;
    if (token != NULL)
    {
        p4 = (struct vname *)malloc(sizeof(struct vname));
        p1->pk = p4;
        strcpy(p4->name, token);
        p3[0] = p4;
    }
    else
    {
        p1->pk = NULL;
    }
    for(i=1; i<j ; i++)
    {
        token = lit(NULL, delim);
        if (token!=NULL)
        {
            p1 = p1->next;
            p4 = (struct vname *)malloc(sizeof(struct vname));
            p1->pk = p4;
            strcpy(p4->name, token);
            p3[i] = p4;
        }
        else
        {
            p1 = p1->next;
            p1->pk = NULL;
        }
    }
    fseek(fp, 1L, SEEK_CUR);
    while ((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        str = ctail(str);
        fseek(fp, 1L, SEEK_CUR);
        token = lit(str, delim);
        if (token != NULL)
        {
            p5 = p3[0];
            p4 = (struct vname *)malloc(sizeof(struct vname));
            p5->pn = p4;
            strcpy(p4->name, token);
            p3[0] = p4;
        }
        else
        {
            if (p3[0] != NULL)
            {
                p3[0]->pn = NULL;
            }
        }
        for (i=1; i<j; i++)
        {
            token = lit(NULL, delim);
            if (token!=NULL)
            {
                p5 = p3[i];
                p4 = (struct vname *)malloc(sizeof(struct vname));
                p5->pn = p4;
                strcpy(p4->name, token);
                p3[i] = p4;
            }
            else
            {
                if (p3[i] != NULL)
                {
                    p3[i]->pn=NULL;
                }
            }
        }
    }
    return head;
}

struct vnumber *loadvnumber(FILE *fp)
{
    char buffer[100];
    char *str,*token;
    char delim[2]=",";
    struct vnumber *head;
    struct vnumber *p1,*p2;
    p1 = (struct vnumber *)malloc(sizeof(struct vnumber));
    head = p1;
    fseek(fp, 37L, SEEK_CUR);
    while((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        str = ctail(str);
        fseek(fp, 2L, SEEK_CUR);
        token = lit(str,delim);
        p2 = (struct vnumber *)malloc(sizeof(struct vnumber));
        strcpy(p2->a.n, token);
        token = lit(NULL, delim);
        p2->a.kind = atoi(token);
        token = lit(NULL, delim);
        strcpy(p2->a.u, token);
        p2->pb = NULL;
        p1->next = p2;
        p1 = p2;
    }
    p2->next = NULL;
    return (head);
}

int loadgrowinfo(FILE *fp, struct vnumber *head2)
{
    char buffer[100];
    char *str,*token;
    int t,j;
    char delim[2] = ",";
    struct vnumber *p;
    struct growinfo *p1,*p2;
    fseek(fp, 44L, SEEK_CUR);
    while((str = fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
        str = ctail(str);
        fseek(fp, 2L, SEEK_CUR);
        token = lit(str, delim);
        t = atoi(token);
        p = head2;
        for (j=0; j<t; j++)
        {
            p = p->next;
        }
        if (p->pb != NULL)
        {
            p1 = p->pb;
            while (p1->pg !=NULL)
            {
                p1 = p1->pg;
            }
        }
        p2 = (struct growinfo *)malloc(sizeof(growinfo));
        token = lit(NULL, delim);
        t = atoi(token);
        p2->i.a = t;
        token = lit(NULL, delim);
        t = atoi(token);
        p2->i.h = t;
        token = lit(NULL, delim);
        t = atoi(token);
        p2->i.y = t;
        if(p->pb != NULL)
        {
            p1->pg = p2;
            p2->pg = NULL;
        }
        else
        {
            p->pb = p2;
            p2->pg = NULL;
        }
    }
    return 1;
}

int savevkind(FILE *fp, struct vkind *head)
{
    struct vkind *p1;
    struct vname *p2[50] = {NULL};
    struct vname *p3;
    fseek(fp, 9L, SEEK_CUR);
    int i,j,flag;
    p1 = head;
    while(p1->next != NULL)
    {
        p1 = p1->next;
        if(p1->next != NULL)
        {fprintf(fp, "%d,", p1->a.kind);}
        else
        {
            fprintf(fp, "%d\n", p1->a.kind);
        }
    }
    fseek(fp, 9L, SEEK_CUR);
    p1 =head;
    while(p1->next != NULL)
    {
        p1 = p1->next;
        if(p1->next != NULL)
        {fprintf(fp, "%s,", p1->a.info);}
        else
        {
            fprintf(fp, "%s\n", p1->a.info);
        }
    }
    fseek(fp, 8L, SEEK_CUR);
    p1 = head;
    i = 0;
    while(p1->next != NULL)
    {
        p1 = p1->next;
        p2[i] = p1->pk;
        i++;
    }
    j = i;
    flag = 1;
    while (flag == 1)
    {
        flag = 0;
        for(i=0; i<j; i++)
        {
            p3 = p2[i];
            if(p3 != NULL)
            {
                flag = 1;
            }
        }
        if (flag == 1)
        {
            for(i=0; i<j; i++)
            {
                p3 = p2[i];
                if (p3 != NULL&&i != j-1)
                {
                    fprintf(fp, ",%s", p3->name);
                }
                else if (p3 != NULL&&i == j-1)
                    {
                        fprintf(fp, ",%s\n", p3->name);
                    }
                else if (p3 == NULL &&i == j-1)
                    {
                        fprintf(fp, ",\n");
                    }
                else
                {
                    fprintf(fp, ",");
                }
                if (p3 != NULL)
                {
                    p2[i] = p3->pn;
                }
            }
        }
    }
    return 1;
}

int savevnumber(FILE *fp, struct vnumber *head)
{
    struct vnumber *p1;
    int i = 1;
    fseek(fp, 35L, SEEK_CUR);
    p1 = head->next;
    while(p1 != NULL)
    {
        fprintf(fp, "%d,%s,%d,%s\n", i, p1->a.n, p1->a.kind, p1->a.u);
        p1 = p1->next;
        i++;
    }
    return 1;
}

int savegrowinfo(FILE *fp, struct vnumber *head)
{
    struct growinfo *p1[50];
    int i,j,k,flag;
    struct vnumber *p2;
    i = 0;
    int year = 2010;
    p2 = head->next;
    fseek(fp, 42L, SEEK_CUR);
    while(p2 != NULL)
    {
        p1[i] = p2->pb;
        p2 = p2->next;
        i++;
    }
    j = i;
    flag = 1;
    k = 1;
    while (flag == 1)
    {
        flag = 0;
        for (i=0; i<j; i++)
        {
            if(p1[i] != NULL)
            {
                flag = 1;
            }
        }
        if(flag == 1)
        {
            while(year <= 2019)
            {
                for (i=0; i<j; i++)
                {
                    if(p1[i] != NULL&&p1[i]->i.y == year)
                    {
                        fprintf(fp, "%d,%d,%d,%d,%d\n", k, i+1, p1[i]->i.a, p1[i]->i.h, p1[i]->i.y);
                        p1[i] = p1[i]->pg;
                        k++;
                    }
                }
                year = year+1;
            }
        }
    }
    return 1;
}

int inputvkind(struct vkind *head, char *v)
{
    struct vkind *p1,*p2;
    p1 = head;
    while(p1->next != NULL)
    {
        p1 = p1->next;
    }
    p2 = (struct vkind *)malloc(sizeof(struct vkind));
    if(p2 == NULL)
    {
        return -2;
    }
    strcpy(p2->a.info, v);
    p2->a.kind = p1->a.kind+1;
    p1->next = p2;
    p2->next = NULL;
    p2->pk = NULL;
    return 1;
}

int inputvnumber(struct vkind *head1, struct vnumber *head2, struct vnumber *v)
{
    struct vkind *p1 = NULL;
    struct vnumber *p2 = NULL;
    struct vnumber *p3 = NULL;
    struct vname  *p4 = NULL;
    struct vname  *p5 = NULL;
    int i;
    i = v->a.kind;
    p1 = head1->next;
    while(p1->a.kind != i&&p1->next != NULL)
    {
        p1 = p1->next;
    }
    if(p1->a.kind != i)
    {
        return -1;
    }
    if(p1->pk != NULL)
    {
        p4 = p1->pk;
        while(p4->pn != NULL)
        {
            p4 = p4->pn;
        }
        p5 = (struct vname *)malloc(sizeof(struct vname));
        if(p5 == NULL)
        {
            return -2;
        }
        strcpy(p5->name, v->a.n);
        p4->pn = p5;
        p5->pn = NULL;
    }
    else
    {
        p5 = (struct vname *)malloc(sizeof(struct vname));
        if(p5 == NULL)
        {
            return -2;
        }
        strcpy(p5->name, v->a.n);
        p1->pk = p5;
        p5->pn = NULL;
    }
    p2 = head2->next;
    while(p2->next != NULL)
    {
        p2 = p2->next;
    }
    p3 = (struct vnumber *)malloc(sizeof(struct vnumber));
    if(p3 == NULL)
    {
        return -2;
    }
    *p3 = *v;
    p2->next = p3;
    p3->next = NULL;
    p3->pb = NULL;
    return 1;
}

int inputgrowinfo(struct vnumber *head, char *name, struct growinfo *g)
{
    struct vnumber *p1 = NULL;
    p1 = head->next;
    while((strcmp(p1->a.n, name)) != 0&&p1->next != NULL)
    {
        p1 = p1->next;
    }
    if((strcmp(p1->a.n, name)) != 0)
    {
        return -1;
    }
    int i;
    struct growinfo *p2 = NULL;
    struct growinfo *p3 = NULL;
    struct growinfo *p4 = NULL;
    i = g->i.y;
    p3 = (struct growinfo *)malloc(sizeof(struct growinfo));
    if (p3 == NULL)
    {
        return -2;
    }
    p2 = p1->pb;
    p3->i.a = g->i.a;
    p3->i.h = g->i.h;
    p3->i.y = g->i.y;
    if (p1->pb != NULL&&i >= p2->i.y)
    {
       if (p2->pg == NULL)
       {
           p2->pg = p3;
           p3->pg = NULL;
           return 1;
       }
       else
       {
           while(i>=p2->pg->i.y&&p2->pg->pg != NULL)
           {
               p2 = p2->pg;
           }
           if (i>=p2->pg->i.y)
           {
               p2->pg->pg = p3;
               p3->pg = NULL;
               return 1;
           }
           else
           {
               p4 = p2->pg;
               p2->pg = p3;
               p3->pg = p4;
               return 1;
           }
       }
    }
    else
    {
        p1->pb = p3;
        p3->pg = p2;
        return 1;
    }
}

int changevkind(struct vkind *head, char *name)
{
    struct vkind* p1 = NULL;
    p1 = head->next;
    while((strcmp(p1->a.info, name)) != 0&&p1->next != NULL)
    {
        p1 = p1->next;
    }
    if((strcmp(p1->a.info, name)) != 0)
    {
        return -1;
    }
    char c[100];
    printf("         请输入改变后的名称：");
    scanf("%s",c);
    fflush(stdin);
    strcpy(p1->a.info, c);
    return 1;
}

int changevnumber(struct vkind *head1, struct vnumber *head2, char *name)
{
    struct vnumber *p2 = NULL;
    struct vkind *p1 = NULL;
    struct vkind *p5 = NULL;
    struct vname *p3 = NULL;
    struct vname *p4 = NULL;
    p2 = head2->next;
    while((strcmp(p2->a.n, name)) != 0&&p2->next != NULL)
    {
        p2 = p2->next;
    }
    if((strcmp(p2->a.n, name)) != 0)
    {
        return -1;
    }
    int i = 1;
    int t;
    int k;
    while (i != 0)
    {
        printf("         请选择你要修改的信息：1（蔬菜种类编号） 2（蔬菜名字） 3（蔬菜营养成分） 0（不再进行修改）");
        scanf("%d", &i);
        fflush(stdin);
        p1 = head1->next;
        if (i == 1)
        {
            printf("         请输出新的蔬菜的编号：");
            scanf("%d", &k);
            fflush(stdin);
            while(p1->a.kind != k&&p1->next != NULL)
            {
                p1 = p1->next;
            }
            if (p1->a.kind != k)
            {
                printf("         无效蔬菜编号！\n");
                continue;
            }
            t = p2->a.kind;
            p2->a.kind = k;
            p5 = head1->next;
            while(p5->a.kind != t)
            {
                p5 = p5->next;
            }
            if((strcmp(p5->pk->name, name)) == 0)
            {
                p4 = p5->pk;
                p5->pk = p5->pk->pn;
            }
            else
            {
                p3 = p5->pk;
                while((strcmp(p3->pn->name, name)) != 0)
                {
                    p3 = p3->pn;
                }
                p4 = p3->pn;
                p3->pn = p3->pn->pn;
            }
            if (p1->pk == NULL)
            {
                p1->pk = p4;
                p4->pn = NULL;
            }
            else
            {
                p3 = p1->pk;
                while(p3->pn != NULL)
                {
                    p3 = p3->pn;
                }
                p3->pn =p4;
                p4->pn = NULL;
            }
        }
    }
    return 1;
}

int changegrowinfo(struct vnumber *head, char *name, int year)
{
    struct vnumber *p1 = NULL;
    struct growinfo *p2 = NULL;
    int a,b,c;
    p1 = head->next;
    while((strcmp(p1->a.n, name)) != 0&&p1->next != NULL)
    {
        p1 = p1->next;
    }
    if((strcmp(p1->a.n, name)) != 0)
    {
        return -1;
    }
    p2 = p1->pb;
    if(p2 == NULL)
    {
        return -1;
    }
    while (p2->i.y != year&&p2->pg != NULL)
    {
        p2 = p2->pg;
    }
    if(p2->i.y != year)
    {
        return -1;
    }
    else
    {
        ct:
            printf("请输入修改后的种植信息（面积 收成 年份）：\n");
            scanf("%d %d %d", &a, &b, &c);
            fflush(stdin);
            if(b<0||a<0||c<0)
            {
                printf("错误输入！\n");
                goto ct;
            }
            p2->i.a = a;
            p2->i.h = b;
            p2->i.y = c;
    }
    return 1;
}

void freevkind(struct vkind *p)
{
    struct vkind *p1 = NULL;
    struct vname *p2 = NULL;
    struct vname *p3 = NULL;
    p1 = p->next;
    p->next = p1->next;
    p2 = p1->pk;
    free(p1);
    while(p2 != NULL)
    {
        p3 = p2->pn;
        free(p2);
        p2 = p3;
    }
}

void freevnumber(struct vnumber *p)
{
    struct vnumber *p1 = NULL;
    struct growinfo *p2 = NULL;
    struct growinfo *p3 = NULL;
    p1 = p->next;
    p->next = p1->next;
    p2 = p1->pb;
    free(p1);
    while (p2 != NULL)
    {
        p3 = p2->pg;
        free(p2);
        p2 = p3;
    }
}

int devkind(struct vkind *head1, struct vnumber *head2, char *name)
{
    struct vkind *p1 = NULL;
    struct vnumber *p2 = NULL;
    int i;
    p1 = head1;
    while((strcmp(p1->next->a.info, name)) != 0&&p1->next->next != NULL)
    {
        p1 = p1->next;
    }
    if ((strcmp(p1->next->a.info, name)) != 0)
    {
        return -1;
    }
    i = p1->next->a.kind;
    freevkind(p1);
    p2 = head2;
    while(p2->next != NULL)
    {
        if(p2->next->a.kind == i)
        {
            freevnumber(p2);
        }
        else
        {
            p2 = p2->next;
        }
    }
    return 1;
}

int devnumber(struct vkind *head1, struct vnumber *head2, char *name)
{
    struct vnumber *p2 = NULL;
    struct vkind *p1 = NULL;
    struct vname *p3 = NULL;
    struct vname *p4 = NULL;
    p2 = head2;
    while ((strcmp(p2->next->a.n, name)) != 0&&p2->next->next != NULL)
    {
        p2 = p2->next;
    }
    if ((strcmp(p2->next->a.n, name)) != 0)
    {
        return -1;
    }
    int i;
    i = p2->next->a.kind;
    freevnumber(p2);
    p1 = head1->next;
    while (p1->a.kind != i)
    {
        p1 = p1->next;
    }
    if((strcmp(p1->pk->name, name)) == 0)
    {
        p3 = p1->pk;
        p1->pk = p3->pn;
        free(p3);
    }
    else
    {
        p3 = p1->pk;
        while((strcmp(p3->pn->name, name)) != 0)
        {
            p3 = p3->pn;
        }
        p4 = p3->pn;
        p3->pn = p4->pn;
        free(p4);
    }
    return 1;
}

int degrowinfo(struct vnumber *head, char *name, int year)
{
    struct vnumber *p1 = NULL;
    struct growinfo *p2 = NULL;
    struct growinfo *p3 =NULL;
    p1 = head->next;
    while((strcmp(p1->a.n, name)) != 0&&p1->next != NULL)
    {
        p1 = p1->next;
    }
    if((strcmp(p1->a.n, name)) != 0)
    {
        return -1;
    }
    if(p1->pb == NULL)
    {
        return -1;
    }
    if(p1->pb->i.y == year)
    {
        p2 = p1->pb;
        p1->pb = p2->pg;
        free(p2);
    }
    else
    {
        p2 = p1->pb;
        if (p2->pg == NULL)
        {
            return -1;
        }
        else
        {
            while(p2->pg->i.y != year&&p2->pg->pg != NULL)
            {
                p2 = p2->pg;
            }
            if(p2->pg->i.y != year)
            {
                return -1;
            }
            else
            {
                p3 = p2->pg;
                p2->pg = p3->pg;
                free(p3);
            }
        }
    }
    return 1;
}

int printvkind(struct vkind *head)
{
    struct vkind *p1 = NULL;
    struct vname *p2[50] = {NULL};
    int i = 0;
    int j;
    p1 = head->next;
    printf("分类编号");
    while(p1 != NULL)
    {
        if(p1->next != NULL)
        {
            printf(",%10d", p1->a.kind);
        }
        else
        {
            printf(",%10d\n", p1->a.kind);
        }
        p1 = p1->next;
        i++;
    }
    p1 = head->next;
    printf("分类名称");
    while(p1 != NULL)
    {
        if(p1->next != NULL)
        {
            printf(",%10s", p1->a.info);
        }
        else
        {
            printf(",%10s\n", p1->a.info);
        }
        p1 = p1->next;
    }
    p1 = head->next;
    for (j=0; j<i; j++)
    {
        p2[j] = p1->pk;
        p1 = p1->next;
    }
    int flag = 1;
    printf("蔬菜名称");
    for (j=0; j<i; j++)
        {
            if(p2[j] == NULL&&j != i-1)
            {
                printf(",          ");
            }
            else if(p2[j] == NULL&&j == i-1)
            {
                printf(",          \n");
            }
            else if(p2[j] != NULL&&j != i-1)
            {
                printf(",%10s", p2[j]->name);
                p2[j] = p2[j]->pn;
            }
            else
            {
                printf(",%10s\n", p2[j]->name);
                p2[j] = p2[j]->pn;
            }
        }
    while (flag == 1)
    {
        flag = 0;
        for (j=0; j<i; j++)
        {
            if(p2[j] != NULL)
            {
                flag = 1;
            }
        }
        if ( flag == 0)
        {
            return 1;
        }
        printf("        ");
        for (j=0; j<i; j++)
        {
            if(p2[j] == NULL&&j != i-1)
            {
                printf(",          ");
            }
            else if(p2[j] == NULL&&j == i-1)
            {
                printf(",          \n");
            }
            else if(p2[j] != NULL&&j != i-1)
            {
                printf(",%10s", p2[j]->name);
                p2[j] = p2[j]->pn;
            }
            else
            {
                printf(",%10s\n", p2[j]->name);
                p2[j] = p2[j]->pn;
            }
        }
    }
    return 1;
}

int printvnumber(struct vnumber *head)
{
    struct vnumber *p1 = NULL;
    int i = 1;
    p1 = head->next;
    printf("蔬菜编号,蔬菜名称,分类码,营养成分\n");
    while(p1 != NULL)
    {
        printf("%3d %12s %5d   %s\n", i, p1->a.n, p1->a.kind, p1->a.u);
        i++;
        p1 = p1->next;
    }
    return 1;
}

int printgrowinfo(struct vnumber *head)
{
    struct vnumber *p1 = NULL;
    p1 = head->next;
    int i;
    int j;
    i=1;
    j=1;
    struct growinfo *p2 = NULL;
    printf("编号,蔬菜编号,种植面积,收获重要,种植年份\n");
    while(p1 != NULL)
    {
        p2 = p1->pb;
        while(p2 != NULL)
        {
            printf("%3d %8d %8d %8d %8d\n", i, j, p2->i.a, p2->i.h, p2->i.y);
            p2 = p2->pg;
            i++;
        }
        p1 = p1->next;
        j++;
    }
    return 1;
}

int svkind(struct vkind *head, int t)
{
    struct vkind *p1 = NULL;
    struct vname *p2 = NULL;
    p1 = head->next;
    while(p1 != NULL)
    {
        if(p1->a.kind != t)
        {
            p1 = p1->next;
        }
        else
        {
            break;
        }
    }
    if (p1 == NULL)
    {
        return -1;
    }
    p2 = p1->pk;
    if (p2 == NULL)
    {
        printf("         没有该类型的蔬菜！\n");
        return 1;
    }
    while (p2 != NULL)
    {
        printf("         %s\n",p2->name);
        p2 = p2->pn;
    }
    return 1;
}

int svnumber1(struct vnumber *head, char *n)
{
    int flag = 0;
    char *s = NULL;
    struct vnumber *p1 = NULL;
    p1 = head->next;
    while (p1 != NULL)
    {
        s = strstr(p1->a.n, n);
        if(s == NULL)
        {
            p1 = p1->next;
        }
        else
        {
            printf("%s %d %s\n",p1->a.n, p1->a.kind, p1->a.u);
            p1 = p1->next;
            flag = 1;
        }
    }
    if (flag == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int svnumber2(struct vnumber *head, int t, char *u)
{
    int flag = 0;
    struct vnumber *p1 = NULL;
    char *s = NULL;
    p1 = head->next;
    while(p1 != NULL)
    {
        if(p1->a.kind != t)
        {
            p1 = p1->next;
            continue;
        }
        else
        {
            s = strstr(p1->a.u, u);
            if (s == NULL)
            {
                p1 = p1->next;
                continue;
            }
            else
            {
                printf("%s %d %s\n",p1->a.n, p1->a.kind, p1->a.u);
                p1 = p1->next;
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int sgrowinfo1(struct vnumber *head, int year, char *n)
{
    struct vnumber *p1 = NULL;
    struct growinfo *p2 = NULL;
    char *s =NULL;
    int flag = 0;
    p1 = head->next;
    while (p1 != NULL)
    {
        s = strstr(p1->a.n, n);
        if (s == NULL)
        {
            p1 = p1->next;
            continue;
        }
        p2 = p1->pb;
        while(p2 != NULL)
        {
            if (p2->i.y != year)
            {
                p2 = p2->pg;
            }
            else
            {
                printf("%s %d %d %d\n", p1->a.n, p2->i.a, p2->i.h, p2->i.y);
                p2 = p2->pg;
                flag = 1;
            }
        }
        p1 = p1->next;
    }
    if (flag == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int sgrowinfo2(struct vnumber *head, char *name)
{
    struct vnumber *p1 = NULL;
    int i;
    struct growinfo *p2 =NULL;
    int flag = 0;
    p1 = head->next;
    while (p1 != NULL)
    {
        i = strcmp(p1->a.n, name);
        if (i != 0)
        {
            p1 = p1->next;
            continue;
        }
        flag = 1;
        p2 = p1->pb;
        if (p2 == NULL)
        {
            printf("%s未种植！\n", p1->a.n);
        }
        else
        {
            while(p2 != NULL)
            {
                printf("%s %d %d %d\n", p1->a.n, p2->i.a, p2->i.h, p2->i.y);
                p2 = p2->pg;
            }
        }
        p1 = p1->next;
    }
    if (flag == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int cvkind(struct vkind *head1, struct vnumber *head2, int year)
{
    struct vkind *p1 = NULL;
    struct vnumber *p2 = NULL;
    struct growinfo *p3 = NULL;
    int i;
    int j;
    int k = 0;
    int a[50];
    int h[50];
    int t[50];
    int m,n,s;
    p1 = head1->next;
    while(p1 != NULL)
    {
        k++;
        p1 = p1->next;
    }
    p1 = head1->next;
    for(j=0; j<k; j++)
    {
        t[j] = j;
        a[j] = 0;
        h[j] = 0;
        i = p1->a.kind;
        p2 = head2->next;
        while(p2 != NULL)
        {
            if(p2->a.kind == i)
            {
                p3 = p2->pb;
                while(p3 != NULL)
                {
                    if (p3->i.y == year)
                    {
                        a[j] = a[j]+p3->i.a;
                        h[j] = h[j]+p3->i.h;
                        p3 = p3->pg;
                    }
                    else
                    {
                        p3 = p3->pg;
                    }
                }
                p2 = p2->next;
            }
            else
            {
                p2 = p2->next;
            }
        }
        p1 = p1->next;
    }
    for (m=0; m<k; m++)
    {
        s = h[m];
        for (n=m+1; n<k; n++)
        {
            if(s > h[n])
            {
                s = h[n];
                h[n] = h[m];
                h[m] = s;
                s = t[n];
                t[n] = t[m];
                t[m] = s;
                s = a[n];
                a[n] = a[m];
                a[m] = s;
            }
            s = h[m];
        }
    }
    for(i=0; i<k; i++)
    {
        p1 = head1->next;
        for (j=0; j<t[i]; j++)
        {
            p1 = p1->next;
        }
        printf("%s %d %d %d\n", p1->a.info, a[i], h[i], year);
    }
    int differ;
    int count;
    int count2;
    char pic[20]="■■■■";
    char pic2[20]="          ";
    printf("     %d年各类蔬菜收获重量柱状图（单位：kg）\n",year);
    i = k-1;
    while(i >= 0)
    {
        if (i != 0)
        {differ = (h[i]-h[i-1])/10;}
        else
        {
            differ = h[i];
        }
        for(count=0; count < differ; count++)
        {
            for(count2=0; count2<k; count2++)
            {
                if (count2 >= i)
                {
                    printf("  %-s",pic);
                }
                else
                {
                    printf("%-s",pic2);
                }
            }
            printf("\n");
        }
        i--;
    }
    for(i=0; i<k; i++)
    {
        p1 = head1->next;
        for (j=0; j<t[i]; j++)
        {
            p1 = p1->next;
        }
        printf("     %s", p1->a.info);
    }
    printf("\n");
    printf("         是否需要导入表格中（1（导入） 0（不导入））：");
    int choose;
    scanf("%d", &choose);
    FILE *fp = NULL;
    fp = fopen("C:\\Users\\GYQ\\Desktop\\按年份各类蔬菜信息统计表.csv", "r+");
    if (choose == 0)
    {
        fclose(fp);
        return 1;
    }
    else
    {
        fseek(fp, 47L, SEEK_CUR);
        for(i=0; i<k; i++)
        {
            p1 = head1->next;
            for (j=0; j<t[i]; j++)
            {
                p1 = p1->next;
            }
            fprintf(fp, "%d,%s,%d,%d\n", year, p1->a.info, a[i], h[i]);
        }
        fclose(fp);
        return 1;
    }
}

int cyear(struct vnumber *head, int start, int end)
{
    int a[100];
    int h[100];
    int t[100];
    struct vnumber *p1 = NULL;
    struct growinfo *p2= NULL;
    int i = 0;
    int j;
    int k;
    int s;
    if (start > end)
    {
        return -1;
    }
    p1 = head->next;
    while(p1 != NULL)
    {
        i++;
        p1 = p1->next;
    }
    p1 = head->next;
    for (j=0; j<i; j++)
    {
        a[j] = 0;
        h[j] = 0;
        t[j] = j;
        p2 = p1->pb;
        while(p2 != NULL)
        {
            if(p2->i.y >= start&&p2->i.y <= end)
            {
                a[j] = a[j]+p2->i.a;
                h[j] = h[j]+p2->i.h;
            }
            p2 = p2->pg;
        }
        p1 = p1->next;
    }
    for (j=0; j<i; j++)
    {
        s = h[j];
        for (k=j+1; k<i; k++)
        {
            if(s > h[k])
            {
                s = h[k];
                h[k] = h[j];
                h[j] = s;
                s = t[k];
                t[k] = t[j];
                t[j] = s;
                s = a[k];
                a[k] = a[j];
                a[j] = s;
            }
            s = h[j];
        }
    }
    for(j=0; j<i; j++)
    {
        p1 = head->next;
        for (k=0; k<t[j]; k++)
        {
            p1 = p1->next;
        }
        printf("%s %d %d %d\n", p1->a.n, p1->a.kind, a[j], h[j]);
    }
    return 1;
}

int cnumber(struct vkind *head, char *name)
{
    struct vkind *p1 = NULL;
    char *s =NULL;
    p1 = head->next;
    while(p1 != NULL)
    {
        s = strstr(p1->a.info, name);
        if (s != NULL)
        {
            break;
        }
        p1 = p1->next;
    }
    if (s == NULL)
    {
        return -1;
    }
    struct vname *p2 = NULL;
    p2 = p1->pk;
    int i = 0;
    while(p2 != NULL)
    {
        i++;
        printf("%s\n", p2->name);
        p2 = p2->pn;
    }
    printf("共有%d种\n", i);
    return 1;
}

int cnurtrion(struct vnumber *head, char *u)
{
    int flag = 0;
    char *s = NULL;
    struct vnumber *p1 = NULL;
    p1 = head->next;
    while(p1 != NULL)
    {
        s = strstr(p1->a.u, u);
        if(s != NULL)
        {
            flag = 1;
            printf("%s\n", p1->a.n);
        }
        p1 = p1->next;
    }
    if (flag == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int cname(struct vkind *head1, struct vnumber *head2, char *name, int start, int end)
{
    struct vkind *p1 = NULL;
    struct vnumber *p2 = NULL;
    struct growinfo *p3 = NULL;
    int kind;
    int flag = 0;
    p2 = head2->next;
    p1 = head1->next;
    while((strcmp(p2->a.n, name)) != 0&&p2->next != NULL)
    {
        p2 = p2->next;
    }
    if ((strcmp(p2->a.n, name)) != 0)
    {
        return -1;
    }
    p3 = p2->pb;
    if(p3 == NULL)
    {
        return -2;
    }
    else
    {
        kind = p2->a.kind;
        while(p1->a.kind != kind)
        {
            p1 = p1->next;
        }
        while(p3!=NULL&&p3->i.y>=start&&p3->i.y<=end)
        {
            printf("%d %s %s %d %d\n", p3->i.y, p2->a.n, p1->a.info, p3->i.a, p3->i.h);
            p3 = p3->pg;
            flag = 1;
        }
    }
    if (flag == 0)
    {
        return -2;
    }
    else
    {
        printf("         是否需要导入表格中（1（导入） 0（不导入））：");
    int choose;
    scanf("%d", &choose);
    FILE *fp = NULL;
    fp = fopen("C:\\Users\\GYQ\\Desktop\\按蔬菜名称统计信息表.csv", "r+");
        if (choose == 0)
        {
            fclose(fp);
            return 1;
        }
        else
        {
            fseek(fp, 54L, SEEK_CUR);
            p3 = p2->pb;
            while(p3 != NULL&& p3->i.y>=start&&p3->i.y<=end)
            {

                fprintf(fp, "%d,%s,%s,%d,%d\n", p3->i.y, p2->a.n, p1->a.info, p3->i.a, p3->i.h);
                p3 = p3->pg;
            }
            fclose(fp);
            return 1;
        }
    }
}

int freesearch(struct vkind *head1, struct vnumber *head2, char *kindname, int kind, char *name, char *u, int y1, int y2, int a1, int a2, int h1, int h2)
{
    struct vkind *p1 = NULL;
    struct vnumber *p2 = NULL;
    struct growinfo *p3 = NULL;
    int k = 0;
    int i;
    int flag = 0;
    struct vnumber *p4[50] = {NULL};
    char a[5] = "0";
    if ((strcmp(kindname, a)) == 0)
    {

    }
    else
    {
        p1 = head1->next;
        while((strstr(p1->a.info, kindname)) == NULL&&p1->next != NULL)
        {
            p1 = p1->next;
        }
        if ((strstr(p1->a.info, kindname)) == NULL)
        {
            return -1;
        }
        k = p1->a.kind;
    }
    if(kind == 0)
    {

    }
    else
    {
        p1 = head1->next;
        while(p1->a.kind != kind&&p1->next != NULL)
        {
            p1 = p1->next;
        }
        if (p1->a.kind != kind)
        {
            return -1;
        }
        if (k != 0&&k != kind)
        {
            return -1;
        }
        k = kind;
    }
    p2 = head2->next;
    i = 0;
    if ((strcmp(name, a)) == 0)
    {

    }
    else
    {
        while(p2 != NULL)
        {
            if((strstr(p2->a.n, name)) == NULL)
            {
                p2 = p2->next;
                continue;
            }
            if (p2->a.kind != k&&k != 0)
            {
                p2 = p2->next;
                continue;
            }
            p4[i] = p2;
            p2 = p2->next;
            i++;
            flag = 1;
        }
        if (flag == 0)
        {
            return -1;
        }
        p4[i] = NULL;
    }
    if (p4[0] == 0)
    {
        while(p2 != NULL)
        {
            if (p2->a.kind == k)
            {
                p4[i] = p2;
                i++;
            }
            p2 = p2->next;
        }
    }
    int j = 0;
    int l;
    if ((strcmp(u, a)) == 0)
    {

    }
    else
    {
        while(p4[j] != NULL)
        {
            if((strstr(p4[j]->a.u, u)) == NULL)
            {
                l = j;
                for(; l<i; l++)
                {
                    p4[l] = p4[l+1];
                }
            }
            else
            {
                j++;
            }
        }
    }
    if (p4[0] == NULL)
    {
        return -1;
    }
    j = 0;
    flag = 0;
    while (p4[j] != NULL)
    {
        p3 = p4[j]->pb;
        k = p4[j]->a.kind;
        p1 = head1->next;
        while(p1->a.kind != k)
        {
            p1 = p1->next;
        }
        while (p3 != NULL)
        {
            if((p3->i.a>=a1&&p3->i.a<=a2)||(a2==0&&p3->i.a>=a1)||(a1==0&&a2==0))
            {
                if((p3->i.h>=h1&&p3->i.h<=h2)||(h2==0&&p3->i.h>=h1)||(h1==0&&h2==0))
                {
                    if((p3->i.y>=y1&&p3->i.y<=y2)||(y2==0&&p3->i.y>=y1)||(y1==0&&y2==0)||(y1==0&&p3->i.y<=y2))
                    {
                        flag = 1;
                        printf("%s %d %s %s %d %d %d\n", p1->a.info, p1->a.kind, p4[j]->a.n, p4[j]->a.u, p3->i.y, p3->i.a, p3->i.h);
                    }
                }
            }
            p3 = p3->pg;
        }
        j++;
    }
    if (flag == 0)
    {
        return -1;
    }
    FILE *fp = NULL;
    fp = fopen("C:\\Users\\GYQ\\Desktop\\自由查找.csv", "r+");
    if (fp == NULL)
    {
        fclose(fp);
        return 0;
    }
    printf("         是否保存信息：（1 或 0）：");
    scanf("%d", &i);
    if(i==0)
    {
        fclose(fp);
        return 1;
    }
    else
    {
        fprintf(fp,"蔬菜种类名,分类编号,蔬菜名称,营养成分,种植年份,种植面积,收获重量\n");
        fseek(fp,0L,SEEK_END);
        j = 0;
        while (p4[j] != NULL)
        {
            p3 = p4[j]->pb;
            while (p3 != NULL)
            {
                if((p3->i.a>=a1&&p3->i.a<=a2)||(a2==0&&p3->i.a>=a1)||(a1==0&&a2==0))
                {
                    if((p3->i.h>=h1&&p3->i.h<=h2)||(h2==0&&p3->i.h>=h1)||(h1==0&&h2==0))
                    {
                        if((p3->i.y>=y1&&p3->i.y<=y2)||(y2==0&&p3->i.y>=y1)||(y1==0&&y2==0)||(y1==0&&p3->i.y<=y2))
                        {
                            fprintf(fp, "%s,%d,%s,%s,%d,%d,%d\n", p1->a.info, p1->a.kind, p4[j]->a.n, p4[j]->a.u, p3->i.y, p3->i.a, p3->i.y);
                        }
                    }
                }
                p3 = p3->pg;
            }
            j++;
        }
        fclose(fp);
        return 1;
    }
}

int main()
{
    FILE *fp = NULL;
    struct vkind *head1 = NULL;
    struct vnumber *head2 = NULL;
    struct vnumber ve;
    struct vkind *free1 = NULL;
    struct vkind *free2 = NULL;
    struct vnumber *free3 = NULL;
    struct vnumber *free4 = NULL;
    int k,op,t;
    int r;
    int year;
    int start,end;
    char v[50];
    char v2[50];
    char v3[50];
    int a1,a2;
    int h1,h2;
    struct growinfo g;
    k = 0;
    op = 1;
    fp = fopen("C:\\Users\\GYQ\\Desktop\\蔬菜种类信息表.csv", "r");
    if (fp == NULL)
    {
        printf("          未能打开文件！\n");
        fclose(fp);
        return 0;
    }
    head1 = loadvkind(fp);
    fclose(fp);
    fp = fopen("C:\\Users\\GYQ\\Desktop\\蔬菜基本信息表.csv", "r");
    if (fp == NULL)
    {
        printf("          未能打开文件！\n");
        fclose(fp);
        return 0;
    }
    head2 = loadvnumber(fp);
    fclose(fp);
    fp = fopen("C:\\Users\\GYQ\\Desktop\\菜农种植信息表.csv", "r");
    if (fp == NULL)
    {
        printf("          未能打开文件！\n");
        fclose(fp);
        return 0;
    }
    k = loadgrowinfo(fp, head2);
    fclose(fp);
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("         Menu for Vegetable Management System  \n");
        printf("-------------------------------------------------   \n");
        printf("          Load and Save:                            \n");
        printf("           1. Loadvkind         2. Loadvnumber      \n");
        printf("           3. Loadgrowinfo      4. Savavkind        \n");
        printf("           5. Savavnumber       6. Savagrowinfo     \n\n");
        printf("          DataOperate:                              \n");
        printf("           7. Inputvkind        8. Inputvnumber     \n");
        printf("           9. Inputgrowinfo    10. Changevkind      \n");
        printf("          11. Changevnumber    12. Changegrowinfo   \n");
        printf("          13. Devkind          14. Devnumber        \n");
        printf("          15. Degrowinfo                            \n\n");
        printf("          Print:                                    \n");
        printf("          16. Printvkind       17. Printvnumber     \n");
        printf("          18. Printgrowinfo                         \n\n");
        printf("          Search:                                   \n");
        printf("          19. Searchvkind      20. Searchvnumber1   \n");
        printf("          21. Searchvnumber2   22. Searchgrowinfo1  \n");
        printf("          23. Searchgrowinfo2                     \n\n");
        printf("          Counter:                                  \n");
        printf("          24. Countvkind       25. Countervyaer     \n");
        printf("          26. Counternumber    27. Counternurtrion  \n");
        printf("          28. Countername      29. Freesearch       \n");
        printf("           0. Exit                                  \n");
        printf("-------------------------------------------------   \n");
        printf("          请输入将要进行的操作[0~29]：");
        fflush(stdin);
        k = scanf("%d",&op);
        if (k != 1)
        {
            printf("          无效输入，请重新输入！\n");
            fflush(stdin);
            system("pause");
            continue;
        }
        if(op<0||op>39)
        {
            printf("          无效输入，请重新输入！\n");
            fflush(stdin);
            system("pause");
            continue;
        }
        fflush(stdin);
        switch(op)
        {
        case 1:
            fp = fopen("C:\\Users\\GYQ\\Desktop\\蔬菜种类信息表.csv", "r");
            if (fp == NULL)
            {
                printf("          未能打开文件！\n");
                fclose(fp);
                return 0;
            }
            head1 = loadvkind(fp);
            if(head1 != NULL)
            {
                printf("          加载成功！\n");
            }
            else
            {
                printf("          加载失败！\n");
            }
            system("pause");
            fclose(fp);
            break;
        case 2:
            fp = fopen("C:\\Users\\GYQ\\Desktop\\蔬菜基本信息表.csv", "r");
            if (fp == NULL)
            {
                printf("          未能打开文件！\n");
                fclose(fp);
                return 0;
            }
            head2 = loadvnumber(fp);
            if(head2 != NULL)
            {
                printf("          加载成功！\n");
            }
            else
            {
                printf("          加载失败！\n");
            }
            system("pause");
            fclose(fp);
            break;
        case 3:
            fp = fopen("C:\\Users\\GYQ\\Desktop\\菜农种植信息表.csv", "r");
            if (fp == NULL)
            {
                printf("          未能打开文件！\n");
                fclose(fp);
                return 0;
            }
            k = loadgrowinfo(fp, head2);
            if(k != 0)
            {
                printf("          加载成功！\n");
            }
            else
            {
                printf("          加载失败！\n");
            }
            system("pause");
            fclose(fp);
            break;
        case 4:
            fp = fopen("C:\\Users\\GYQ\\Desktop\\蔬菜种类信息表.csv", "r+");
            if (fp == NULL)
            {
                printf("          未能打开文件！\n");
                fclose(fp);
                return 0;
            }
            k = savevkind(fp, head1);
            if(k != 0)
            {
                printf("          保存成功！\n");
            }
            else
            {
                printf("          保存失败！\n");
            }
            system("pause");
            fclose(fp);
            break;
        case 5:
            fp = fopen("C:\\Users\\GYQ\\Desktop\\蔬菜基本信息表.csv", "r+");
            if (fp == NULL)
            {
                printf("          未能打开文件！\n");
                fclose(fp);
                return 0;
            }
            k = savevnumber(fp, head2);
            if(k != 0)
            {
                printf("          保存成功！\n");
            }
            else
            {
                printf("          保存失败！\n");
            }
            system("pause");
            fclose(fp);
            break;
        case 6:
            fp = fopen("C:\\Users\\GYQ\\Desktop\\菜农种植信息表.csv", "r+");
            if (fp == NULL)
            {
                printf("          未能打开文件！\n");
                fclose(fp);
                return 0;
            }
            k = savegrowinfo(fp, head2);
            if(k != 0)
            {
                printf("          保存成功！\n");
            }
            else
            {
                printf("          保存失败！\n");
            }
            system("pause");
            fclose(fp);
            break;
        case 7:
            printf("          请输入需要增加的蔬菜种类：");
            scanf("%s", v);
            fflush(stdin);
            k = inputvkind(head1, v);
            if (k == 1)
            {
                printf("          添加成功！\n");
            }
            else if (k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 8:
            printf("          请输入需要增加的蔬菜信息（种类编号 名称 营养价值）：");
            r = scanf("%d %s %s", &ve.a.kind, ve.a.n, ve.a.u);
            fflush(stdin);
            if (r != 3)
            {
                printf("         错误输入！\n");
                system("pause");
                continue;
            }
            k = inputvnumber(head1, head2, &ve);
            if (k == 1)
            {
                printf("          添加成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到蔬菜种类！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 9:
            printf("          请输入需要增加的种植信息（蔬菜名称 面积 收获 年份）：");
            r = scanf("%s %d %d %d", v, &g.i.a, &g.i.h, &g.i.y);
            fflush(stdin);
            if (r != 4)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = inputgrowinfo(head2, v, &g);
            if (k == 1)
            {
                printf("          添加成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到蔬菜！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 10:
            printf("          请输入需要修改的蔬菜种类：");
            scanf("%s",v);
            fflush(stdin);
            k = changevkind(head1, v);
            if (k == 1)
            {
                printf("          修改成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到蔬菜种类！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 11:
            printf("          请输入需要修改的蔬菜名称：");
            scanf("%s",v);
            fflush(stdin);
            k = changevnumber(head1, head2, v);
            if (k == 1)
            {
                printf("          修改成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到蔬菜！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 12:
            printf("          请输入需要修改的种植信息（蔬菜名称 年份）：\n");
            r = scanf("%s %d", v, &year);
            fflush(stdin);
            if(r != 2)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = changegrowinfo(head2, v, year);
            if (k == 1)
            {
                printf("          修改成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到对应蔬菜种植信息！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 13:
            printf("          请输入需要删除的蔬菜种类:");
            scanf("%s", v);
            fflush(stdin);
            k = devkind(head1, head2, v);
            if (k == 1)
            {
                printf("         删除成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到对应蔬菜种类信息！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 14:
            printf("          请输入需要删除的蔬菜名称:");
            scanf("%s", v);
            fflush(stdin);
            k = devnumber(head1, head2, v);
            if (k == 1)
            {
                printf("          删除成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到对应蔬菜信息！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 15:
            printf("          请输入需要删除的种植信息（蔬菜名称 种植年份）：\n");
            r = scanf("%s %d", v, &year);
            fflush(stdin);
            if (r != 2)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = degrowinfo(head2, v, year);
            if (k == 1)
            {
                printf("          删除成功！\n");
            }
            else if(k == -1)
            {
                printf("          未找到对应种植信息！\n");
            }
            else if(k == -2)
            {
                printf("          内存分配失败！\n");
            }
            system("pause");
            break;
        case 16:
            k=0;
            k = printvkind(head1);
            if (k == 1)
            {
                printf("         输出成功！\n");
            }
            else
            {
                printf("         输出失败！\n");
            }
            system("pause");
            break;
        case 17:
            k = 0;
            k = printvnumber(head2);
            if (k == 1)
            {
                printf("         输出成功！\n");
            }
            else
            {
                printf("         输出失败！\n");
            }
            system("pause");
            break;
        case 18:
            k = 0;
            k = printgrowinfo(head2);
            if (k == 1)
            {
                printf("         输出成功！\n");
            }
            else
            {
                printf("         输出失败！\n");
            }
            system("pause");
            break;
        case 19:
            k = 0;
            printf("         请输入需要查找的蔬菜种类：");
            r = scanf("%d", &t);
            fflush(stdin);
            if (r != 1)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = svkind(head1, t);
            if (k == 1)
            {
                printf("         查找成功！\n");
            }
            else if (k == -1)
            {
                printf("        未找到类似信息！\n");
            }
            else
            {
                printf("         查找失败！\n");
            }
            system("pause");
            break;
        case 20:
            k = 0;
            printf("         请输入需要查找的蔬菜关键字：");
            scanf("%s", v);
            fflush(stdin);
            k = svnumber1(head2, v);
            if (k == 1)
            {
                printf("         查找成功！\n");
            }
            else if (k == -1)
            {
                printf("        未找到类似信息！\n");
            }
            else
            {
                printf("         查找失败！\n");
            }
            system("pause");
            break;
        case 21:
            k = 0;
            printf("         请输入需要查找的蔬菜分类码 营养成分：");
            r = scanf("%d %s", &t, v);
            fflush(stdin);
            if (r != 2)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = svnumber2(head2, t, v);
            if (k == 1)
            {
                printf("         查找成功！\n");
            }
            else if (k == -1)
            {
                printf("        未找到类似信息！\n");
            }
            else
            {
                printf("         查找失败！\n");
            }
            system("pause");
            break;
        case 22:
            k = 0;
            printf("         请输入需要查找的蔬菜部分名称 年份：");
            r = scanf("%s %d", v, &year);
            fflush(stdin);
            if (r != 2)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = sgrowinfo1(head2, year, v);
            if (k == 1)
            {
                printf("         查找成功！\n");
            }
            else if (k == -1)
            {
                printf("        未找到类似信息！\n");
            }
            else
            {
                printf("         查找失败！\n");
            }
            system("pause");
            break;
        case 23:
            k = 0;
            printf("         请输入需要查找的蔬菜名称：");
            scanf("%s", v);
            fflush(stdin);
            k = sgrowinfo2(head2, v);
            if (k == 1)
            {
                printf("         查找成功！\n");
            }
            else if (k == -1)
            {
                printf("        未找到类似信息！\n");
            }
            else
            {
                printf("         查找失败！\n");
            }
            system("pause");
            break;
        case 24:
            k = 0;
            printf("                请输入需要查找的年份：");
            r = scanf("%d", &year);
            fflush(stdin);
            if (r != 1)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = cvkind(head1, head2, year);
            if(k == 1)
            {
                printf("         统计成功！\n");
            }
            else
            {
                printf("         统计失败！\n");
            }
            system("pause");
            break;
        case 25:
            k = 0;
            printf("                请输入需要查找的年份范围：");
            r = scanf("%d %d", &start, &end);
            fflush(stdin);
            if (r != 2)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            k = cyear(head2, start, end);
            if(k == 1)
            {
                printf("         统计成功！\n");
            }
            else if (k == -1)
            {
                printf("         错误年份范围！\n");
            }
            else
            {
                printf("         统计失败！\n");
            }
            system("pause");
            break;
        case 26:
            k = 0;
            printf("                请输入需要统计的蔬菜种类：");
            scanf("%s", v);
            fflush(stdin);
            k = cnumber(head1, v);
            if(k == 1)
            {
                printf("         统计成功！\n");
            }
            else if (k == -1)
            {
                printf("         没有找到蔬菜类型！\n");
            }
            else
            {
                printf("         统计失败！\n");
            }
            system("pause");
            break;
        case 27:
            k = 0;
            printf("                请输入需要统计的蔬菜营养成分：");
            scanf("%s", v);
            fflush(stdin);
            k = cnurtrion(head2, v);
            if(k == 1)
            {
                printf("         统计成功！\n");
            }
            else if (k == -1)
            {
                printf("         没有找到！\n");
            }
            else
            {
                printf("         统计失败！\n");
            }
            system("pause");
            break;
        case 28:
            k = 0;
            printf("                请输入需要统计的蔬菜名称 时间开始 时间结束：");
            r = scanf("%s %d %d", v, &start, &end);
            fflush(stdin);
            if (r != 3)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            if (start > end)
            {
                printf("         错误输入！\n");
            }
            else
            {
                k = cname(head1, head2, v, start, end);
                if(k == 1)
                {
                    printf("         统计成功！\n");
                }
                else if (k == -1)
                {
                    printf("         没有找到蔬菜！\n");
                }
                else if (k == -2)
                {
                    printf("         未种植！\n");
                }
                else
                {
                    printf("         统计失败！\n");
                }
                system("pause");
                break;
            }
        case 29:
            printf("         请输入自由查询信息（按照一下顺序，若无要求则输入0：蔬菜种类名关键词 分类编号 蔬菜名称关键词 营养成分关键词 种植年份范围 种植面积范围 收获重量范围）：\n");
            r = scanf("%s %d %s %s %d %d %d %d %d %d", v, &t, v2, v3, &start, &end, &a1, &a2, &h1, &h2);
            fflush(stdin);
            if (r != 10)
            {
                printf("         错误输入！\n");
                system("pause");
                break;
            }
            if ((end != 0&&start > end)||(start < 0))
            {
                printf("         错误输入！\n");
            }
            else if ((a2 != 0&&a1 > a2)||(a1 < 0))
            {
                printf("         错误输入！\n");
            }
            else if ((h2 != 0&&h1 > h2)||(h1 < 0))
            {
                printf("         错误输入！\n");
            }
            else
            {
                k = freesearch(head1, head2, v, t, v2, v3, start, end, a1, a2, h1, h2);
                if (k == 1)
                {
                    printf("         查找成功！\n");
                }
                else if (k == -1)
                {
                    printf("         未找到符合条件信息！\n");
                }
                else if (k == 0)
                {
                    printf("         文件操作失败！\n");
                }
                else
                {
                    printf("        程序报错！\n");
                }
            }
            system("pause");
            break;
        case 0:
            break;
        }
        fflush(stdin);
    }
    printf("          欢迎下次使用本系统！再见！\n");
    free1 = head1->next;
    while(free1 != NULL)
    {
        free2 = free1->next;
        freevkind(free1);
        free1 = free2;
    }
    free3 = head2->next;
    while(free3 != NULL)
    {
        free4 = free3->next;
        freevnumber(free3);
        free3 = free4;
    }
    return 0;
}
