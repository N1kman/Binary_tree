#include "header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	tree* trees = nullptr;                          //��������� �� ������

	for (;;)
	{
		puts("1 - �������� ������� � ������.\n2 - ������� ������.\n3 - �������� �������� ������.\n4 - �����.");
		int choice = input(4);

		switch (choice)
		{
		case 1:
			add(&trees);                               //������� ����������
			break;

		case 2:
			menu_show(trees);                          //������� ���� ������ ������
			break;

		case 3:
			trees = del_any(trees);		               //������� �������� ��������� ������
			break;

		case 4:
			ending(&trees);                            //���������� ������
			break;
		}
	}
}