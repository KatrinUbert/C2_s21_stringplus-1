#include <check.h>
#include <stdio.h>

#include "s21_sprintf.h"

START_TEST(test_s21_sprintf_f) {
  char buffer[100];
  double number;

  number = 123.456;
  int result = s21_sprintf(buffer, "%+f", number);
  ck_assert_str_eq(buffer, "+123.456000");

  number = -123.456;
  result = s21_sprintf(buffer, "%+f", number);
  ck_assert_str_eq(buffer, "-123.456000");

  number = 0.0;
  result = s21_sprintf(buffer, "%+f", number);
  ck_assert_str_eq(buffer, "+0.000000");

  number = 123.456789;
  result = s21_sprintf(buffer, "%+.2f", number);
  ck_assert_str_eq(buffer, "+123.46");

  number = -123.456789;
  result = s21_sprintf(buffer, "%+.2f", number);
  ck_assert_str_eq(buffer, "-123.46");

  number = 0.0;
  result = s21_sprintf(buffer, "%+.2f", number);
  ck_assert_str_eq(buffer, "+0.00");

  result = s21_sprintf(buffer, "% f", number);
  ck_assert_str_eq(buffer, " 0.00");

  number = 13.092002;
  result = s21_sprintf(buffer, "%10.2f", number);
  ck_assert_str_eq(buffer, "     13.09");

  result = s21_sprinf(buffer, "%-10.2f", number);
  ck_assert_str_eq(buffer, "13.09     ");

  result = s21_sprintf(buffer, "%010.2f", number);
  ck_assert_str_eq(buffer, "0000013.09");

  number = 0.000001;
  int result = s21_sprintf(buffer, "%+f", number);
  ck_assert_str_eq(buffer, "+0.000001");
}
END_TEST

Suite *string_test_suite_create(void) {
  Suite *suite = suite_create("Strings");
  TCase *tcase_memchr, *tcase_memcmp, *tcase_memcpy, *tcase_memset,
      *tcase_strncat, *tcase_strchr, *tcase_strncmp, *tcase_strncpy,
      *tcase_strcspn, *tcase_strerror, *tcase_strlen, *tcase_strpbrk,
      *tcase_strrchr, *tcase_strstr, *tcase_strtok, *tcase_s21_sprintf_f,
      *tcase_upper, *tcase_lower, *tcase_insert, *tcase_trim;

  tcase_s21_sprintf_f = tcase_create("tcase_s21_sprintf_f");
  tcase_add_test(tcase_s21_sprintf_f, test_s21_sprintf_f);
  suite_add_tcase(suite, tcase_s21_sprintf_f);
}