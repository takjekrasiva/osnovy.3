#pragma warning(disable : 4996) // для использования устаревших функций (scanf)
#include <stdio.h>

/*объявление символических констант*/

#define YES 1
#define NO 0
#define MAXLINE 1024 // максимальная длина массива

int main(void)
{
    /*объявление и инициализация*/

    char original[MAXLINE];    // исходная строка
    char result[MAXLINE];      // результат
    char c;                    // текущий символ
    int word = NO;             // наличие слова
    int symb = NO;             // наличие лишнего символа
    int letter_count = 0;      // счетчик
    int max_length = 0;        // количество букв в самом длинном слове
    char *in_ptr = original;   // указатель на текущий символ входной строки
    char *out_ptr = result;    // указатель на текущий символ выходной строки
    char *word_ptr = original; // указатель на начало слова

    gets(original);

    do
    {
        c = *in_ptr; // загрузка текущего символа
        if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\0' || c == '?' || c == '!' || c == ';' || c == ':' ||
            c == '-' || c == '_' || c == '(' || c == ')' || c == '\t' || c == '/' || c == '&' || c == '"') // разделитель найден
        {
            if (letter_count > max_length && symb == NO)
            {
                max_length = letter_count;
            }
            word = NO;
            symb = NO; // нет лишнего символа
            letter_count = 0; // обнуляется, новое слово
        }
        else
        {
            letter_count++;
            if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // проверить не является ли этот символ лишним
            {
                symb = YES; // в слове есть лишний символ
            }
          
            word = YES;
        }
        in_ptr++;
    } while (c != '\0'); // все слова проверены

    in_ptr = original;

    do
    {
        c = *in_ptr; // загрузка текущего символа из буфера
        if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\0' || c == '?' || c == '!' || c == ';' || c == ':' ||
            c == '-' || c == '_' || c == '(' || c == ')' || c == '\t' || c == '/' || c == '&' || c == '"') // разделитель найден
        {
            if (word == YES && symb == NO && letter_count != max_length || symb == YES)
            {
                while (word_ptr < in_ptr) 
                {
                    *out_ptr++ = *word_ptr++; // копирование слова, запись слова
                }
            }
            else // символы=макс
            {
                while (word_ptr < in_ptr)
                {
                    word_ptr++;
                }
            }
            word = NO;
            symb = NO;
            letter_count = 0;
            *out_ptr++ = c;
        }
        else
        {
            letter_count++; // пропуск макс слова
            if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // проверка, яляется ли этот символ лишним
            {
                symb = YES; // в слове есть лишний символ
            }
            if (word == NO) // найдена первая буква слова
            {
                word_ptr = in_ptr; // запомнить адрес начала слова
            }
            word = YES;
        }
        in_ptr++;
    } while (c != '\0');
    puts(result);
    return 0;
}
