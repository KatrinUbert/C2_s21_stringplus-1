#include "s21_strerror.h"

START_TEST(test_strerror) {
  FILE *f = fopen("1.txt", "r");
  if (f == NULL) {
    char *res_orig = strerror(errno);
    char *res = s21_strerror(errno);
    ck_assert_int_eq(*res_orig, *res);
  }
}
END_TEST

Suite *string_test_suite_create(void) {
  Suite *suite = suite_create("Strings");
  TCase *tcase_memchr, *tcase_memcmp, *tcase_memcpy, *tcase_memset,
      *tcase_strncat, *tcase_strchr, *tcase_strncmp, *tcase_strncpy,
      *tcase_strcspn, *tcase_strerror, *tcase_strlen, *tcase_strpbrk,
      *tcase_strrchr, *tcase_strstr, *tcase_strtok, *tcase_upper, *tcase_lower,
      *tcase_insert, *tcase_trim;

  tcase_strerror = tcase_create("tcase_strerror");
  tcase_add_test(tcase_strerror, test_strerror);
  suite_add_tcase(suite, tcase_strerror);
}
