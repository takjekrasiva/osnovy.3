#include <stdio.h>
#define BUF_SIZE 1000 // максимальный размер линии

int compareLines(char *left, char *right) { // функция сравнения линий
    while (1) {
        if (*left == '\0' || *left == '\n') { // все непоследние строки считываются как "line\n\0", последняя как "line\0"
            if (*right == '\0' || *right == '\n') return 0; // это сравение останавливается на \0 или \n

            return -1;
        }

        if (*left != *right) {
            return -1;
        }

        left++;
        right++;
    }
}

int main() {
    char currentLine[BUF_SIZE]; // текущая линия
    char previousLine[BUF_SIZE]; // предыдущая линия
    FILE *inputFile = fopen("input.txt", "r"); // файл на вход
    FILE *outputFile = fopen("output.txt", "w"); // файл на выход

    int lineIndex = 0; // индекс линий, сброс
    while (fgets(currentLine, BUF_SIZE, inputFile)) { // считываем исходный файл по линиям

        int isDuplicate = 0; // флаг найденного дубликата линии
        FILE *inputFile2 = fopen("input.txt", "r");  // открываем его на чтение еще раз
        for (int previousLineIndex = 0; previousLineIndex < lineIndex; previousLineIndex++) { // проходим цикл линий
            fgets(previousLine, BUF_SIZE, inputFile2); // достаём линию
            if (compareLines(currentLine, previousLine) == 0) { // сравниваем с предыдущей
                isDuplicate = 1; // если они равны, маркируем это во флаг
                break;
            }
        }
        fclose(inputFile2); // закрываем файл
        lineIndex++; // переходим к следующей линии

        if (isDuplicate) continue; // если нашли дубликат, переходим к поиску следующего

        fputs(currentLine, outputFile); // складываем уникальную линию в выходной файл
    }

    fclose(inputFile); // закрываем входной файл
    fclose(outputFile); // закрываем выходной файл
    return 0;
}