#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

const char a1[] = "int";
const char a2[] = "char";
const char a3[] = "double";
const char a4[] = "float";
const char a5[] = "long";
const char a6[] = "signed";
const char a7[] = "unsigned";
const char a8[] = "short";
const char a9[] = "void";//Т.к. нам нужно будет проверить на тип возвращаемого значение(в прототипе он обязан быть) создадим массивы
//И потом в функции поиска, если нам встретится один из этих значений, мы продолжим обработку

char search(const char* line);//Функция поиска, туда закидывам строку, в которой ищем

int main() {
	HANDLE hStdout;
	WORD foregroundColor0;
	WORD foregroundColor1;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	foregroundColor0 = FOREGROUND_BLUE;//Цветова
	FILE *fin;
	char line[100];//Сюда мы будем записывать строку из файла
	char *ptr = NULL;//Для перемещения по строке
	int flag;
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;//Флаги на комментарии и записть данных в ""
	fin = fopen("base.txt", "r");
	if (fin == NULL) {
		system("pause");
	}
	while (!feof(fin)) {
		memset(line, NULL, 100);//Обнуляем строку, чтобы не было наложения 
		fgets(line, 100, fin);//Считываем строку
		flag1 = 0;//Обнуляем флаг, ответственный за коменнарии типа //
		ptr = line;
		while (*ptr != '\n' && *ptr != '\0') {
			if (*ptr == '/' && *(ptr + 1) == '/' && flag1 == 0)//Если в комментарии, то flag1 = 1
				flag1 = 1;
			if (*ptr == '/' && *(ptr + 1) == '*' && flag2 == 0)//Если вошли в комментарий типа /**/ то flag2 = 1
				flag2 = 1;
			if (*ptr == '*' && *(ptr + 1) == '/' && flag2 == 1)//Если вышли, то 0
				flag2 = 0;
			if (*ptr == '\"' && flag3 == 1) { //Вот тут мне крайне лень расписывать :) поэтому если не поймёшь, то запишу голосовое
				flag3 = 0;
				goto n;
			}
			if (*ptr == '\"' && flag3 == 0) {
				flag3 = 1;
				goto n;
			}
			if (*ptr == '"' && flag4 == 1) {
				flag4 = 0;
				goto n;
			}
			if (*ptr == '"' && flag4 == 0) {
				flag4 = 1;
				goto n;
			}
		n:;
			if (flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0) {//Если мы не в комментариях и не в ""
				if (*(ptr + 1) == ' ' || *(ptr + 1) == '\\') {//Страшная штука для пропуска пробелов и переходов на новую строку 
					while (*(ptr) == ' ') {//Если пробелы, то посимвольно выводим в консоль и радуемся жизни
						printf("%c", *ptr);
						ptr++;
					}
					if (*ptr == '\\') {//А если переход на новую строку
						do {
							printf("%c", *ptr);//Выводим символ
							printf("\n");//Выводим \n
							fgets(line, 100, fin);//Считываем новую строку
							ptr = line;
							while (*ptr == ' ') {//Так же обрабатываем пробелы
								printf("%c", *ptr);
								ptr++;
							}
						} while (*ptr == '\\');//Продолжаем этот цикл до тех пор, пока нам не прекратится встречатся "\"
					}
				}
				char* tmp;//Указатель для перемещения по дополнительной строке
				char str[100];//Дополнительная строка
				memset(str, NULL, 100);//Заполняем её нулями
				tmp = str;
				while (*ptr != ';' && *ptr != '\n' && *ptr != '\0') {//Т.к. мы нашли слово, то можем смело записывать его в дополнительную строку из основной до ;
					*tmp = *ptr;
					ptr++;
					tmp++;
				}
				if (*ptr == ';' && *(ptr - 1) == ')' && search(str) == 't') {//Тпереь мы проверяем это слово на наличие возвращаемого значения
					SetConsoleTextAttribute(hStdout, foregroundColor0);//Если проверку строка прошла, то меняем цвет
					tmp = str;//Указатель на начала доп строки
					while (*tmp != '\n' && *tmp != '\0') {//Выводим доп строку
						printf("%c", *tmp);
						tmp++;
					}
				}
				else {
					SetConsoleTextAttribute(hStdout, 7);//Если не прошли, то меняем цвет на обычный и выводим доп строку
					tmp = str;
					while (*tmp != '\n' && *tmp != '\0') {
						printf("%c", *tmp);
						tmp++;
					}
				}
				if (*ptr == ';')//Важная проверка, т.к. если мы не сделаем таку проверку с последующим выводом у нас не будет выводится ;
					printf("%c", *ptr);
			}
			else {
				SetConsoleTextAttribute(hStdout, 7);
				printf("%c", *ptr);//Выводим любой символ в стандартном цвете 
			}
			ptr++;
		}
		printf("\n");
	}
	system("pause");
}

