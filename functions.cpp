#include "header.h"

//������������� ������� ���������� �������� ������
void push_front(tree** trees, int info)
{
	tree* buff = (tree*)malloc(sizeof(tree));              //��������� ������
	if (!buff)error();
	else
	{
		buff->info = info;                                 //��������� ����������
		buff->right = nullptr;                             //��������� ��������� �� ������ �������
		buff->left = nullptr;                              //��������� ��������� �� ����� �������
		buff->count = 1;                                   //���������� ������

		if (!*trees)
		{
			*trees = buff;
		}
		else
		{
			tree* check = *trees;          //��� ������� �� ������

			while (check)
			{
				if (check->info == info)
				{
					check->count++;        //��������� �������
					free(buff);            //������� ������ 
					break;
				}
				else
				{
					if (check->info > info)
					{
						if (check->left == nullptr)
						{
							check->left = buff;    //��������� � ������
							check = nullptr;       //����� �� �����
						}
						else
						{
							check = check->left;   //����������� �����
						}
					}
					else
					{
						if (check->right == nullptr)
						{
							check->right = buff;    //��������� � ������
							check = nullptr;        //����� �� �����
						}
						else
						{
							check = check->right;   //����������� ������
						}
					}
				}
			}
		}
	}
}

//������� ���a������ �������� ����������
tree* push_front_recurs(tree* trees, int info)
{
	if (!trees)
	{
		trees = (tree*)malloc(sizeof(tree));  //��������� ������
		if (!trees)error();
		else
		{
			//���� ������
			trees->info = info;
			trees->count = 1;
			trees->left = nullptr;
			trees->right = nullptr;
		}
	}
	else
		if (trees->info == info)trees->count++;
		else
			if (trees->info > info)trees->left = push_front_recurs(trees->left, info);
			else trees->right = push_front_recurs(trees->right, info);
	return trees;
}

//������� ���� ���a������
void add(tree** trees)
{
	puts("1 - ����������.\n2 - ������������.");
	int mode = input(2);         //����� ����������

	for (;;)
	{
		puts("������� ����������:");
		int info = input(100);   //���� ����������

		if (mode == 1)
		{
			(*trees) = push_front_recurs((*trees), info);   //������� ���a������ ������� ����������
		}
		else
		{
			push_front(trees, info);                        //����� �� ������������ ���a������
		}

		puts("������ ����������?(Y/N)");
		for (;;)
		{
			rewind(stdin);                                   //������� �������
			char choice = getchar();                         //���� 
			if (choice == 'N' or choice == 'n')return;       //����� �� ���������
			else if (choice == 'Y' or choice == 'y') break;  //����� �� �������
			else puts("--->������<---");
		}
	}
}

//����������� ������� ������ ������ 
void print_recurs(tree* trees, int mode)
{
	if (!trees)return;
	if (mode == 1)
	{
		for (int i = 0; i < trees->count; i++)
		{
			printf("%d ", trees->info);
		}
	}
	if (trees->left)print_recurs(trees->left, mode);     //������ �����
	if (mode == 2)
	{
		for (int i = 0; i < trees->count; i++)
		{
			printf("%d ", trees->info);
		}
	}
	if (trees->right)print_recurs(trees->right, mode);   //������ ������
	if (mode == 3)
	{
		for (int i = 0; i < trees->count; i++)
		{
			printf("%d ", trees->info);
		}
	}
}

//������� ����� ������ �� ����������
void print(tree* trees)
{
	int flag = 1;                                                     //���� �������� �����
	stack* pointer = nullptr;
	push_front(&pointer, trees);                                      //��������� ����� � ����

	if (trees->left or trees->right)for (int i = 0; i < trees->count; i++)printf("%d ", trees->info);//����� �����

	//���� ���� ���� ���-�� � ����� ��� ������ � ������
	while (pointer or trees->right)
	{
		do
		{
			if (flag and trees->left)trees = trees->left;             //���� ���� ����� � ������ ����
			else if (trees->right)trees = trees->right;               //���� ���� ������
			flag = 1;                                                 //������������ �������� �����
			if (trees->left and trees->right)
			{
				push_front(&pointer, trees);                          //��������� ����
			}
			for (int i = 0; i < trees->count; i++)printf("%d ", trees->info); //����� 
		} while (trees->left or trees->right);

		if (pointer)
		{
			trees = pointer->node;  //����������� �� ����
			pop_back(&pointer);     //�������� � ������� �����
		}

		if (trees->left and trees->right)flag = 0;  //�������� ������ � ����
		else break;                                 //������ ������ ������� ��� �������
	}
}

