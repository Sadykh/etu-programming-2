char *setStr();																											// ввод строки
struct FILMS *set(int *size);																							// ввод структуры
void getHeadTables();																									// вывод заголовка таблицы
void getFilms(struct FILMS *items, int size);																			// контрольный вывод
void getFields(int i, struct FILMS *data);																				// вывод каждого поля
void setFilterParams(int *year, int *time);																				// ввод параметров для фильтрации
int setYear();																											// ввод года
int setTime();																											// ввод продолжительности
float setRating();																										// ввод рейтинга
int setGenre();																											// ввод жанра
void wrapGetfilterParams(int filterParamYear, int filterParamTime);														// обертка для вывода параметров для фильтрации
void wrapGetFilmsSource(struct FILMS *films_source, int films_source_size);												// обертка для вывода исходной структуры
struct FILMS *process(struct FILMS *items, int size, int year, int time, int *films_result_size, int *film_processed);	// обработка структуры
void wrapGetFilmsResults(struct FILMS *films_result, int films_result_size, int film_processed);						// обертка для вывода результатов
struct FILMS *freeMemory(struct FILMS *item, int size);																	// освобождение памяти
char **getGenresArrayList();																							// формирование списка жанров
void getGenresPrintList();																								// вывод списка жанров
int getExistGenreCount(int number);																						// проверка, существует ли введеный жанр
int setOffset();																										// установка смещения страниц
void getFilmsPage(struct FILMS *items, int size, int offset);															// вывод страницы с фильмом	
void getPageInfo(int maxPages, int page, int currentItem, int maxCurrentItems);											// вывод информации о странице
struct FILMS *wrapSetSource(struct FILMS *films_source, int *films_source_size);										// обертка для ввода исходный данных