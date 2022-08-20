#include "header.h"

//функция окончания программы
void ending(tree** trees)
{
	puts("Хотите продолжить?(Y/N)");
	for (;;)
	{
		rewind(stdin);                                   //очистка буффера
		char choice = getchar();                         //ввод 
		if (choice == 'N' or choice == 'n')
		{
			clear(trees);         //очистка дерева
			trees = nullptr;
			exit(0);              //выход из программы
		}
		else
			if (choice == 'Y' or choice == 'y') return; //выход из функции
			else puts("--->ОШИБКА<---");
	}
}

//экстренное завершение в случае ошибки
void error()
{
	puts("ERROR"); //сообщение об ошибке
	Sleep(3000);   //задержка на 3 секунды
	exit(-1);      //экстренное завершение
}

//функция ввода типа инт с дополнительной проверкой
int input(int test)
{
	int number;

	for (;;)
	{
		rewind(stdin);                                                       //очистка буффера
		int check = scanf_s("%d", &number);                                  //ввод числа
		if (check and number > 0 and number <= test) return number;          //возвращение аргумента
		else puts("--->ОШИБКА<---");
	}
}

//функция удаления элемента
void pop_back(stack** point)
{
	if (!*point)return;
	if (!((*point)->last))
	{
		free(*point);                                 //освобождение памяти
		*point = nullptr;                             //зануление указателя
	}
	else
	{
		stack* buff = (*point);                       //запоминаем вершину стека
		(*point) = (*point)->last;                    //сдвигаем вершину стека
		free(buff);                                   //освобождение памяти
	}
}

//функция добовления элемента
void push_front(stack** point, tree* trees)
{
	if (!*point)
	{
		(*point) = (stack*)malloc(sizeof(stack));     //выделение памяти
		if ((*point))
		{
			(*point)->last = nullptr;                 //зануления указателя на предыдущий элемент
			(*point)->node = trees;                   //занесение элемента
		}
		else error();

	}
	else
	{
		stack* buff = (stack*)malloc(sizeof(stack));  //выделение памяти
		if (buff)
		{
			buff->last = (*point);                    //указываем на предыдущий элемент
			(*point) = buff;                          //меняем вершину стека
			(*point)->node = trees;                   //занесение элемента

		}
		else error();
	}
}