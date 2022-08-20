#include "header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	tree* trees = nullptr;                          //указатель на дерево

	for (;;)
	{
		puts("1 - добавить элемент в дерево.\n2 - вывести дерево.\n3 - удаление элемента дерева.\n4 - выход.");
		int choice = input(4);

		switch (choice)
		{
		case 1:
			add(&trees);                               //функция добовления
			break;

		case 2:
			menu_show(trees);                          //функция меню выбора вывода
			break;

		case 3:
			trees = del_any(trees);		               //функция удаления фрагмента дерева
			break;

		case 4:
			ending(&trees);                            //завершение работы
			break;
		}
	}
}