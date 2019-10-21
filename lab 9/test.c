#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fin, *fout;
	int i, j, flag = 0, nc = 0, max = 0, ns = 1, str; // nc - счётчик уникальных символов
	char s[80];                                       // ns - счётчик строк
	fin = fopen("input.txt", "r");                    // входной файл, открываем на чтение
	fout = fopen("output.txt", "w");                  // выходной файл, открываем на запись
	while (fgets(s, 80, fin))                         // проходим цикл по входному файлу
	{
		for (i = 0; i < strlen(s); i++)
		{
			for (j = 0; j < strlen(s); j++)
			{
				if (s[i] == s[j] && i != j) // проверяем каждый элемент строки на повторяемость
					flag = 1;
			}
			if (flag == 0) // если символ не повторяется
				nc++;      // счётчик увеличивается на 1
			else
				flag = 0;
		}
		if (max < nc)
		{ // ищем максимальное количество неповторяемых символов
			max = nc;
			str = ns; // записываем номер строки с их максимумом
		}
		ns++;
		nc = 0;
	}
	ns = 1;
	fclose(fin);
	fin = fopen("input.txt", "r");
	while (fgets(s, 80, fin))
	{                       // повторно построчно считываем исходный файл
		if (ns != str)      // кроме строки с максимальным количеством разных символов
			fputs(s, fout); // копируем его в выходной файл
		ns++;
	}
	fclose(fin); // закрываем файлы
	fclose(fout);
	return 0;
}
