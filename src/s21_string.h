#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

/*
%[флаги][ширина][.точность][длина]спецификатор
Спецификаторы: c, d, f, s, u, %
1	c	Символ
2	d	Знаковое десятичное целое число
3	f	Десятичное число с плавающей точкой
4	s	Строка символов
5	u	Беззнаковое десятичное целое число
6	%	Символ %

Флаги: -, +, (пробел)
1	-	    Выравнивание по левому краю в пределах заданной ширины поля.
Выравнивание по правому краю используется по умолчанию (см. подспецификатор
ширины).
2	+	    Заставляет явно указывать знак плюс или минус (+ или
-) даже для положительных чисел. По умолчанию только отрицательным числам
предшествует знак «-».
3	(пробел) Если знак не будет выведен, перед
значением вставляется пробел.

Ширина: (число)
1   (число) Минимальное количество печатаемых символов. Если выводимое значение
короче этого числа, результат дополняется пробелами. Значение не усекается, даже
если результат больше.

Точность: .(число)
1   .число  Для целочисленных спецификаторов (d, i, o, u, x, X) — точность
определяет минимальное количество записываемых цифр. Если записываемое значение
короче этого числа, результат дополняется ведущими нулями. Значение не
усекается, даже если результат длиннее. Точность 0 означает, что для значения 0
не записывается ни одного символа. Для спецификаторов e, E и f — это количество
цифр, которые должны быть напечатаны после десятичной точки. Для спецификаторов
g и G — это максимальное количество значащих цифр, которые должны быть
напечатаны. Для s — это максимальное количество печатаемых символов. По
умолчанию все символы печатаются до тех пор, пока не встретится терминирующий
нуль. Для типа с — никак не влияет. Если точность не указана для спецификаторов
e, E, f, g и G, то по умолчанию ее значение равно 6. Если точность не указана
для остальных спецификаторов, то по умолчанию ее значение равно 1. Если число не
указано (нет явного значения точности), то по умолчанию — 0.

Длина: h, l
1   h   Аргумент интерпретируется как короткое int или короткое int без знака
        (применяется только к целочисленным спецификаторам: i, d, o, u, x и X).
2   l   Аргумент интерпретируется как длинное int или длинное int без знака для
целочисленных спецификаторов (i, d, o, u, x и X) и как широкий символ или строка
широких символов для спецификаторов c и s.
*/
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// int spec c = 1, d = 2, f = 3, s = 4, u = 5
struct s21_format_node {
  int flag_minus;
  int flag_plus;
  int flag_space;

  int flag_width;
  s21_size_t width;
  int flag_accuracy;
  s21_size_t accuracy;

  int len_h;
  int len_l;

  int spec;
};

/*Обнаружили строку формата, обработали строку формата, вернули структуру
 * формата*/
int s21_parsing_format(const char *string, s21_size_t *start_pos,
                       struct s21_format_node *dest_format);
void s21_prep_format_node(struct s21_format_node *format);
int s21_find_format_errors(struct s21_format_node *dest_format);
s21_size_t s21_parse_str_to_int(const char *string, s21_size_t *start_position,
                                s21_size_t *result);

/*Берем структуру формата, аргумент, творим магию, возвращаем (или не
 * возвращаем) форматированную строку*/
char *s21_formatted_char(struct s21_format_node dest_format,
                         va_list started_factor);
char *s21_formatted_int(struct s21_format_node dest_format,
                        va_list started_factor);
char *s21_formatted_float(struct s21_format_node dest_format,
                          va_list started_factor);
char *s21_formatted_str(struct s21_format_node dest_format, const char *str,
                        s21_size_t len);
char *s21_formatted_unsing_int(struct s21_format_node dest_format,
                               va_list started_factor);

/*Возвращает новую строку с учетом точности и знака у чисел*/
char *s21_accur_int_format(struct s21_format_node dest_format,
                           const char *base_str, int negative);
/*Возвращает новую строку подогнанную под ширину*/
char *s21_width_format(struct s21_format_node dest_format,
                       const char *base_str);

/*Переводит ПОЛОЖИТЕЛЬНОЕ ЦЕЛОЕ число в строку*/
char *s21_int_to_str(s21_size_t num);
/*Переводит ПОЛОЖИТЕЛЬНОЕ ДРОБНОЕ число в строку*/
char *s21_float_to_str(double num, s21_size_t accuracy);
/*Переводит строку в ПОЛОЖИТЕЛЬНОЕ ЦЕЛОЕ*/
s21_size_t s21_str_to_int(const char *num_str);
/*Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов, входящих в str2.*/
s21_size_t s21_str_found_len(const char *string1, const char *string2);
/*Возращает новую строку нужной длины заполненой указанным символом*/
char *s21_new_str_char(char symbol, s21_size_t len);

#endif  // S21_SPRINTF_H