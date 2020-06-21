#define SHOW_CONSOLE
#include "veg.h"


int main()
{
    int i;
    kind *head1, *p1; //head1为主链类型头指针,p1用于操作主链
    veg1 *D_head1[5]; //D_head1为主链下属分链头指针
    veg1 *sort_head;  //排序链表表头指针
    //veg1 *tp        //tp为测试指针
    veg2 *gr_head; //蔬菜种植信息排序链表头
    FILE *fp;

    //创建主链
    head1 = creat_trunk();
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\蔬菜种类信息表.csv", "r");
    if (fp == NULL)
    {
        printf("fail to open the file1!!!\n");
        fclose(fp);
        return 0;
    }
    insert_veg(head1, fp);
    p1 = head1->right; //测试
    fclose(fp);

    //初始化表头指针数组
    p1 = head1->right;
    for (i = 0; i < 5; i++)
    {
        D_head1[i] = p1->down;
        p1 = p1->right;
    }

    //创造排序链
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\蔬菜基本信息表.csv", "r");
    if (fp == NULL)
    {
        printf("fail to open the file2!!!\n");
        fclose(fp);
        return 0;
    }
    sort_head = sorting_line(fp);
    //tp = sort_head->next;
    //printf("%d %s %d\n", tp->info.num1, tp->info.name, tp->info.num2);
    fclose(fp);

    //导入种植信息表，导入到排序主链中
    fp = fopen("C:\\Users\\40375\\Desktop\\课程设计\\任务一数据\\csv\\菜农种植信息表.csv", "r");
    if (fp == NULL)
    {
        printf("fail to open the file3!!!\n");
        fclose(fp);
        return 0;
    }
    gr_head = loading_grow_infolist(fp, sort_head);
    fclose(fp);

    //将排序链元素排入主链
    put_in(D_head1,sort_head);


    //下面是菜单
    int op=1;
    int l_op=1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("                   蔬菜种植系统菜单 \n");
        printf("--------------------------------------------------------\n");
        printf("            1. 蔬菜信息的导入，删除和修改\n");
        printf("    	    2. 蔬菜信息的查询\n");
        printf("    	    3. 蔬菜信息的统计\n");
        printf("            0. 退出系统\n");
        printf("--------------------------------------------------------\n");
        printf("    请选择你的操作[0~3]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            while (l_op)
            {
                system("cls");
                printf("\n\n");
                printf("              蔬菜信息的导入，删除和修改菜单 \n");
                printf("--------------------------------------------------------\n");
                printf("            1. 蔬菜种类信息和基本信息的导入\n");
                printf("            2. 蔬菜种类信息和基本信息的修改\n");
                printf("            3. 蔬菜种类和基本信息的删除 \n");
                printf("    	    4. 蔬菜种植信息的导入 \n");
                printf("            5. 蔬菜种植信息的修改 \n");
                printf("            6. 蔬菜种植信息的删除 \n");
                printf("            0. 返回上级菜单\n");
                printf("--------------------------------------------------------\n");
                printf("    请选择你的操作[0~6]:");
                getchar();
                scanf("%d", &l_op);
                switch (l_op)
                {
                case 1:
                    add_veg(D_head1, sort_head);
                    save_info1(D_head1, sort_head, gr_head);
                    system("pause");
                    break;
                case 2:
                    adjust_veg(D_head1, sort_head);
                    save_info1(D_head1, sort_head, gr_head);
                    system("pause");
                    break;
                case 3:
                    del_veg(D_head1, sort_head, gr_head);
                    save_info1(D_head1, sort_head, gr_head);
                    system("pause");
                    break;
                case 4:
                    add_grow_veg(D_head1, sort_head, gr_head);
                    save_info1(D_head1, sort_head, gr_head);
                    system("pause");
                    break;
                case 5:
                    adjust_grow_veg(D_head1, sort_head, gr_head);
                    save_info1(D_head1, sort_head, gr_head);
                    system("pause");
                    break;
                case 6:
                    del_grow_veg(D_head1, sort_head, gr_head);
                    save_info1(D_head1, sort_head, gr_head);
                    system("pause");
                    break;

                case 0:
                    break;
                }
            }
            l_op = 1;
            break;

        case 2:
            while (l_op)
            {
                system("cls");
                printf("\n\n");
                printf("              蔬菜信息的查询菜单 \n");
                printf("--------------------------------------------------------\n");
                printf("            1. 蔬菜名称按分类码查询\n");
                printf("            2. 蔬菜基本信息按名称关键词查询  \n");
                printf("            3. 蔬菜基本信息按分类和营养成分关键词查询 \n");
                printf("            4. 蔬菜种植信息按部分名称和年份查询 \n");
                printf("            5. 蔬菜种植信息按蔬菜名称查询 \n");
                printf("            6. 自由组合查询 \n");
                printf("            7. 蔬菜按营养成分查询 \n");
                printf("            0. 返回上级菜单\n");
                printf("--------------------------------------------------------\n");
                printf("    请选择你的操作[0~7]:");
                getchar();
                scanf("%d", &l_op);
                switch (l_op)
                {
                case 1:
                    kind_num_search(D_head1);
                    system("pause");
                    break;
                case 2:
                    keyword_basic_info_search(D_head1);
                    system("pause");
                    break;
                case 3:
                    kind_nutrition_search(D_head1);
                    system("pause");
                    break;
                case 4:
                    name_keyword_year_grow_search(D_head1);
                    system("pause");
                    break;
                case 5:
                    name_grow_search(D_head1);
                    system("pause");
                    break;
                case 6:
                    free_search(D_head1);
                    system("pause");
                    break;
                case 7:
                    nutrition_search(D_head1);
                    system("pause");
                    break;
                case 0:
                    break;
                }
            }
            l_op=1;
            break;

        case 3:
            while (l_op)
            {
                system("cls");
                printf("\n\n");
                printf("               蔬菜信息的统计菜单 \n");
                printf("--------------------------------------------------------\n");
                printf("            1. 按分类蔬菜种植信息的重量，面积统计（输出统计图）\n");
                printf("            2. 按起止年份统计蔬菜种植信息的重量，面积  \n");
                printf("            3. 统计各个种类蔬菜的总数量 \n");
                printf("            4. 按营养成分输出具有该营养成分的蔬菜 \n");
                printf("            5. 统计各个种类蔬菜收获总重量 \n");
                printf("            6. 按年份统计蔬菜种植信息 \n");
                printf("            7. 近三年内蔬菜种植信息统计 \n");
                printf("            0. 返回上级菜单\n");
                printf("--------------------------------------------------------\n");
                printf("    请选择你的操作[0~7]:");
                getchar();
                scanf("%d", &l_op);
                switch (l_op)
                {
                case 1:
                    count_kind_grow_info(D_head1);
                    system("pause");
                    break;
                case 2:
                    count_year_name(sort_head, gr_head);
                    system("pause");
                    break;
                case 3:
                    count_kind_veg(D_head1);
                    system("pause");
                    break;
                case 4:
                    nutrition_search(D_head1);
                    system("pause");
                    break;
                case 5:
                    count_kind_veg_weight(D_head1);
                    system("pause");
                    break;
                case 6:
                    output_grow_info(D_head1);
                    system("pause");
                    break;
                case 7:
                    latest_threeyear_grow_info(D_head1);
                    system("pause");
                    break;
                case 0:
                    break;
                }
            }
            l_op = 1;
            break;
        case 0:
            break;
        }
    }
    printf("    欢迎下次再使用本系统！\n");
    system("pause");
    return 0;
}
