#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include "baseDefine.h"

#define _NO_CRT_STDIO_INLINE


/*
	@start
	@name pressEnterForContinue
	@prototype void pressEnterForContinue()
	@example pressEnterForContinue
	@description Описание функции
	@return Возврат функции
	@end
*/
void pressEnterForContinue()
{
	rewind(stdin);
	printf(" Нажмите ENTER для продолжения работы программы. \n\n");
	while (_getch() != '\r');
}


/*
	@start
	@name getTitle
	@prototype void getTitle(char *title)
	@example getTitle
	@description Описание функции
	@param  char *	title	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void getTitle(char *title)
{
	system("cls");
	printf("\n ===== %s \n\n", title);
}


/*
	@start
	@name getMenu
	@prototype void getMenu()
	@example getMenu
	@description Описание функции
	@return Возврат функции
	@end
*/
void getMenu()
{
	getTitle("Меню");
	printf(" 1 - Ввод данных \n");
	printf(" 2 - Контрольный вывод исходных данных \n");
	printf(" 3 - Ввод параметров для фильтрации данных \n");
	printf(" 4 - Контрольный вывод параметров для фильтрации \n");
	printf(" 5 - Обработка данных \n");
	printf(" 6 - Вывод результата \n");
	printf(" 7 - Справка\n");
	printf(" 0 - Выход из программы\n");
}


/*
	@start
	@name getReference
	@prototype void getReference()
	@example getReference
	@description Описание функции
	@return Возврат функции
	@end
*/
void getReference()
{
	getTitle("Справка");
	printf(" Программа является каталогом фильмов с возможностью фильтрации данных по двум критериям.\n");
	printf(" Исходными данными является каталог фильмов. \n");
	printf(" Каталог фильмов содержит следующие поля: название фильма, жанр, год, продолжительность и рейтинг. \n");
	printf(" Для фильтрации каталога фильмов нужно ввести год и продолжительность фильма. \n\n");
	printf(" Информация по каждому полю появляется в виде подсказки при взаимодействии с данной программой.");
	pressEnterForContinue();
}


/*
	@start
	@name getError
	@prototype void getError(int error_code)
	@example getError
	@description Описание функции
	@param  int	error_code	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void getError(int error_code)
{
	if (error_code)
		printf("\n -------- Ошибка! \n\t  ");

	switch (error_code)
	{
		case 1:
			printf("Максимальная длина строки - %d символов. Ввод завершен, введеные символы сохранены.", MAX_TITLE_FILM);
			break;
		case 2:
			printf("Должен быть написан минимум один символ.");
			break;
		case 3:
			printf("Выполнение данного пункта невозможно. Данные ещё не добавлены.");
			break;
		case 4:
			printf("Следующий параметр для фильтрации не введен: продолжительность.");
			break;
		case 5:
			printf("Следующий параметр для фильтрации не введен: год.");
			break;
		case 6:
			printf("Результаты отсутствуют. Нет данных, совпадающих с данными критериями.");
			break;
		case 7:
			printf("Данный пункт меню не распознан. Возможно, вы ввели неправильно.");
			break;
		case 8:
			printf("Год должен быть в промежутке от %d по %d год.", YEAR_MIN_DATE, YEAR_MAX_DATE);
			break;
		case 9:
			printf("Продолжительность фильма должна быть в промежутке от %d до %d минут.", TIME_MIN_MINUT, TIME_MAX_MINUT);
			break;
		case 10:
			printf("Введен неверный тип данных. Нужно ввести целое число.");
			break;
		case 11:
			printf("Введен несуществующий номер жанра. Повторите ввод.");
			break;
		case 12:
			printf("Рейтинг фильма должен быть в промежутке от %d до %d.", RATING_MIN, RATING_MAX);
			break;
		case 13:
			printf("Введен неверный тип данных. Нужно ввести вещественное число.");
			break;
		case 14:
			printf("Выполнение данного пункта невозможно. Не была произведена обработка.");
			break;
		default:
			printf("Обратитесь к разработчику.");
			break;
	}

	printf("\n\n");
	pressEnterForContinue();
}


/*
	@start
	@name getchr
	@prototype char getchr()
	@example getchr
	@description Описание функции
	@return Возврат функции
	@end
*/
char getchr()
{
	char c;
	c = _getch();

	if (c == '\r')
		c = '\n';

	if (c != '\b' && c != NULL)
		printf_s("%c", c);

	return c;
}

