#include "header.h"

//нерекурсивная функция добавления элемента дерева
void push_front(tree** trees, int info)
{
	tree* buff = (tree*)malloc(sizeof(tree));              //выделение памяти
	if (!buff)error();
	else
	{
		buff->info = info;                                 //занесение информации
		buff->right = nullptr;                             //зануления указателя на правый элемент
		buff->left = nullptr;                              //зануления указателя на левый элемент
		buff->count = 1;                                   //количество встреч

		if (!*trees)
		{
			*trees = buff;
		}
		else
		{
			tree* check = *trees;          //для прохода по дереву

			while (check)
			{
				if (check->info == info)
				{
					check->count++;        //случилась встреча
					free(buff);            //очистка памяти 
					break;
				}
				else
				{
					if (check->info > info)
					{
						if (check->left == nullptr)
						{
							check->left = buff;    //занесение в дерево
							check = nullptr;       //выход из цикла
						}
						else
						{
							check = check->left;   //продвижение влево
						}
					}
					else
					{
						if (check->right == nullptr)
						{
							check->right = buff;    //занесение в дерево
							check = nullptr;        //выход из цикла
						}
						else
						{
							check = check->right;   //продвижение вправо
						}
					}
				}
			}
		}
	}
}

//функция добaвления элемента рекурсивно
tree* push_front_recurs(tree* trees, int info)
{
	if (!trees)
	{
		trees = (tree*)malloc(sizeof(tree));  //выделение памяти
		if (!trees)error();
		else
		{
			//ввод данных
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

//функция меню добaвления
void add(tree** trees)
{
	puts("1 - Рекурсивно.\n2 - Нерекурсивно.");
	int mode = input(2);         //выбор добавления

	for (;;)
	{
		puts("Введите информацию:");
		int info = input(100);   //ввод информации

		if (mode == 1)
		{
			(*trees) = push_front_recurs((*trees), info);   //функция добaвления вершины рекурсивно
		}
		else
		{
			push_front(trees, info);                        //вызов не рекурсивного добaвления
		}

		puts("Хотите продолжить?(Y/N)");
		for (;;)
		{
			rewind(stdin);                                   //очистка буффера
			char choice = getchar();                         //ввод 
			if (choice == 'N' or choice == 'n')return;       //выход из программы
			else if (choice == 'Y' or choice == 'y') break;  //выход из функции
			else puts("--->ОШИБКА<---");
		}
	}
}

//рекурсивная функция вывода дерева 
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
	if (trees->left)print_recurs(trees->left, mode);     //проход влево
	if (mode == 2)
	{
		for (int i = 0; i < trees->count; i++)
		{
			printf("%d ", trees->info);
		}
	}
	if (trees->right)print_recurs(trees->right, mode);   //проход вправо
	if (mode == 3)
	{
		for (int i = 0; i < trees->count; i++)
		{
			printf("%d ", trees->info);
		}
	}
}

//функция вывод дерева не рекурсивно
void print(tree* trees)
{
	int flag = 1;                                                     //флаг движения влево
	stack* pointer = nullptr;
	push_front(&pointer, trees);                                      //занесение корня в стек

	if (trees->left or trees->right)for (int i = 0; i < trees->count; i++)printf("%d ", trees->info);//вывод корня

	//фикл пока есть что-то в стеке или справа в дереве
	while (pointer or trees->right)
	{
		do
		{
			if (flag and trees->left)trees = trees->left;             //если есть слева и поднят флаг
			else if (trees->right)trees = trees->right;               //если есть справа
			flag = 1;                                                 //установление движения влево
			if (trees->left and trees->right)
			{
				push_front(&pointer, trees);                          //зенесение узла
			}
			for (int i = 0; i < trees->count; i++)printf("%d ", trees->info); //вывод 
		} while (trees->left or trees->right);

		if (pointer)
		{
			trees = pointer->node;  //возвращение на узел
			pop_back(&pointer);     //удаление с вершины стека
		}

		if (trees->left and trees->right)flag = 0;  //движение вправо в узле
		else break;                                 //значит данный элемент был выведен
	}
}

//псевдографический вывод содержимого бинарного дерева
void print(tree* trees, int floor)
{
	if (trees) print(trees->right, floor + 1);                  //проход вправо
	for (int i = 0; i < floor; ++i) printf("     ");            //вывод пробелов по уровню
	if (trees) printf("%d (%d)\n", trees->info, trees->count);  //вывод элемента дерева
	else
	{	
		printf("    #\n");                                      //вывод пустоты
	}
	if (trees) print(trees->left, floor + 1);                   //проход влево
}

//функция меню выбора вывода
void menu_show(tree* trees)
{
	puts("1 - рекурсивно.\n2 - не рекурсивно.\n3 - псевдографический вывод.");
	int mode = input(3);     //выбор вывода
	
	if (!trees)
	{
		puts("Дерево пустое!");
	}
	else
		if (mode == 1)
		{
			puts("1 - прямой.\n2 - симметричный.\n3 - обратный.");
			int choice = input(3);          //выбор
			printf("Дерево:");
			print_recurs(trees, choice);    //вывод дерева рекурсивно
			printf("\n");
		}
		else 
			if (mode == 2)
			{
				printf("Дерево:");
				print(trees);                   //вывод дерева не рекурсивно
				printf("\n");
			}
			else
			{
				print(trees, 0);                //псевдографический вывод содержимого бинарного дерева
			}
}

//функция удаления фрагмента дерева
tree* del_any(tree* trees)
{
	puts("Введите удаляемую информацию:");
	int del = input(100);           //ввод удаляемой информации

	int indicate = 0;               //условие для продолжения поиска удаляемой вершины
	int flag = 0;                   //флаг для фиксирования ,что информация найдена
	tree* buff1, * buff2, * buff3;  //дополнительные указатели

	if (!trees)
	{
		puts("Дерево пустое!");
		return trees;
	}
	else
	{
		buff1 = trees;     //указываем на корень
		buff2 = trees;     //указываем на корень

	   //цикл поиска удаляемой вершины и придыдущей
		do
		{
			if (buff1->info == del)
			{
				indicate = 1; //выход из цикла
				flag = 1;     //элемент найден
			}

			if (buff1->info > del)
			{
				if (buff1->left)
				{
					buff2 = buff1;        //фиксируем придыдущую вершину
					buff1 = buff1->left;  //проходим влево
				}
				else indicate = 1;        //выход из цикла
			}
			else
				if (buff1->info < del)
				{
					if (buff1->right)
					{
						buff2 = buff1;         //фиксируем придыдущую вершину
						buff1 = buff1->right;  //проходим вправо
					}
					else indicate = 1;         //выход из цикла
				}
		} while (!indicate);

		if (!flag)
		{
			puts("Элемент не найден!");
			return trees;
		}
		else
		{
			buff3 = buff1;                  //запоминаем удаляемую вершину

			if (buff2 == buff1)             //если удаляем корень
			{
				if (buff1->right)
				{
					buff3 = buff3->right;                    //уходим вправо
					while (buff3->left)buff3 = buff3->left;  //влево до nullptr
					buff3->left = trees->left;               //перенос ветви
		            trees = trees->right;                    //обходим удаляемую вершину
					free(buff1);                             //очистка памяти
					return trees;                            //возвращение нового корня
				}
				else
				{
					trees = trees->left;    //проходим влево
					free(buff1);            //очистка памяти
					return trees;           //возвращение нового корня
				}
			}
			else
				if (buff2->info > buff1->info)
				{
					if (buff1->right)
					{
						buff3 = buff3->right;                    //уходим вправо
						while (buff3->left)buff3 = buff3->left;  //влево до nullptr
						buff2->left = buff1->right;              //обходим удаляемую вершину
						buff3->left = buff1->left;               //перенос ветви
					}
					else buff2->left = buff1->left;
				}
				else
				{
					if (buff1->left)
					{
						buff3 = buff3->left;                     //уходим влево
						while (buff3->right)buff3 = buff3->right;//вправо до nullptr
						buff2->right = buff1->left;              //обходим удаляемую вершину
						buff3->right = buff1->right;             //перенос ветви
					}
					else buff2->right = buff1->right;
				}
		}
		return trees;
		free(buff1);
	}
}

//очистка дерева
void clear(tree** trees)
{
	if (!*trees)return;
	if ((*trees)->left)clear(&((*trees)->left));
	if ((*trees)->right)clear(&((*trees)->right));
	free(*trees);
	*trees = nullptr;
}


