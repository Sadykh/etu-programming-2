#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <windows.h>
#include "base.h"
#include "films.h"
#include "baseDefine.h"

struct FILMS
{
	char *title;	// название
	int genre;		// жанр
	int time;		// продолжительность
	int year;		// год выпуска
	float rating;	// рейтинг
};

/*
	@start
	@name setStr
	@prototype char *setStr()
	@example setStr
	@description Описание функции
	@return Возврат функции
	@end
*/
char *setStr()
{
	char *str = (char*) malloc(sizeof(char));	// указатель на первый элемент новой строки
	int length = 0;								// счётчик количества символов

	system("cls");
	getTitle("Ввод названия фильма");
	printf(" Подсказка: в названии фильма можно использовать любые символы. Минимальное количество символов - 1. Максимальное количество символов %d. \n", MAX_TITLE_FILM);
	printf(" Название фильма: ");

	// проверяем, что количество символов не превышало и не было перевода на новую строку
	while (length < MAX_TITLE_FILM && ((*(str + length) = getchr()) != '\n'))
	{

		// если backspace, то уменьшаем счётчик символов и выводим в консоль введеный backspace
		if ((*(str + length) == '\b'))
		{
			if (length && length--)
				printf("\b \b");	// стереть только что введеный символ
		}
		else
		{
			if (length++ && length == MAX_TITLE_FILM)
				getError(1);
		}
		// увеличиваем память под символ для ввода и символ окончания строки \0
		str = (char*) realloc(str, (length + 1) * sizeof(char));
	}
	// Метка: конец строки символов
	*(str + length) = '\0';

	if (!length)
	{
		getError(2);
		str = setStr();
	}

	printf(" Ввод названия завершен. \n\n");
	pressEnterForContinue();
	return str;
}


/*
	@start
	@name set
	@prototype struct FILMS *set(int *size)
	@example set
	@description Описание функции
	@param  int *	size	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
struct FILMS *set(int *size)
{
	int repeat = 0;					// повторять ли
	struct FILMS *items = NULL;		// массив структура
	*size = 0;						// размер массива структуры

	do
	{
		items = (struct FILMS*) realloc(items, (*size + 1) * sizeof(struct FILMS));
		(items + *size)->title = setStr();

		(items + *size)->genre = setGenre();
		(items + *size)->year = setYear();
		(items + *size)->time = setTime();
		(items + *size)->rating = setRating();

		rewind(stdin);
		printf("\n Добавить ещё один фильм? (1 - да, 0 - нет): ");
		scanf_s("%d", &repeat);
		printf("\n\n");

		(*size)++;
	}
	while (repeat);
	return items;
}


/*
	@start
	@name getHeadTables
	@prototype void getHeadTables()
	@example getHeadTables
	@description Описание функции
	@return Возврат функции
	@end
*/
void getHeadTables()
{
	printf(" %-3s", "№");
	printf("%-62s", "Название фильма");
	printf("%-27s", "Жанр");
	printf("%-12s", "Год");
	printf("%-32s", "Продолжительность");
	printf("%-12s", "Рейтинг");
	printf("\n \n");
}


