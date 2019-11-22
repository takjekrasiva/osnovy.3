// ����������� ���������� ���������� �����, ������ ������, ���� ��� ��� ����������� �����.

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
	
	// �������� ������ � �������� �� ������
	if ((ifd = fopen("file1.txt", "r")) == NULL || (ofd = fopen("file2.txt", "w")) == NULL)
	{
		printf("file can not open\n");
		system("pause");
		return -1;
	}

	strarr = NULL;	// ������ ����� ������
	str = NULL;		// ������� ������ ������
	flag = NO;		// �������� ���� ������
	sflag = NO;		// �������� ���� �������
	strlen = 0;		// �������� ����� ������
	strcnt = 0;		// �������� ������� �����

	// ��������� ���� �� ������ �� ����� �����
	do {
		c = fgetc(ifd);	// ����� ������� ������ �� �����

		// ���� ����� ������
		if (c == '\n' || c == EOF)
		{
			str = (char*)realloc(str, (strlen + 2) * sizeof(char));	// �������� ������
			str[strlen++] = '\n';	// ���������� ������ �������� ������
			str[strlen] = '\0';		// ���������� ������ ����� ������
			
			flag = YES;	// ��������� ����
			// �������� �� ���� ����������� �������
			for (i = 0; i < strcnt; i++)
			{
				// ���� ������� ������ ��������� � ��� ��������� �������
				if (strcmp(str, strarr[i]) == 0)
				{
					flag = NO;	// �������� ����
					break;	// ������� �� �����
				}
			}
			
			// ���� ���� ������� ������
			if (flag == YES)
			{
				strarr = (char**)realloc(strarr, (strcnt + 1) * sizeof(char*));	// �������� ������ � ������� �����
				strarr[strcnt++] = str;		// ���������� ���� ������� ������
			}
			// ���� ���� ��� ������
			else
			{
				free(str);	// ������� ������� ������
			}

			str = NULL;		// ������ ������
			sflag = NO;		// �������� ���� �����������
			flag = NO;		// �������� ���� ������
			strlen = 0;		// �������� ����� ������� ������
		}
		// ���� ����� ������ ��� ���������
		else if (c == ' ' || c == '\t')
		{
			// ���� ������ �������� � ��� ������ �����������
			if (sflag == NO && flag == YES)
			{
				str = (char*)realloc(str, (strlen + 1) * sizeof(char));		// �������� ������ � ������
				str[strlen++] = ' ';	// ���������� � ������ ������
				sflag = YES;	// ��������� ���� �����������
			}
		}
		// �����
		else
		{
			str = (char*)realloc(str, (strlen + 1) * sizeof(char));	// �������� ������ � ������
			str[strlen++] = c;	// ���������� � ��� ������� ������
			flag = YES;		// ��������� ���� ������
			sflag = NO;		// �������� ���� �����������
		}
	} while (c != EOF);
	fclose(ifd);	// ��������� ������� ����
	
	// �������� �� ���� ����������� �������
	for (i = 0; i < strcnt; i++)
	{
		fputs(strarr[i], ofd);	// ������� ������ � ����
		free(strarr[i]);		// ����������� ���������� ������
	}
	fclose(ofd);	// ��������� �������� ����
	free(strarr);	// ����������� ������

	printf("Program complete\n");
	system("pause");
	return 0;
}