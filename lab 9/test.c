#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fin, *fout;
	int i, j, flag = 0, nc = 0, max = 0, ns = 1, str; // nc - ������� ���������� ��������
	char s[80];                                       // ns - ������� �����
	fin = fopen("input.txt", "r");                    // ������� ����, ��������� �� ������
	fout = fopen("output.txt", "w");                  // �������� ����, ��������� �� ������
	while (fgets(s, 80, fin))                         // �������� ���� �� �������� �����
	{
		for (i = 0; i < strlen(s) - 2; i++)
		{
			for (j = 0; j < strlen(s) - 1; j++)
			{
				if (s[i] == s[j] && i != j) // ��������� ������ ������� ������ �� �������������
					flag = 1;
			}
			if (flag == 0) // ���� ������ �� �����������
				nc++;      // ������� ������������� �� 1
			else
				flag = 0;
		}
		if (max < nc)
		{ // ���� ������������ ���������� ������������� ��������
			max = nc;
			str = ns; // ���������� ����� ������ � �� ����������
		}
		ns++;
		nc = 0;
	}
	ns = 1;
	fclose(fin);
	fin = fopen("input.txt", "r");
	while (fgets(s, 80, fin))
	{                       // �������� ��������� ��������� �������� ����
		if (ns != str)      // ����� ������ � ������������ ����������� ������ ��������
			fputs(s, fout); // �������� ��� � �������� ����
		ns++;
	}
	fclose(fin); // ��������� �����
	fclose(fout);
	return 0;
}