/*
	@start
	@name getFilms
	@prototype void getFilms(struct FILMS *items, int size)
	@example getFilms
	@description Описание функции
	@param  struct FILMS *	items	=>  Описание аргумента 
	@param  int	size	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void getFilms(struct FILMS *items, int size)
{
	int offset;
	offset = setOffset();
	getFilmsPage(items, size, offset);
}


/*
	@start
	@name getFilmsPage
	@prototype void getFilmsPage(struct FILMS *items, int size, int offset)
	@example getFilmsPage
	@description Описание функции
	@param  struct FILMS *	items	=>  Описание аргумента 
	@param  int	size	=>  Описание аргумента 
	@param  int	offset	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void getFilmsPage(struct FILMS *items, int size, int offset)
{
	int maxPages = ceil((float) size / offset);		// максимальное количество страниц
	int page;										// текущая страница
	int currentItem;								// текущий номер фильма
	int maxCurrentItems;							// максимальное количество фильмов на текущей странице


	for (page = 0; page < maxPages; page++)
	{
		currentItem = page * offset;
		maxCurrentItems = currentItem + offset;

		if (size < maxCurrentItems)
			maxCurrentItems = size;

		system("cls");
		getTitle("Вывод фильмов");

		getPageInfo(maxPages, page, currentItem, maxCurrentItems);
		getHeadTables();

		for (currentItem; currentItem < maxCurrentItems; currentItem++)
		{
			getFields(currentItem, items + currentItem);
			printf("\n\n");
		};
		printf("\n\n");

		if (page != maxPages)
			pressEnterForContinue();
	}

	printf("\n\n Вывод списка фильмов завершен.");
}


/*
	@start
	@name getPageInfo
	@prototype void getPageInfo(int maxPages, int page, int currentItem, int maxCurrentItems)
	@example getPageInfo
	@description Описание функции
	@param  int	maxPages	=>  Описание аргумента 
	@param  int	page	=>  Описание аргумента 
	@param  int	currentItem	=>  Описание аргумента 
	@param  int	maxCurrentItems	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void getPageInfo(int maxPages, int page, int currentItem, int maxCurrentItems)
{
	printf(" Вы на %d странице из %d страниц.", page + 1, maxPages);
	printf(" На данной странице отображены фильмы с %d по %d по порядку", currentItem + 1, maxCurrentItems);
	printf("\n\n\n");
}


/*
	@start
	@name setOffset
	@prototype int setOffset()
	@example setOffset
	@description Описание функции
	@return Возврат функции
	@end
*/
int setOffset()
{
	int repeat;
	int number;

	do
	{
		getTitle("Ввод количества фильмов для вывода");

		repeat = 0;
		printf(" Подсказка: количество должно являться целым числом и быть в промежутке от %d по %d. \n", OFFSET_MIN, OFFSET_MAX);
		printf(" Введите количество: ");

		if (scanf_s("%d", &number) != 1)
		{
			rewind(stdin);
			getError(10);
			repeat = 1;
		}
		else if (number < OFFSET_MIN || number > OFFSET_MAX)
		{
			getError(8);
		}
	}
	while (repeat || number < OFFSET_MIN || number > OFFSET_MAX);

	printf(" Ввод количество фильмов для показа завершен. \n\n");
	pressEnterForContinue();
	return number;
}


/*
	@start
	@name getFields
	@prototype void getFields(int i, struct FILMS *data)
	@example getFields
	@description Описание функции
	@param  int	i	=>  Описание аргумента 
	@param  struct FILMS *	data	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void getFields(int i, struct FILMS *data)
{
	char **genres = getGenresArrayList();

	printf(" %-3d", i + 1);
	printf(" %-60s ", data->title);
	printf(" %-25s ", *(genres + data->genre));
	printf(" %-10d ", data->year);
	printf(" %-30d ", data->time);
	printf(" %-10.1f ", data->rating);
}


/*
	@start
	@name setFilterParams
	@prototype void setFilterParams(int *year, int *time)
	@example setFilterParams
	@description Описание функции
	@param  int *	year	=>  Описание аргумента 
	@param  int *	time	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void setFilterParams(int *year, int *time)
{
	getTitle("Ввод параметров для фильтрации данных");
	printf(" Фильтровать можно по двум полям: по году и продолжительности.");
	printf(" В результате будут фильмы, удовлетворяющие данным условиям. \n\n");

	printf(" Завершение ввода поля — нажать на Enter \n\n\n");
	pressEnterForContinue();

	*year = setYear();
	*time = setTime();
}


/*
	@start
	@name setYear
	@prototype int setYear()
	@example setYear
	@description Описание функции
	@return Возврат функции
	@end
*/
int setYear()
{
	int year;
	int repeat;

	do
	{
		getTitle("Ввод года");

		repeat = 0;
		printf(" Подсказка: год должен являться целым числом и быть в промежутке от %d по %d год. \n", YEAR_MIN_DATE, YEAR_MAX_DATE);
		printf(" Введите год: ");

		if (scanf_s("%d", &year) != 1)
		{
			rewind(stdin);
			getError(10);
			repeat = 1;
		}
		else if (year < YEAR_MIN_DATE || year > YEAR_MAX_DATE)
		{
			getError(8);
		}
	}
	while (repeat || year < YEAR_MIN_DATE || year > YEAR_MAX_DATE);

	printf(" Ввод года завершен. \n\n");
	pressEnterForContinue();
	return year;
}


/*
	@start
	@name setTime
	@prototype int setTime()
	@example setTime
	@description Описание функции
	@return Возврат функции
	@end
*/
int setTime()
{
	int time;
	int repeat;

	do
	{
		system("cls");
		getTitle("Ввод продолжительности фильма");
		repeat = 0;
		printf(" Подсказка: продолжительность фильма является целым числом и должна быть в промежутке от %d до %d минут. \n", TIME_MIN_MINUT, TIME_MAX_MINUT);
		printf(" Введите продолжительность: ");

		if (scanf_s("%d", &time) != 1)
		{
			rewind(stdin);
			getError(10);
			repeat = 1;
		}
		else if (time < TIME_MIN_MINUT || time > TIME_MAX_MINUT)
		{
			getError(9);
		}
	}
	while (repeat || time < TIME_MIN_MINUT || time > TIME_MAX_MINUT);

	printf(" Ввод продолжительности завершен. \n\n");
	pressEnterForContinue();
	return time;
}


