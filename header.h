#pragma once

#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iso646.h>

//��������� ������
struct tree
{
	int info;                  //����������
	int count;                 //����� ������
	tree* left;                //��������� �� ����� �����
	tree* right;               //��������� �� ����� ������
};

struct stack                   //���� ����� ������ ����� ������� �������������� �������� �� ����� 
{
	tree* node;                //���� ������  
	stack* last;               //��������� �� ���������� �������  
};

void ending(tree**);           //������� ��������� ���������
void error();                  //���������� ���������� � ������ ������
int input(int);                //������� ����� ���� ��� � �������������� ���������

void push_front(stack**, tree*);     //������� ���������� �������� � ����
void pop_back(stack**);              //������� �������� �������� �� �����

void add(tree**);                    //������� ���� ���������� 
void push_front(tree**, int);        //������� ���������� �������� �� ����������
tree* push_front_recurs(tree*, int); //������� ���a������ �������� ���������� 

void menu_show(tree*);               //������� ���� ������ ������
void print(tree*, int);              //����������������� ����� ����������� ��������� ������
void print_recurs(tree*, int);       //������� ������ ������ ����������
void print(tree*);                   //������� ����� ������ �� ����������

tree* del_any(tree*);                //������� �������� ��������� ������
void clear(tree**);                  //������� ������