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
const char a9[] = "void";//�.�. ��� ����� ����� ��������� �� ��� ������������� ��������(� ��������� �� ������ ����) �������� �������
//� ����� � ������� ������, ���� ��� ���������� ���� �� ���� ��������, �� ��������� ���������

char search(const char* line);//������� ������, ���� ��������� ������, � ������� ����

int main() {
	HANDLE hStdout;
	WORD foregroundColor0;
	WORD foregroundColor1;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	foregroundColor0 = FOREGROUND_BLUE;//�������� ������
	FILE *fin;
	char line[100];//���� �� ����� ���������� ������ �� �����
	char *ptr = NULL;//��� ����������� �� ������
	int flag;
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;//����� �� ����������� � ������� ������ � ""
	fin = fopen("base.txt", "r");
	if (fin == NULL) {
		system("pause");
	}
	while (!feof(fin)) {
		memset(line, NULL, 100);//�������� ������, ����� �� ���� ��������� 
		fgets(line, 100, fin);//��������� ������
		flag1 = 0;//�������� ����, ������������� �� ���������� ���� //
		ptr = line;
		while (*ptr != '\n' && *ptr != '\0') {
			if (*ptr == '/' && *(ptr + 1) == '/' && flag1 == 0)//���� � �����������, �� flag1 = 1
				flag1 = 1;
			if (*ptr == '/' && *(ptr + 1) == '*' && flag2 == 0)//���� ����� � ����������� ���� /**/ �� flag2 = 1
				flag2 = 1;
			if (*ptr == '*' && *(ptr + 1) == '/' && flag2 == 1)//���� �����, �� 0
				flag2 = 0;
			if (*ptr == '\"' && flag3 == 1) { //��� ��� ��� ������ ���� ����������� :) ������� ���� �� ������, �� ������ ���������
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
			if (flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0) {//���� �� �� � ������������ � �� � ""
				if (*(ptr + 1) == ' ' || *(ptr + 1) == '\\') {//�������� ����� ��� �������� �������� � ��������� �� ����� ������ 
					while (*(ptr) == ' ') {//���� �������, �� ����������� ������� � ������� � �������� �����
						printf("%c", *ptr);
						ptr++;
					}
					if (*ptr == '\\') {//� ���� ������� �� ����� ������
						do {
							printf("%c", *ptr);//������� ������
							printf("\n");//������� \n
							fgets(line, 100, fin);//��������� ����� ������
							ptr = line;
							while (*ptr == ' ') {//��� �� ������������ �������
								printf("%c", *ptr);
								ptr++;
							}
						} while (*ptr == '\\');//���������� ���� ���� �� ��� ���, ���� ��� �� ����������� ���������� "\"
					}
				}
				char* tmp;//��������� ��� ����������� �� �������������� ������
				char str[100];//�������������� ������
				memset(str, NULL, 100);//��������� � ������
				tmp = str;
				while (*ptr != ';' && *ptr != '\n' && *ptr != '\0') {//�.�. �� ����� �����, �� ����� ����� ���������� ��� � �������������� ������ �� �������� �� ;
					*tmp = *ptr;
					ptr++;
					tmp++;
				}
				if (*ptr == ';' && *(ptr - 1) == ')' && search(str) == 't') {//������ �� ��������� ��� ����� �� ������� ������������� ��������
					SetConsoleTextAttribute(hStdout, foregroundColor0);//���� �������� ������ ������, �� ������ ����
					tmp = str;//��������� �� ������ ��� ������
					while (*tmp != '\n' && *tmp != '\0') {//������� ��� ������
						printf("%c", *tmp);
						tmp++;
					}
				}
				else {
					SetConsoleTextAttribute(hStdout, 7);//���� �� ������, �� ������ ���� �� ������� � ������� ��� ������
					tmp = str;
					while (*tmp != '\n' && *tmp != '\0') {
						printf("%c", *tmp);
						tmp++;
					}
				}
				if (*ptr == ';')//������ ��������, �.�. ���� �� �� ������� ���� �������� � ����������� ������� � ��� �� ����� ��������� ;
					printf("%c", *ptr);
			}
			else {
				SetConsoleTextAttribute(hStdout, 7);
				printf("%c", *ptr);//������� ����� ������ � ����������� ����� 
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
	char* t9 = strstr(line, a9);//���� � ��� ������ ���� �� ����������(�������� �� ������ strstr)
	if (t1 == NULL && t2 == NULL && t3 == NULL && t4 == NULL && t5 == NULL && t6 == NULL && t7 == NULL && t8 == NULL && t9 == NULL)//���� ������� ���, �� ��������� f
		return 'f';
	if (t1 != NULL) {//��� 9 ����� �������, ��� ���������, �� ����� ���������� 
		if (*t1 == line[0] && (*(t1 + 3) == ' ' || *(t1 + 3) == '\t' || *(t1 + 3) == '*' || *(t1 + 3) == '&')) {//���� ��������� �� ������ ������ � ����� ����� �������� ��� ���� �� ������������� ��������(* � & ����� ���������, �.�. ������������ �������� ����� ���� ��� �� ������, ��� � �� ���������)
			return 't';//���������� t
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
		if (*t9 == line[0] && (*(t9 + 4) == ' ' || *(t9 + 4) == '\t')) {//� ��� ���� �� ����� ��������� * � &, �.�. ��� void
			return 't';
		}
	}