/*
	@start
	@name setRating
	@prototype float setRating()
	@example setRating
	@description Описание функции
	@return Возврат функции
	@end
*/
float setRating()
{
	float rating;
	int repeat;

	do
	{
		getTitle("Ввод рейтинга фильма");
		repeat = 0;
		printf(" Подсказка: рейтинг фильма является вещественным числом и должен быть в промежутке от %d до %d. Разделение точкой, пример: 7.8 \n", RATING_MIN, RATING_MAX);
		printf(" Введите рейтинг: ");

		if (scanf_s("%f", &rating) != 1)
		{
			rewind(stdin);
			getError(13);
			repeat = 1;
		}
		else if (rating < RATING_MIN || rating > RATING_MAX)
		{
			getError(12);
		}
	}
	while (repeat || rating < RATING_MIN || rating > RATING_MAX);

	printf(" Ввод рейтинга  завершен. \n\n");
	pressEnterForContinue();
	return rating;
}


/*
	@start
	@name setGenre
	@prototype int setGenre()
	@example setGenre
	@description Описание функции
	@return Возврат функции
	@end
*/
int setGenre()
{
	int genre_number;
	char **genres = getGenresArrayList();
	int repeat;

	do
	{
		getTitle("Выбор жанра");
		repeat = 0;
		printf(" Подсказка: вам нужно выбрать только жанр из текущего списка. Если вашего жанра нет, возможно вы добавляете не фильм.");
		getGenresPrintList();
		printf(" Введите номер жанра: ");

		if (scanf_s("%d", &genre_number) != 1)
		{
			rewind(stdin);
			getError(10);
			repeat = 1;
		}
		else if (!getExistGenreCount(genre_number - 1)) // у нас отчёт от нуля
		{
			repeat = 1;
			getError(11);
		}
	}
	while (repeat);

	printf(" Ввод жанра завершен. \n\n");
	pressEnterForContinue();

	return genre_number - 1;
}


