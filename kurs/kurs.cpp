#define _CRT_SECURE_NO_WARNINGS // отключение вывода предупреждений в IDE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100     // длина названия категории базы
#define MAXLEN 1000 // максимальная длина позиции
#define YES 1
#define NO 0
#define CATEGORIES 8 // количество категорий
typedef struct sNode // объявление структуры sNode
{
	int id;             // порядковый номер типа целое число
	char name[LEN];     // название позиции
	char category[LEN]; // названия категории
	int cost;           // цена, целое число
	struct sNode *next; // указание на следующую структуру
} Node;
int showMenu() // функция показа меню
{
	int choice; // выбор пункта меню
	printf("1 - Add product\n");
	printf("2 - Editing record \n");
	printf("3 - Delete record\n");
	printf("4 - Display the database on the screen in alphabetical order by product category or product name\n");
	printf("5 - Selection of the 'minimum basket' for a given list of products\n");
	printf("\nPress 0 and Enter if you want to quit.\n");
	scanf("%d", &choice);
	return choice;
}
Node *init(int a) // узел инициализации базы данных
{
	Node *lst; // структура списка в памяти
	lst = (Node *)malloc(sizeof(Node));
	lst->id = a;      // принимаем значение id во внутреннюю переменную a
	lst->next = NULL; // указатель на переход
	return (lst);
}
Node *deleteHead(Node *head) // узел очистки заголовка
{
	Node *temp;        // объявление временного узла
	temp = head->next; // передача заголовка следующему узлу через переменную temp
	free(head);        // очистка заголовка
	return (temp);     // возврат данных заголовка
}
void deleteNode(Node *lst, Node *head) // функция удаления узла
{
	Node *temp;               // объявление временного узла
	temp = head;              // копирование заголовка в переменную temp
	while (temp->next != lst) // пока не пройден весь список
	{
		temp = temp->next; // очищать позицию
	}
	temp->next = lst->next;
	free(lst); // очистка списка
}
void freeList(Node **head) // функция очистки списка
{
	Node *current = *head;
	Node *next = NULL;
	do
	{
		next = current->next;
		free(current);
		current = next;
	} while (current != NULL);
	free(current);
}
Node *Appendlist(Node **headRef) // узел привязки списка
{
	Node *current = *headRef; // загрузка узла
	Node *lst;
	lst = (Node *)malloc(sizeof(Node)); // выделение памяти
	lst->next = NULL;
	if (current == NULL)
	{
		*headRef = lst;
	}
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = lst;
	}
	return (lst);
}
void alphSort(Node **headRef, int structType, int count) // функция алфавитной сортировки данных
{
	Node *current;      // загрузка узла current
	Node *next;         // указание на следующий узел
	int noSwap;         // переменная подкачки
	int iBuf;           // переменная буфера
	char cBuf[MAXLEN];  // данные буфера
	switch (structType) // выбор типа структуры
	{
	case 1: // в первом случае сортировка названия
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->next;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->name, next->name) > 0)
				{
					iBuf = current->id;                // сортировка
					current->id = next->id;            // в алфавитном
					next->id = iBuf;                   // порядке
					strcpy(cBuf, current->name);       // перенос данных
					strcpy(current->name, next->name); // на новые
					strcpy(next->name, cBuf);          // позиции
					strcpy(cBuf, current->category);   // через буфер
					strcpy(current->category, next->category);
					strcpy(next->category, cBuf);
					iBuf = current->cost;
					current->cost = next->cost;
					next->cost = iBuf;
					noSwap = 0;
				}
				current = current->next;
				next = current->next;
			}
			if (noSwap == 1)
				break;
		}
		break;
	case 2: // во втором случае сортировка категории
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->next;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->category, next->category) > 0)
				{
					iBuf = current->id;
					current->id = next->id;
					next->id = iBuf;
					strcpy(cBuf, current->name);
					strcpy(current->name, next->name);
					strcpy(next->name, cBuf);
					strcpy(cBuf, current->category);
					strcpy(current->category, next->category);
					strcpy(next->category, cBuf);
					iBuf = current->cost;
					current->cost = next->cost;
					next->cost = iBuf;
					noSwap = 0;
				}
				current = current->next;
				next = current->next;
			}
			if (noSwap == 1)
				break;
		}
		break;
	default:
		break;
	}
}
void getData(Node **headRef, int *countItemsRet, int *itemNumRet) // функция получения данных
{
	FILE *fpin;                    // объявление входного файла с данными базы
	FILE *finit;                   // объявление инициализирующего файла
	int dataNum;                   // переменная нумерации данных
	int itemNum = 0;               // переменная номера позиции
	int inItem = NO;               // логическая переменная наличия данных в скобках
	int countItems = 0;            // переменная количества позиций
	int i = 0;                     // переменная счетчика
	char line[MAXLEN];             // переменная строки данных
	Node *item_ptr = NULL;         // указатель на позицию
	fpin = fopen("base.txt", "r"); // открытие базы данных из файла
	if (fpin == NULL)              // если файла не существует
	{
		finit = fopen("base.txt", "w"); // создание пустого файла
		fclose(finit);                  // и закрытие записи в него
		fpin = fopen("base.txt", "r");  // открытие файла на чтение
	}
	fscanf(fpin, "%d\n", &countItems); // сканирование количества позиций из файла
	while (!feof(fpin))
	{
		fscanf(fpin, "%s\n", line);
		if (line == NULL)
			break;
		if (*line == '(') // нахождение данных в скобках
		{
			inItem = YES;     // если данные найдены
			itemNum++;        // считаем в переменную
			if (itemNum == 1) // если она не пустая
			{
				item_ptr = *headRef; // возвращаем указатель в headRef
			}
			else // если данные не найдены
			{
				item_ptr = Appendlist(&(*headRef)); // присваиваем указателю список
			}
			dataNum = 0;
			continue;
		}
		if (*line == ')') // если нашли конец данных в скобках
		{
			inItem = NO; // не считаем это за дополнительные данные
			continue;
		}
		if (inItem) // если существуют данные в скобках
		{
			i = -1;    // присваиваем счетчику запас
			++dataNum; // наращиваем переменную количества данных
			switch (dataNum)
			{
			case 1:                        // обработка id
				item_ptr->id = atoi(line); // перемещение указателя id к строке данных
				break;
			case 2: // обработка категории
				do
				{
					i++;                             // увеличиваем счетчик
					item_ptr->category[i] = line[i]; // перемещение указателя категории к соответствующей строке с данными
				} while (line[i] != '\0');           // пока не найден конец строки
				break;
			case 3: // обработка имени
				do
				{
					i++;                         // увеличиваем счетчик
					item_ptr->name[i] = line[i]; // перемещение указателя названия к соответствующей строке с данными
				} while (line[i] != '\0');       // пока не найден конец строки
				break;
			case 4:                          // обработка стоимости
				item_ptr->cost = atoi(line); // перемещение указателя стоимости к строке данных
				break;
			}
		}
	}
	fclose(fpin);                // закрытие данных
	*itemNumRet = itemNum;       // возврат номера в БД
	*countItemsRet = countItems; // возврат количества позиций в БД
}
void putData(Node **headRef, int itemNum) // функция записи данных с аргументами в виде узла и номера позиции
{
	FILE *fpin;                     // открытие файла с БД
	Node *current = *headRef;       // перемещение указателя в начало
	fpin = fopen("base.txt", "w");  // открытие файла базы на запись
	fprintf(fpin, "%d\n", itemNum); // вывод номера позиции
	while (current != NULL)         // цикл по базе данных
	{
		fprintf(fpin, "(\n");                     // пустая строка
		fprintf(fpin, "%d\n", current->id);       // вывод порядкового номера данных
		fprintf(fpin, "%s\n", current->category); // вывод категории данных
		fprintf(fpin, "%s\n", current->name);     // вывод поля названия
		fprintf(fpin, "%d\n", current->cost);     // вывод поля стоимости
		fprintf(fpin, ")\n");                     // пустая строка
		current = current->next;                  // перемещение к следующей позиции
	}
	fclose(fpin); // закрытие файла
}
int main() // основной код
{
	Node *HeadPointer = init(0);                                                                                       // инициализация указателя заголовка
	Node *ItemPointer = NULL;                                                                                          // инициализации указателя позиции
	char WantedName[LEN];                                                                                              // переменная названия
	int itemNum;                                                                                                       //  переменная номера позиции
	int countItems;                                                                                                    // перменная количества позиций
	int i = 0;                                                                                                         // счётчик
	int need_menu;                                                                                                     // переменная команды выбора меню
	int need_cost;                                                                                                     // ... выбора стоимости
	int need_item;                                                                                                     // ... выбора позицци
	int need_category;                                                                                                 // ... выбора категории
	int need_showCategory;                                                                                             // ... показа категории
	char categories[CATEGORIES][100] = { "Fruits", "Meat", "Milk", "Drinks", "Candy", "Vegetables", "Bread", "Bakery" }; // категории товаров
	int need_basketCategories[CATEGORIES + 1];                                                                         // переменная корзины товаров по категориям
	getData(&HeadPointer, &countItems, &itemNum);                                                                      // вызов функции считывания данных

	do
	{
		need_menu = showMenu(); // показ меню
		switch (need_menu)
		{
		case 1:                     // вывод справки по навигации
			printf("1 - Fruits\n"); // каждая категория имеет свой номер
			printf("2 - Meat\n");
			printf("3 - Milk\n");
			printf("4 - Drinks\n");
			printf("5 - Candy\n");
			printf("6 - Vegetables\n");
			printf("7 - Bread\n");
			printf("8 - Bakery\n");
			printf("Select product category : ");
			scanf("%d", &need_category); // ввод нужного номера категории
			printf("If nothing happens, press any key\n");
			printf("Enter the item name :\n");
			getchar(); // ввод названия продукта
			printf("If nothing happens, press any key\n");
			fgets(WantedName, LEN, stdin);
			printf("If nothing happens, press any key\n");
			printf("Enter the price of the item : "); // ввод цены продукта
			scanf("%d", &need_cost);
			countItems++;     // считаем введённу/ позицию
			if (itemNum == 0) // если номер продукта нулевой
			{
				ItemPointer = HeadPointer; // перемещаемся в начало
			}
			else // иначе
			{
				ItemPointer = Appendlist(&HeadPointer); // перемещаемся к списку
			}
			ItemPointer->id = countItems;  // передаем введенные данные номера позиции
			ItemPointer->cost = need_cost; // и стоимости
			i = -1;
			do
			{
				i++;
				ItemPointer->name[i] = WantedName[i]; // и названия позиции
			} while (WantedName[i] != '\0');          // пока не дошли до конца ввода
			i = -1;
			do
			{
				i++;
				ItemPointer->category[i] = categories[need_category - 1][i]; // передаем категорию
			} while (categories[need_category - 1][i] != '\0');              // пока не дошли до конца ввода
			itemNum++;                                                       // наращиваем счетчик позиции
			break;
		case 2:

			if (!itemNum) // если позиций нет
			{
				printf("There is no items here\n"); // говорим об этом

				break;
			}
			printf("Select the item you want to change : \n");
			ItemPointer = HeadPointer;
			i = 1;
			while (ItemPointer != NULL)
			{
				printf("%d - %s\n", i, ItemPointer->name); // меняем названия позиции
				i++;
				ItemPointer = ItemPointer->next; // переходим к следующей позиции
			}
			ItemPointer = HeadPointer; // перемещаемся в начало
			scanf("%d", &need_item);   // даём команду смены позицции
			for (i = 0; i < need_item - 1; i++)
			{
				ItemPointer = ItemPointer->next; // перемещаемся к следующей позиции
			}
			printf("Old item type : %s\n||||||||||\n", ItemPointer->category); // вывод категорий
			for (i = 0; i < CATEGORIES; i++)
			{
				printf("%d %s\n", i + 1, &categories[i]);
			}
			printf("Enter a new category of product : "); // ввод новой категории
			scanf("%d", &need_category);
			printf("Old product name : %s\nEnter new product name : ", ItemPointer->name); // замена названия продукта
			printf("If nothing happens, press any key\n");
			getchar();
			fgets(WantedName, LEN, stdin);
			printf("If nothing happens, press any key\n");
			getchar();
			printf("Old cost: %d\nEnter new cost : ", ItemPointer->cost); // замена стоимости продукта
			scanf("%d", &need_cost);
			ItemPointer->cost = need_cost; // запись новых данных в базу
			i = -1;
			do
			{
				i++;
				ItemPointer->name[i] = WantedName[i];
			} while (WantedName[i] != '\0'); // пока не дошли до конца данных
			i = -1;
			i = -1;
			do
			{
				i++;
				ItemPointer->category[i] = categories[need_category - 1][i]; // то же самое с категорией
			} while (categories[need_category - 1][i] != '\0');

			break;
		case 3:
			if (!itemNum) // если не нашли позицию
			{
				printf("There is no items here\n");

				break;
			}
			printf("Select the item you want to remove : \n"); // обработка удаления позиции (продукта)
			ItemPointer = HeadPointer;                         // идём с начала
			i = 1;
			while (ItemPointer != NULL) // вывод данных о позициях
			{
				printf("%d %s\n", i, ItemPointer->name);
				i++;
				ItemPointer = ItemPointer->next;
			}
			scanf("%d", &need_item); // выбираем, что хотим удалить
			ItemPointer = HeadPointer;
			for (i = 0; i < need_item - 1; i++)
			{
				ItemPointer = ItemPointer->next;
			}
			if (need_item == 1) // если это первая позиция
			{
				HeadPointer = deleteHead(ItemPointer); // удаляем заголовок
			}
			else // иначе
			{
				deleteNode(ItemPointer, HeadPointer); // удаляем его по указателю
			}
			itemNum--;    // уменьшаем счетчик позиций
			if (!itemNum) // если позиций нет
			{
				HeadPointer = init(0); // очищаем заголовок
			}
			break;
		case 4:

			if (!itemNum) // если нет позиций
			{
				printf("There is no items here\n"); // говорим об этом
				break;
			}
			printf("Choose sorting method: \n"); // выбор данных по которым будет производиться сортировка
			printf("1 - Name\n2 - Category\n");  // имя либо категория
			scanf("%d", &need_showCategory);     // получаем выбор

			alphSort(&HeadPointer, need_showCategory, itemNum); // вызываем функцию сортировки
			ItemPointer = HeadPointer;                          // идём в начало
			i = 1;
			while (ItemPointer != NULL)
			{
				printf("      <%d>      \n", i);                 // выводим
				printf("ID: %d\n", ItemPointer->id);             // результат
				printf("Category: %s\n", ItemPointer->category); // сортировки
				printf("Name: %s\n", ItemPointer->name);         // по нужным
				printf("Cost: %d\n", ItemPointer->cost);         // полям
				i++;
				ItemPointer = ItemPointer->next; // идём дальше
			}
			break;
		case 5:
			if (!itemNum) // если нет данных
			{
				printf("There is no items here\n"); // говорим об этом
				break;
			}
			for (i = 0; i < CATEGORIES; i++)
			{
				printf("%d %s\n", i + 1, categories[i]); // вывод всех категорий
			}
			printf("Select the types of goods for the minimum basket.\nEnter by one type.When finished, enter 0\n"); // обработка выбора позиций
			i = 0;
			do
			{
				scanf("%d", &need_basketCategories[i]); // ввод данных в корзину
				if (i)
				{
					for (int j = 0; j < i; j++)                                   // цикл по корзине
						if (need_basketCategories[j] == need_basketCategories[i]) // если позиция уже в корзине
						{                                                         // говорим об этом
							printf("This type of product is already in the basket. Choose a different one or finish the selection.\n");
							i--;
						}
				}
				i++;
			} while (need_basketCategories[i - 1]);
			i = 0;
			while (need_basketCategories[i])
			{
				int max = 100000;          // задаем максимум данных в корзине
				Node *max_ptr = NULL;      // сброс максимального значния указателя
				ItemPointer = HeadPointer; // перемещение к началу
				while (ItemPointer != NULL)
				{
					if (!strcmp(ItemPointer->category, categories[need_basketCategories[i] - 1])) // если указатель категории не совпадает с выбранной категорией
					{
						if (ItemPointer->cost < max) // если в текущем указателе стоимость меньше максимальной
						{
							max = ItemPointer->cost; // присваиваем переменной максимума стимость текущего элемента
							max_ptr = ItemPointer;   // и даём указателю информацию о положении максимальной стоимости
						}
					}
					ItemPointer = ItemPointer->next; // идём дальше
				}
				i++;
				if (!(max_ptr == NULL)) // если есть информация о позиции максимальной стоимости
				{
					printf("      <%d>      \n", i); // вывод данных
					printf("ID: %d\n", max_ptr->id);
					printf("Category: %s\n", max_ptr->category);
					printf("Name: %s\n", max_ptr->name);
					printf("Cost: %d\n", max_ptr->cost);
				}
			}
			break;
		default:
			break;
		};
	} while (need_menu); // возврат к меню выбора команды
	if (itemNum)
	{
		putData(&HeadPointer, countItems); // запись данных
	}
	freeList(&HeadPointer); // очистка списка
	return 0;
}