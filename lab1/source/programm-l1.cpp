#include "stdafx.h"
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "films.h"
#include "base.h"

int main()
{
	int select_menu;						// Флажок выбора меню
	struct FILMS* films_source = NULL;		// исходная структура
	struct FILMS* films_result = NULL;		// результирующая структура
	int films_source_size = NULL;			// размер исходной структуры
	int films_result_size = NULL;			// размер обработанной структуры
	int repeat = 0;							// повторять ли
	int filterParamYear = NULL;				// значение года для фильтрации
	int filterParamTime = NULL;				// значение продолжительности для фильтрации
	int film_processed = 0;					// обработано ли

	SetConsoleCP(1251);						// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);				// установка кодовой страницы win-cp 1251 в поток вывода
	system("title = Лабораторная №1");
	system("mode con cols=150 lines=30");
	
	do
	{
		system("cls");
		getMenu();
		printf("\n Введите номер пункта меню: ");
		scanf_s("%d", &select_menu);
		printf("\n");

		switch (select_menu)
		{
			case 0:
				getTitle("Выход");
				printf(" Вы выбрали выход. Всего хорошего");
				break;
			case 1:
				films_source = freeMemory(films_source, films_source_size);
				films_result = freeMemory(films_result, films_result_size);
				film_processed = 0;
				films_source = wrapSetSource(films_source, &films_source_size);
				break;
			case 2:
				wrapGetFilmsSource(films_source, films_source_size);
				break;
			case 3:
				films_result = freeMemory(films_result, films_result_size);
				film_processed = 0;
				setFilterParams(&filterParamYear, &filterParamTime);
				break;
			case 4:
				wrapGetfilterParams(filterParamYear, filterParamTime);
				break;
			case 5:
				films_result = freeMemory(films_result, films_result_size);
				films_result = process(films_source, films_source_size, filterParamYear, filterParamTime, &films_result_size, &film_processed);
				break;
			case 6:
				wrapGetFilmsResults(films_result, films_result_size, film_processed);
				break;
			case 7:
				getReference();
				break;
			default:
				getError(7);
				break;
		}

		printf("\n ");
	}
	while (select_menu);

	films_source = freeMemory(films_source, films_source_size);
	films_result = freeMemory(films_result, films_result_size);

	return 0;
}