/*
	@start
	@name wrapGetfilterParams
	@prototype void wrapGetfilterParams(int filterParamYear, int filterParamTime)
	@example wrapGetfilterParams
	@description Описание функции
	@param  int	filterParamYear	=>  Описание аргумента 
	@param  int	filterParamTime	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void wrapGetfilterParams(int filterParamYear, int filterParamTime)
{
	getTitle("Контрольный вывод параметров для фильтрации");
	if (filterParamYear)
	{
		if (filterParamTime)
		{
			printf(" Фильтрация будет происходить по следующим параметрам:");
			printf("\n Год: %d", filterParamYear);
			printf("\n Продолжительность: %d", filterParamTime);
			pressEnterForContinue();
		}
		else
			getError(4);
	}
	else
		getError(5);
}


/*
	@start
	@name wrapGetFilmsSource
	@prototype void wrapGetFilmsSource(struct FILMS *films_source, int films_source_size)
	@example wrapGetFilmsSource
	@description Описание функции
	@param  struct FILMS *	films_source	=>  Описание аргумента 
	@param  int	films_source_size	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void wrapGetFilmsSource(struct FILMS *films_source, int films_source_size)
{
	getTitle("Контрольный вывод исходных данных");
	if (films_source != NULL)
		getFilms(films_source, films_source_size);
	else
		getError(3);
}


/*
	@start
	@name wrapGetFilmsResults
	@prototype void wrapGetFilmsResults(struct FILMS *films_result, int films_result_size, int film_processed)
	@example wrapGetFilmsResults
	@description Описание функции
	@param  struct FILMS *	films_result	=>  Описание аргумента 
	@param  int	films_result_size	=>  Описание аргумента 
	@param  int	film_processed	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
void wrapGetFilmsResults(struct FILMS *films_result, int films_result_size, int film_processed)
{
	getTitle("Вывод результата");
	if (film_processed)
		if (films_result != NULL)
			getFilms(films_result, films_result_size);
		else
			getError(6);
	else
		getError(14);


}


/*
	@start
	@name process
	@prototype struct FILMS *process(struct FILMS *items, int size, int year, int time, int *films_result_size, int *film_processed)
	@example process
	@description Описание функции
	@param  struct FILMS *	items	=>  Описание аргумента 
	@param  int	size	=>  Описание аргумента 
	@param  int	year	=>  Описание аргумента 
	@param  int	time	=>  Описание аргумента 
	@param  int *	films_result_size	=>  Описание аргумента 
	@param  int *	film_processed	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
struct FILMS *process(struct FILMS *items, int size, int year, int time, int *films_result_size, int *film_processed)
{
	struct FILMS *resultFilms = NULL;	// структура
	int i = 0;							// вспомогательные переменные
	int j = 0;

	getTitle("Обработка данных");
	if (items != NULL)
	{
		if (year)
		{
			if (time)
			{
				for (i = 0; i < size; i++)
				{
					if ((items + i)->year == year && (items + i)->time == time)
					{
						resultFilms = (struct FILMS*) realloc(resultFilms, (j + 1) * sizeof(struct FILMS));

						(resultFilms + j)->title = (char*) malloc(sizeof(char) * (strlen((items + i)->title) + 1));
						strcpy((resultFilms + j)->title, (items + i)->title);

						(resultFilms + j)->genre = (items + i)->genre;
						(resultFilms + j)->year = (items + i)->year;
						(resultFilms + j)->time = (items + i)->time;
						(resultFilms + j)->rating = (items + i)->rating;
						j++;
						*films_result_size = j;
					}
				}
				*film_processed = 1;
				printf("\n Обработка завершена.\n");
				printf(" Для просмотора результатов выполните пункт 6 из главного меню. \n");
				pressEnterForContinue();
			}
			else
				getError(4);
		}
		else
			getError(5);
	}
	else
		getError(3);

	return resultFilms;
}


/*
	@start
	@name freeMemory
	@prototype struct FILMS *freeMemory(struct FILMS *item, int size)
	@example freeMemory
	@description Описание функции
	@param  struct FILMS *	item	=>  Описание аргумента 
	@param  int	size	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
struct FILMS *freeMemory(struct FILMS *item, int size)
{
	int i;	// вспомогательная переменная

	if (item != NULL)
	{
		for (i = 0; i < size; i++)
			if ((item + i)->title != NULL)
			{
				printf("Очищаем : %s", (item + i)->title);
				free((item + i)->title);
				(item + i)->title = NULL;
			}
		free(item);
		item = NULL;
	}
	return NULL;
}


/*
	@start
	@name getGenresArrayList
	@prototype char **getGenresArrayList()
	@example getGenresArrayList
	@description Описание функции
	@return Возврат функции
	@end
*/
char **getGenresArrayList()
{
	int count = 0;	// количество жанров
	int i;			// вспомогательная переменная
	char **genres;	// адрес указателя на 1 символ строки

	char *genresArray[] = {"аниме", "биографический", "боевик", "вестерн", "военный",
		"детектив", "детский", "документальный", "драма", "исторический",
		"кинокомикс", "комедия", "концерт", "короткометражный", "криминал",
		"мелодрама", "мистика", "музыка", "мультфильм", "мюзикл", "научный",
		"приключения", "реалити-шоу", "семейный", "спорт", "ток-шоу", "триллер",
		"ужасы", "фантастика", "фильм-нуар", "фэнтези", "эротика", "\0"};

	while (*(genresArray + count))
		count++;

	genres = (char**) malloc(sizeof(char*) * (count + 1));
	for (i = 0; i < count; i++)
		*(genres + i) = genresArray[i];

	*(genres + count) = "\0";

	return genres;
}


/*
	@start
	@name getGenresPrintList
	@prototype void getGenresPrintList()
	@example getGenresPrintList
	@description Описание функции
	@return Возврат функции
	@end
*/
void getGenresPrintList()
{
	char **genres = getGenresArrayList();
	int i = 0;

	printf("\n\n");
	for (i = 0; *(genres + i) != "\0"; i++)
	{
		printf(" %2d. ", i + 1);
		printf("%-25s", *(genres + i));
		if ((i + 1) % 3 == 0)
			printf("\n");
	}
	printf("\n\n");
}


/*
	@start
	@name getGenresCount
	@prototype int getGenresCount()
	@example getGenresCount
	@description Описание функции
	@return Возврат функции
	@end
*/
int getGenresCount()
{
	char **genres = getGenresArrayList();
	int count = 0;

	while (strlen(*(genres + count)))
		count++;

	return count;
}


/*
	@start
	@name getExistGenreCount
	@prototype int getExistGenreCount(int number)
	@example getExistGenreCount
	@description Описание функции
	@param  int	number	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
int getExistGenreCount(int number)
{
	int count = getGenresCount();

	if (number < 0 || number >= count)
		return 0;

	return 1;
}


/*
	@start
	@name wrapSetSource
	@prototype struct FILMS *wrapSetSource(struct FILMS *films_source, int *films_source_size)
	@example wrapSetSource
	@description Описание функции
	@param  struct FILMS *	films_source	=>  Описание аргумента 
	@param  int *	films_source_size	=>  Описание аргумента 
	@return Возврат функции
	@end
*/
struct FILMS *wrapSetSource(struct FILMS *films_source, int *films_source_size)
{
	getTitle("Ввод данных");

	films_source = set(films_source_size);
	return films_source;
}