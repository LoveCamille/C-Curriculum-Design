#define SHOW_CONSOLE
#include "veg.h"


int main()
{
    int i;
    kind *head1, *p1; //head1Ϊ��������ͷָ��,p1���ڲ�������
    veg1 *D_head1[5]; //D_head1Ϊ������������ͷָ��
    veg1 *sort_head;  //���������ͷָ��
    //veg1 *tp        //tpΪ����ָ��
    veg2 *gr_head; //�߲���ֲ��Ϣ��������ͷ
    FILE *fp;

    //��������
    head1 = creat_trunk();
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\�߲�������Ϣ��.csv", "r");
    if (fp == NULL)
    {
        printf("fail to open the file1!!!\n");
        fclose(fp);
        return 0;
    }
    insert_veg(head1, fp);
    p1 = head1->right; //����
    fclose(fp);

    //��ʼ����ͷָ������
    p1 = head1->right;
    for (i = 0; i < 5; i++)
    {
        D_head1[i] = p1->down;
        p1 = p1->right;
    }

    //����������
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\�߲˻�����Ϣ��.csv", "r");
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

    //������ֲ��Ϣ�����뵽����������
    fp = fopen("C:\\Users\\40375\\Desktop\\�γ����\\����һ����\\csv\\��ũ��ֲ��Ϣ��.csv", "r");
    if (fp == NULL)
    {
        printf("fail to open the file3!!!\n");
        fclose(fp);
        return 0;
    }
    gr_head = loading_grow_infolist(fp, sort_head);
    fclose(fp);

    //��������Ԫ����������
    put_in(D_head1,sort_head);


    //�����ǲ˵�
    int op=1;
    int l_op=1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("                   �߲���ֲϵͳ�˵� \n");
        printf("--------------------------------------------------------\n");
        printf("            1. �߲���Ϣ�ĵ��룬ɾ�����޸�\n");
        printf("    	    2. �߲���Ϣ�Ĳ�ѯ\n");
        printf("    	    3. �߲���Ϣ��ͳ��\n");
        printf("            0. �˳�ϵͳ\n");
        printf("--------------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~3]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            while (l_op)
            {
                system("cls");
                printf("\n\n");
                printf("              �߲���Ϣ�ĵ��룬ɾ�����޸Ĳ˵� \n");
                printf("--------------------------------------------------------\n");
                printf("            1. �߲�������Ϣ�ͻ�����Ϣ�ĵ���\n");
                printf("            2. �߲�������Ϣ�ͻ�����Ϣ���޸�\n");
                printf("            3. �߲�����ͻ�����Ϣ��ɾ�� \n");
                printf("    	    4. �߲���ֲ��Ϣ�ĵ��� \n");
                printf("            5. �߲���ֲ��Ϣ���޸� \n");
                printf("            6. �߲���ֲ��Ϣ��ɾ�� \n");
                printf("            0. �����ϼ��˵�\n");
                printf("--------------------------------------------------------\n");
                printf("    ��ѡ����Ĳ���[0~6]:");
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
                printf("              �߲���Ϣ�Ĳ�ѯ�˵� \n");
                printf("--------------------------------------------------------\n");
                printf("            1. �߲����ư��������ѯ\n");
                printf("            2. �߲˻�����Ϣ�����ƹؼ��ʲ�ѯ  \n");
                printf("            3. �߲˻�����Ϣ�������Ӫ���ɷֹؼ��ʲ�ѯ \n");
                printf("            4. �߲���ֲ��Ϣ���������ƺ���ݲ�ѯ \n");
                printf("            5. �߲���ֲ��Ϣ���߲����Ʋ�ѯ \n");
                printf("            6. ������ϲ�ѯ \n");
                printf("            7. �߲˰�Ӫ���ɷֲ�ѯ \n");
                printf("            0. �����ϼ��˵�\n");
                printf("--------------------------------------------------------\n");
                printf("    ��ѡ����Ĳ���[0~7]:");
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
                printf("               �߲���Ϣ��ͳ�Ʋ˵� \n");
                printf("--------------------------------------------------------\n");
                printf("            1. �������߲���ֲ��Ϣ�����������ͳ�ƣ����ͳ��ͼ��\n");
                printf("            2. ����ֹ���ͳ���߲���ֲ��Ϣ�����������  \n");
                printf("            3. ͳ�Ƹ��������߲˵������� \n");
                printf("            4. ��Ӫ���ɷ�������и�Ӫ���ɷֵ��߲� \n");
                printf("            5. ͳ�Ƹ��������߲��ջ������� \n");
                printf("            6. �����ͳ���߲���ֲ��Ϣ \n");
                printf("            7. ���������߲���ֲ��Ϣͳ�� \n");
                printf("            0. �����ϼ��˵�\n");
                printf("--------------------------------------------------------\n");
                printf("    ��ѡ����Ĳ���[0~7]:");
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
    printf("    ��ӭ�´���ʹ�ñ�ϵͳ��\n");
    system("pause");
    return 0;
}