//����������������� ����� ����������� ��������� ������
void print(tree* trees, int floor)
{
	if (trees) print(trees->right, floor + 1);                  //������ ������
	for (int i = 0; i < floor; ++i) printf("     ");            //����� �������� �� ������
	if (trees) printf("%d (%d)\n", trees->info, trees->count);  //����� �������� ������
	else
	{	
		printf("    #\n");                                      //����� �������
	}
	if (trees) print(trees->left, floor + 1);                   //������ �����
}

//������� ���� ������ ������
void menu_show(tree* trees)
{
	puts("1 - ����������.\n2 - �� ����������.\n3 - ����������������� �����.");
	int mode = input(3);     //����� ������
	
	if (!trees)
	{
		puts("������ ������!");
	}
	else
		if (mode == 1)
		{
			puts("1 - ������.\n2 - ������������.\n3 - ��������.");
			int choice = input(3);          //�����
			printf("������:");
			print_recurs(trees, choice);    //����� ������ ����������
			printf("\n");
		}
		else 
			if (mode == 2)
			{
				printf("������:");
				print(trees);                   //����� ������ �� ����������
				printf("\n");
			}
			else
			{
				print(trees, 0);                //����������������� ����� ����������� ��������� ������
			}
}

//������� �������� ��������� ������
tree* del_any(tree* trees)
{
	puts("������� ��������� ����������:");
	int del = input(100);           //���� ��������� ����������

	int indicate = 0;               //������� ��� ����������� ������ ��������� �������
	int flag = 0;                   //���� ��� ������������ ,��� ���������� �������
	tree* buff1, * buff2, * buff3;  //�������������� ���������

	if (!trees)
	{
		puts("������ ������!");
		return trees;
	}
	else
	{
		buff1 = trees;     //��������� �� ������
		buff2 = trees;     //��������� �� ������

	   //���� ������ ��������� ������� � ����������
		do
		{
			if (buff1->info == del)
			{
				indicate = 1; //����� �� �����
				flag = 1;     //������� ������
			}

			if (buff1->info > del)
			{
				if (buff1->left)
				{
					buff2 = buff1;        //��������� ���������� �������
					buff1 = buff1->left;  //�������� �����
				}
				else indicate = 1;        //����� �� �����
			}
			else
				if (buff1->info < del)
				{
					if (buff1->right)
					{
						buff2 = buff1;         //��������� ���������� �������
						buff1 = buff1->right;  //�������� ������
					}
					else indicate = 1;         //����� �� �����
				}
		} while (!indicate);

		if (!flag)
		{
			puts("������� �� ������!");
			return trees;
		}
		else
		{
			buff3 = buff1;                  //���������� ��������� �������

			if (buff2 == buff1)             //���� ������� ������
			{
				if (buff1->right)
				{
					buff3 = buff3->right;                    //������ ������
					while (buff3->left)buff3 = buff3->left;  //����� �� nullptr
					buff3->left = trees->left;               //������� �����
		            trees = trees->right;                    //������� ��������� �������
					free(buff1);                             //������� ������
					return trees;                            //����������� ������ �����
				}
				else
				{
					trees = trees->left;    //�������� �����
					free(buff1);            //������� ������
					return trees;           //����������� ������ �����
				}
			}
			else
				if (buff2->info > buff1->info)
				{
					if (buff1->right)
					{
						buff3 = buff3->right;                    //������ ������
						while (buff3->left)buff3 = buff3->left;  //����� �� nullptr
						buff2->left = buff1->right;              //������� ��������� �������
						buff3->left = buff1->left;               //������� �����
					}
					else buff2->left = buff1->left;
				}
				else
				{
					if (buff1->left)
					{
						buff3 = buff3->left;                     //������ �����
						while (buff3->right)buff3 = buff3->right;//������ �� nullptr
						buff2->right = buff1->left;              //������� ��������� �������
						buff3->right = buff1->right;             //������� �����
					}
					else buff2->right = buff1->right;
				}
		}
		return trees;
		free(buff1);
	}
}

//������� ������
void clear(tree** trees)
{
	if (!*trees)return;
	if ((*trees)->left)clear(&((*trees)->left));
	if ((*trees)->right)clear(&((*trees)->right));
	free(*trees);
	*trees = nullptr;
}


