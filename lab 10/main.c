// —копировать содержимое текстового файла, удал€€ строки, если они уже встречались ранее.

#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO 0
#define YES 1

int main(void)
{
	int flag, sflag, strlen, strcnt, i;
	char **strarr, *str, c;
	FILE *ifd, *ofd;
	
	// открытие файлов и проверка на ошибки
	if ((ifd = fopen("file1.txt", "r")) == NULL || (ofd = fopen("file2.txt", "w")) == NULL)
	{
		printf("file can not open\n");
		system("pause");
		return -1;
	}

	strarr = NULL;	// массив строк пустой
	str = NULL;		// текущая строка пустая
	flag = NO;		// опускаем флаг строки
	sflag = NO;		// опускаем флаг пробела
	strlen = 0;		// обнуляем длину строки
	strcnt = 0;		// обнуляем счетчик строк

	// повторяем пока не дойдем до конца файла
	do {
		c = fgetc(ifd);	// берем текущий символ из файла

		// если конец строки
		if (c == '\n' || c == EOF)
		{
			str = (char*)realloc(str, (strlen + 2) * sizeof(char));	// выделяем память
			str[strlen++] = '\n';	// записываем символ перевода строки
			str[strlen] = '\0';		// записываем символ конца строки
			
			flag = YES;	// поднимаем флаг
			// проходим по всем сохраненным строкам
			for (i = 0; i < strcnt; i++)
			{
				// если текущая строка совпадает с уже найденной строкой
				if (strcmp(str, strarr[i]) == 0)
				{
					flag = NO;	// опускаем флаг
					break;	// выходим из цикла
				}
			}
			
			// если флаг остался поднят
			if (flag == YES)
			{
				strarr = (char**)realloc(strarr, (strcnt + 1) * sizeof(char*));	// выделяем память в массиве строк
				strarr[strcnt++] = str;		// записываем туда текущую строку
			}
			// если флаг был опущен
			else
			{
				free(str);	// удаляем текущую строку
			}

			str = NULL;		// строка пустая
			sflag = NO;		// опускаем флаг разделителя
			flag = NO;		// опускаем флаг строки
			strlen = 0;		// обнуляем длину текущей строки
		}
		// если нашли пробел или табуляцию
		else if (c == ' ' || c == '\t')
		{
			// если строка началась и это первый разделитель
			if (sflag == NO && flag == YES)
			{
				str = (char*)realloc(str, (strlen + 1) * sizeof(char));		// выделяем память в строке
				str[strlen++] = ' ';	// записываем в строку пробел
				sflag = YES;	// поднимаем флаг разделителя
			}
		}
		// иначе
		else
		{
			str = (char*)realloc(str, (strlen + 1) * sizeof(char));	// выделяем память в строке
			str[strlen++] = c;	// записываем в нее текущий символ
			flag = YES;		// поднимаем флаг строки
			sflag = NO;		// опускаем флаг разделителя
		}
	} while (c != EOF);
	fclose(ifd);	// закрываем входной файл
	
	// проходим по всем сохраненным строкам
	for (i = 0; i < strcnt; i++)
	{
		fputs(strarr[i], ofd);	// выводим строку в файл
		free(strarr[i]);		// освобождаем выделенную память
	}
	fclose(ofd);	// закрываем выходной файл
	free(strarr);	// освобождаем память

	printf("Program complete\n");
	system("pause");
	return 0;
}