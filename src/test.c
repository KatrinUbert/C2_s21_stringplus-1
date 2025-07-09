#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

int s21_strcmp(const char *string1, const char *string2) {
  if (!string1 && !string2) return 0;
  if (string1 && !string2) return 1;
  if (!string1 && string2) return -1;
  for (; *string1 && *string1 == *string2; string1++, string2++) {
  };
  int res = *string1 - *string2;
  if (res > 0) return 1;
  if (res < 0) return -1;
  return 0;
}

// 1
START_TEST(test_memchr) {
  char *memchr_str[6] = {"hello!",       "",           "NULL",
                         "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char memchar_char = 't';

  for (int i = 0; i < 6; i++) {
    if (memchr_str[i]) {
      char *memchr_test =
          (char *)memchr(memchr_str[i], memchar_char, strlen(memchr_str[i]));
      char *s21memchar_test = (char *)s21_memchr(memchr_str[i], memchar_char,
                                                 strlen(memchr_str[i]));
      ck_assert_int_eq(s21_strcmp(memchr_test, s21memchar_test), 0);
    }
  }
}
END_TEST

// 2
START_TEST(test_memcmp) {
  char *memcmp_str[6] = {"hello!",       "",           "NULL",
                         "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char *memcmp_str1[6] = {"hello!hello!", "",      "Nu",
                          "QWERT",        "12340", "@qwerty1"};

  for (int i = 0; i < 6; i++) {
    if (memcmp_str[i] && memcmp_str1[i]) {
      int memcmp_test =
          memcmp(memcmp_str[i], memcmp_str1[i], s21_strlen(memcmp_str1[i]));
      int s21_memcmp_test =
          s21_memcmp(memcmp_str[i], memcmp_str1[i], s21_strlen(memcmp_str1[i]));
      ck_assert_int_eq(memcmp_test, s21_memcmp_test);
    }
  }
}
END_TEST

// 3
START_TEST(test_memcpy) {
  char memcpy_str[6][100] = {"hello!",     "",
                             "NULL",       "QWERTYqwerty",
                             "1234567890", "@qwerty111_!#$^&*()"};
  char s21memcpy_str[6][100] = {"hello!",     "",
                                "NULL",       "QWERTYqwerty",
                                "1234567890", "@qwerty111_!#$^&*()"};
  char *memcpy_str1[6] = {"123", "123", "123", "123", "123", "@123!#$^&*()"};

  for (int i = 0; i < 6; i++) {
    char *memcpy_test =
        (char *)memcpy(memcpy_str[i], memcpy_str1[i], strlen(memcpy_str1[i]));
    char *s21memcpy_test = (char *)s21_memcpy(s21memcpy_str[i], memcpy_str1[i],
                                              strlen(memcpy_str1[i]));
    ck_assert_int_eq(s21_strcmp(memcpy_test, s21memcpy_test), 0);
  }
}
END_TEST

// 4
START_TEST(test_memset) {
  char memset_str[6][100] = {"hello!",     "",
                             "NULL",       "QWERTYqwerty",
                             "1234567890", "@qwerty111_!#$^&*()"};
  char s21memset_str[6][100] = {"hello!",     "",
                                "NULL",       "QWERTYqwerty",
                                "1234567890", "@qwerty111_!#$^&*()"};
  char memset_char = 't';

  for (int i = 0; i < 6; i++) {
    char *memset_test = (char *)memset(memset_str[i], memset_char, 2);
    char *s21memset_test = (char *)s21_memset(s21memset_str[i], memset_char, 2);
    ck_assert_int_eq(s21_strcmp(memset_test, s21memset_test), 0);
  }
}
END_TEST

// 5
START_TEST(test_strncat) {
  char strncat_str[6][100] = {"hello!",     "",
                              "NULL",       "QWERTYqwerty",
                              "1234567890", "@qwerty111_!#$^&*()"};
  char s21strncat_str[6][100] = {"hello!",     "",
                                 "NULL",       "QWERTYqwerty",
                                 "1234567890", "@qwerty111_!#$^&*()"};
  char *strncat_str1[6] = {"123", "123", "123", "", "\t123", "@123!#$^&*()"};

  for (int i = 0; i < 6; i++) {
    char *strncat_test =
        strncat(strncat_str[i], strncat_str1[i], s21_strlen(strncat_str1[i]));
    char *s21strncat_test = s21_strncat(s21strncat_str[i], strncat_str1[i],
                                        s21_strlen(strncat_str1[i]));
    ck_assert_int_eq(s21_strcmp(strncat_test, s21strncat_test), 0);
  }
}
END_TEST

// 6
START_TEST(test_strchr) {
  char *strchr_str[6] = {"hello!",       "",           "NULL",
                         "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char strchr_char = 't';

  for (int i = 0; i < 6; i++) {
    if (strchr_str[i]) {
      char *strchr_test = strchr(strchr_str[i], strchr_char);
      char *s21strchr_test = s21_strchr(strchr_str[i], strchr_char);
      ck_assert_int_eq(s21_strcmp(strchr_test, s21strchr_test), 0);
    }
  }
}
END_TEST

// 7
START_TEST(test_strncmp) {
  char *strncmp_str[6] = {"hello!",       "",           "NULL",
                          "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char *strncmp_str1[6] = {"hel", "", "Nu", "QWERT", "12340", "@qwerty1"};

  for (int i = 0; i < 6; i++) {
    if (strncmp_str[i] && strncmp_str1[i]) {
      int strncmp_test =
          strncmp(strncmp_str[i], strncmp_str1[i], s21_strlen(strncmp_str1[i]));
      int s21strncmp_test = s21_strncmp(strncmp_str[i], strncmp_str1[i],
                                        s21_strlen(strncmp_str1[i]));
      ck_assert_int_eq(strncmp_test, s21strncmp_test);
    }
  }
}
END_TEST

// 8
START_TEST(test_strncpy) {
  char strncpy_str[6][100] = {"hello!",     "",
                              "NULL",       "QWERTYqwerty",
                              "1234567890", "@qwerty111_!#$^&*()"};
  char s21strncpy_str[6][100] = {"hello!",     "",
                                 "NULL",       "QWERTYqwerty",
                                 "1234567890", "@qwerty111_!#$^&*()"};
  char *strncpy_str1[6] = {"hel", "", "Nu", "QWERT", "12340", "@qwerty1"};

  for (int i = 0; i < 6; i++) {
    char *strncpy_test =
        strncpy(strncpy_str[i], strncpy_str1[i], s21_strlen(strncpy_str1[i]));
    char *s21strncpy_test = s21_strncpy(s21strncpy_str[i], strncpy_str1[i],
                                        s21_strlen(strncpy_str1[i]));
    ck_assert_int_eq(s21_strcmp(strncpy_test, s21strncpy_test), 0);
  }
}
END_TEST

// 9
START_TEST(test_strcspn) {
  char *strcspn_str[6] = {"hello!",       "",           "NULL",
                          "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char *strcspn_str1[6] = {"qwerty", "qwerty", "qwerty",
                           "qwerty", "0987",   "123"};

  for (int i = 0; i < 6; i++) {
    if (strcspn_str[i] && strcspn_str1[i]) {
      size_t strcspn_test = strcspn(strcspn_str[i], strcspn_str1[i]);
      s21_size_t s21strcspn_test = s21_strcspn(strcspn_str[i], strcspn_str1[i]);
      ck_assert_int_eq(strcspn_test, s21strcspn_test);
    }
  }
}
END_TEST

// 11
START_TEST(test_strlen) {
  char *strlen_str[6] = {"hello!",       "",           "NULL",
                         "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};

  for (int i = 0; i < 6; i++) {
    if (strlen_str[i]) {
      size_t strlen_test = strlen(strlen_str[i]);
      s21_size_t s21strlen_test = s21_strlen(strlen_str[i]);
      ck_assert_int_eq(strlen_test, s21strlen_test);
    }
  }
}
END_TEST

// 12
START_TEST(test_strpbrk) {
  char *strpbrk_str[6] = {"hello!",       "",           "NULL",
                          "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char *strpbrk_str1[6] = {"qwerty", "qwerty", "qwerty",
                           "qwerty", "0987",   "123"};

  for (int i = 0; i < 6; i++) {
    if (strpbrk_str[i] && strpbrk_str1[i]) {
      char *strpbrk_test = strpbrk(strpbrk_str[i], strpbrk_str1[i]);
      char *s21strpbrk_test = s21_strpbrk(strpbrk_str[i], strpbrk_str1[i]);
      ck_assert_int_eq(s21_strcmp(strpbrk_test, s21strpbrk_test), 0);
    }
  }
}
END_TEST

// 13
START_TEST(test_strrchr) {
  char *strrchr_str[6] = {"hello!",       "",           "NULL",
                          "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char strrchr_char = 't';

  for (int i = 0; i < 6; i++) {
    if (strrchr_str[i]) {
      char *strrchr_test = strrchr(strrchr_str[i], strrchr_char);
      char *s21strrchr_test = s21_strrchr(strrchr_str[i], strrchr_char);
      ck_assert_int_eq(s21_strcmp(strrchr_test, s21strrchr_test), 0);
    }
  }
}
END_TEST

// 14
START_TEST(test_strstr) {
  char *strstr_str[6] = {"hello!",       "",           "NULL",
                         "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char *strstr_str1[6] = {"lo!", "qwerty", "qwerty", "qwerty", "678", "123"};

  for (int i = 0; i < 6; i++) {
    if (strstr_str[i] && strstr_str1[i]) {
      char *strstr_test = strstr(strstr_str[i], strstr_str1[i]);
      char *s21strstr_test = s21_strstr(strstr_str[i], strstr_str1[i]);
      ck_assert_int_eq(s21_strcmp(strstr_test, s21strstr_test), 0);
    }
  }
}
END_TEST

// 15
START_TEST(test_strtok) {
  char strtok_str[] = "qwerty asdfgh,. zxcvbn QWERTY .,,,,,-ASDF";
  char s21strtok_str[] = "qwerty asdfgh,. zxcvbn QWERTY .,,,,,-ASDF";
  char *strtok_l = strtok(strtok_str, " ,.-");
  char *s21strtok_l = s21_strtok(s21strtok_str, " ,.-");
  int i = 0;
  while (strtok_l || s21strtok_l) {
    if (!strtok_l && s21strtok_l)
      ck_assert_int_eq(0, 1);
    else if (strtok_l && !s21strtok_l)
      ck_assert_int_eq(1, 0);
    else {
      ck_assert_int_eq(s21_strcmp(strtok_l, s21strtok_l), 0);
    }
    i++;
    strtok_l = strtok(s21_NULL, " ,.-");
    s21strtok_l = s21_strtok(s21_NULL, " ,.-");
  }
}
END_TEST

START_TEST(test_upper) {
  char *str_to_up[6] = {"hello!",       "",           "NULL",
                        "QWERTYqwerty", "1234567890", "@qwerty111_!#$^&*()"};
  char *str_to_up_check[6] = {"HELLO!",     "",
                              "NULL",       "QWERTYQWERTY",
                              "1234567890", "@QWERTY111_!#$^&*()"};
  for (int i = 0; i < 6; i++) {
    char *res_to_up = (char *)s21_to_upper(str_to_up[i]);
    ck_assert_int_eq(s21_strcmp(res_to_up, str_to_up_check[i]), 0);
    free(res_to_up);
  }
}
END_TEST

START_TEST(test_lower) {
  char *str_to_low[6] = {"helLo!",       "",           "NULL",
                         "QWERTYqwerty", "1234567890", "@qwERTy111_!#$^&*()"};
  char *str_to_low_check[6] = {"hello!",     "",
                               "null",       "qwertyqwerty",
                               "1234567890", "@qwerty111_!#$^&*()"};

  for (int i = 0; i < 6; i++) {
    char *res_to_low = (char *)s21_to_lower(str_to_low[i]);
    ck_assert_int_eq(s21_strcmp(res_to_low, str_to_low_check[i]), 0);
    free(res_to_low);
  }
}
END_TEST

START_TEST(test_insert) {
  char str_orig[] = "insert into a text";
  char str_ins[] = "a string ";
  char str_check[] = "insert a string into a text";

  char *res = (char *)s21_insert(str_orig, str_ins, 7);
  ck_assert_int_eq(s21_strcmp(res, str_check), 0);
  free(res);
}
END_TEST

START_TEST(test_trim) {
  char *str_to_trim[6] = {" ---hello!--- ",   "",
                          "123456NULL123456", "@@@#$QWERTYqwerty123",
                          "1234567890",       ".@qwERTy111_!#$^&*()."};
  char *str_trim_set[6] = {" -",        "",           "1234567890",
                           "1234@@@#$", "1234567890", "@qwerty111_!#$^&*()"};
  char *str_check[6] = {"hello!",       "", "NULL",
                        "QWERTYqwerty", "", ".@qwERTy111_!#$^&*()."};

  for (int i = 0; i < 6; i++) {
    char *res = (char *)s21_trim(str_to_trim[i], str_trim_set[i]);
    ck_assert_int_eq(s21_strcmp(res, str_check[i]), 0);
    free(res);
  }
}
END_TEST

Suite *string_test_suite_create(void) {
  Suite *suite = suite_create("Strings");
  TCase *tcase_memchr, *tcase_memcmp, *tcase_memcpy, *tcase_memset,
      *tcase_strncat, *tcase_strchr, *tcase_strncmp, *tcase_strncpy,
      *tcase_strcspn, *tcase_strlen, *tcase_strpbrk, *tcase_strrchr,
      *tcase_strstr, *tcase_strtok, *tcase_upper, *tcase_lower, *tcase_insert,
      *tcase_trim;

  tcase_memchr = tcase_create("tcase_memchr");
  tcase_add_test(tcase_memchr, test_memchr);
  suite_add_tcase(suite, tcase_memchr);

  tcase_memcmp = tcase_create("tcase_memcmp");
  tcase_add_test(tcase_memcmp, test_memcmp);
  suite_add_tcase(suite, tcase_memcmp);

  tcase_memcpy = tcase_create("tcase_memcpy");
  tcase_add_test(tcase_memcpy, test_memcpy);
  suite_add_tcase(suite, tcase_memcpy);

  tcase_memset = tcase_create("tcase_memset");
  tcase_add_test(tcase_memset, test_memset);
  suite_add_tcase(suite, tcase_memset);

  tcase_strncat = tcase_create("tcase_strncat");
  tcase_add_test(tcase_strncat, test_strncat);
  suite_add_tcase(suite, tcase_strncat);

  tcase_strchr = tcase_create("tcase_strchr");
  tcase_add_test(tcase_strchr, test_strchr);
  suite_add_tcase(suite, tcase_strchr);

  tcase_strncmp = tcase_create("tcase_strncmp");
  tcase_add_test(tcase_strncmp, test_strncmp);
  suite_add_tcase(suite, tcase_strncmp);

  tcase_strncpy = tcase_create("tcase_strncpy");
  tcase_add_test(tcase_strncpy, test_strncpy);
  suite_add_tcase(suite, tcase_strncpy);

  tcase_strcspn = tcase_create("tcase_strcspn");
  tcase_add_test(tcase_strcspn, test_strcspn);
  suite_add_tcase(suite, tcase_strcspn);

  tcase_strlen = tcase_create("tcase_strlen");
  tcase_add_test(tcase_strlen, test_strlen);
  suite_add_tcase(suite, tcase_strlen);

  tcase_strpbrk = tcase_create("tcase_strpbrk");
  tcase_add_test(tcase_strpbrk, test_strpbrk);
  suite_add_tcase(suite, tcase_strpbrk);

  tcase_strrchr = tcase_create("tcase_strrchr");
  tcase_add_test(tcase_strrchr, test_strrchr);
  suite_add_tcase(suite, tcase_strrchr);

  tcase_strstr = tcase_create("tcase_strstr");
  tcase_add_test(tcase_strstr, test_strstr);
  suite_add_tcase(suite, tcase_strstr);

  tcase_strtok = tcase_create("tcase_strtok");
  tcase_add_test(tcase_strtok, test_strtok);
  suite_add_tcase(suite, tcase_strtok);

  tcase_upper = tcase_create("tcase_upper");
  tcase_add_test(tcase_upper, test_upper);
  suite_add_tcase(suite, tcase_upper);

  tcase_lower = tcase_create("tcase_lower");
  tcase_add_test(tcase_lower, test_lower);
  suite_add_tcase(suite, tcase_lower);

  tcase_insert = tcase_create("tcase_insert");
  tcase_add_test(tcase_insert, test_insert);
  suite_add_tcase(suite, tcase_insert);

  tcase_trim = tcase_create("tcase_trim");
  tcase_add_test(tcase_trim, test_trim);
  suite_add_tcase(suite, tcase_trim);

  return suite;
}

int main() {
  Suite *suite = string_test_suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
