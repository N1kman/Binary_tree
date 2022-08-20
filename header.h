#pragma once

#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iso646.h>

//структура дерева
struct tree
{
	int info;                  //информация
	int count;                 //число встреч
	tree* left;                //указатель на ветвь слева
	tree* right;               //указатель на ветвь справа
};

struct stack                   //стек узлов дерева через которые осуществляется движение по ветви 
{
	tree* node;                //узел дерева  
	stack* last;               //указатель на придыдущий элемент  
};

void ending(tree**);           //функция окончания программы
void error();                  //экстренное завершение в случае ошибки
int input(int);                //функция ввода типа инт с дополнительной проверкой

void push_front(stack**, tree*);     //функция добавления элемента в стек
void pop_back(stack**);              //функция удаления элемента из стека

void add(tree**);                    //функция меню добавления 
void push_front(tree**, int);        //функция добавления элемента не рекурсивно
tree* push_front_recurs(tree*, int); //функция добaвления элемента рекурсивно 

void menu_show(tree*);               //функция меню выбора вывода
void print(tree*, int);              //псевдографический вывод содержимого бинарного дерева
void print_recurs(tree*, int);       //функция вывода дерева рекурсивно
void print(tree*);                   //функция вывод дерева не рекурсивно

tree* del_any(tree*);                //функция удаления фрагмента дерева
void clear(tree**);                  //очистка дерева