char search(const char* line) {
	char* t1 = strstr(line, a1);
	char* t2 = strstr(line, a2);
	char* t3 = strstr(line, a3);
	char* t4 = strstr(line, a4);
	char* t5 = strstr(line, a5);
	char* t6 = strstr(line, a6);
	char* t7 = strstr(line, a7);
	char* t8 = strstr(line, a8);
	char* t9 = strstr(line, a9);//Ищем в доп строке один из параметров(прочитай шо делает strstr)
	if (t1 == NULL && t2 == NULL && t3 == NULL && t4 == NULL && t5 == NULL && t6 == NULL && t7 == NULL && t8 == NULL && t9 == NULL)//Если таковых нет, то возращаем f
		return 'f';
	if (t1 != NULL) {//Тут 9 таких условий, все идентичны, ну кроме последнего 
		if (*t1 == line[0] && (*(t1 + 3) == ' ' || *(t1 + 3) == '\t' || *(t1 + 3) == '*' || *(t1 + 3) == '&')) {//Если указатель на начале строки и после конца значение идёт одно из перечисленных значений(* и & нужно учитывать, т.к. возвращаемое значение может быть как по ссылке, так и по указателю)
			return 't';//Возвращаем t
		}
	}
	if (t2 != NULL) {
		if (*t1 == line[0] && (*(t1 + 4) == ' ' || *(t1 + 4) == '\t' || *(t1 + 4) == '*' || *(t1 + 4) == '&')) {
			return 't';
		}
	}
	if (t3 != NULL) {
		if (*t1 == line[0] && (*(t1 + 6) == ' ' || *(t1 + 6) == '\t' || *(t1 + 6) == '*' || *(t1 + 6) == '&')) {
			return 't';
		}
	}
	if (t4 != NULL) {
		if (*t1 == line[0] && (*(t1 + 5) == ' ' || *(t1 + 5) == '\t' || *(t1 + 5) == '*' || *(t1 + 5) == '&')) {
			return 't';
		}
	}
	if (t5 != NULL) {
		if (*t1 == line[0] && (*(t1 + 4) == ' ' || *(t1 + 4) == '\t' || *(t1 + 4) == '*' || *(t1 + 4) == '&')) {
			return 't';
		}
	}
	if (t6 != NULL) {
		if (*t1 == line[0] && (*(t1 + 6) == ' ' || *(t1 + 6) == '\t' || *(t1 + 6) == '*' || *(t1 + 6) == '&')) {
			return 't';
		}
	}
	if (t7 != NULL) {
		if (*t1 == line[0] && (*(t1 + 8) == ' ' || *(t1 + 8) == '\t' || *(t1 + 8) == '*' || *(t1 + 8) == '&')) {
			return 't';
		}
	}
	if (t8 != NULL) {
		if (*t1 == line[0] && (*(t1 + 5) == ' ' || *(t1 + 5) == '\t' || *(t1 + 5) == '*' || *(t1 + 5) == '&')) {
			return 't';
		}
	}
	if (t5 != NULL) {
		if (*t9 == line[0] && (*(t9 + 4) == ' ' || *(t9 + 4) == '\t')) {//А вот туть не нужно учитывать * и &, т.к. это void
			return 't';
		}
	}
