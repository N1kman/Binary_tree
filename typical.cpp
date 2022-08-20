#include "header.h"

//������� ��������� ���������
void ending(tree** trees)
{
	puts("������ ����������?(Y/N)");
	for (;;)
	{
		rewind(stdin);                                   //������� �������
		char choice = getchar();                         //���� 
		if (choice == 'N' or choice == 'n')
		{
			clear(trees);         //������� ������
			trees = nullptr;
			exit(0);              //����� �� ���������
		}
		else
			if (choice == 'Y' or choice == 'y') return; //����� �� �������
			else puts("--->������<---");
	}
}

//���������� ���������� � ������ ������
void error()
{
	puts("ERROR"); //��������� �� ������
	Sleep(3000);   //�������� �� 3 �������
	exit(-1);      //���������� ����������
}

//������� ����� ���� ��� � �������������� ���������
int input(int test)
{
	int number;

	for (;;)
	{
		rewind(stdin);                                                       //������� �������
		int check = scanf_s("%d", &number);                                  //���� �����
		if (check and number > 0 and number <= test) return number;          //����������� ���������
		else puts("--->������<---");
	}
}

//������� �������� ��������
void pop_back(stack** point)
{
	if (!*point)return;
	if (!((*point)->last))
	{
		free(*point);                                 //������������ ������
		*point = nullptr;                             //��������� ���������
	}
	else
	{
		stack* buff = (*point);                       //���������� ������� �����
		(*point) = (*point)->last;                    //�������� ������� �����
		free(buff);                                   //������������ ������
	}
}

//������� ���������� ��������
void push_front(stack** point, tree* trees)
{
	if (!*point)
	{
		(*point) = (stack*)malloc(sizeof(stack));     //��������� ������
		if ((*point))
		{
			(*point)->last = nullptr;                 //��������� ��������� �� ���������� �������
			(*point)->node = trees;                   //��������� ��������
		}
		else error();

	}
	else
	{
		stack* buff = (stack*)malloc(sizeof(stack));  //��������� ������
		if (buff)
		{
			buff->last = (*point);                    //��������� �� ���������� �������
			(*point) = buff;                          //������ ������� �����
			(*point)->node = trees;                   //��������� ��������

		}
		else error();
	}
}