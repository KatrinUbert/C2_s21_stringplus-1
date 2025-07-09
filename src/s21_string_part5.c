#include <stdlib.h>

#include "s21_string.h"

// 5.1
void *s21_to_upper(const char *string) {
  if (!string) return s21_NULL;
  char *res_str = (char *)malloc(sizeof(char) * (s21_strlen(string) + 1));
  if (!res_str) return s21_NULL;
  char *res = res_str;
  for (; *string; string++, res_str++) {
    if (*string > 96 && *string < 123)
      *res_str = *string - 32;
    else
      *res_str = *string;
  }
  *res_str = '\0';
  return res;
}

// 5.2
void *s21_to_lower(const char *string) {
  if (!string) return s21_NULL;
  char *res_str = (char *)malloc(sizeof(char) * (s21_strlen(string) + 1));
  if (!res_str) return s21_NULL;
  char *res = res_str;
  for (; *string; string++, res_str++) {
    if (*string > 64 && *string < 91)
      *res_str = *string + 32;
    else
      *res_str = *string;
  }
  *res_str = '\0';
  return res;
}

// 5.3
void *s21_insert(const char *src_string, const char *string,
                 s21_size_t start_index) {
  if (start_index > s21_strlen(src_string)) return s21_NULL;
  char *res_str = (char *)malloc(
      sizeof(char) * (s21_strlen(src_string) + s21_strlen(string) + 1));
  if (!res_str) return s21_NULL;
  char *res = res_str;

  for (s21_size_t i = 0; i < start_index && *src_string;
       i++, src_string++, res_str++) {
    *res_str = *src_string;
  }

  for (; *string; string++, res_str++) {
    *res_str = *string;
  }

  for (; *src_string; src_string++, res_str++) {
    *res_str = *src_string;
  }

  *res_str = '\0';

  return res;
}

/*void *s21_insert(const char *src_string, const char *string,
                 s21_size_t start_index) {
  s21_size_t src_str_len = (!src_string) ? 0 : s21_strlen(src_string);
  s21_size_t ins_str_len = (!string) ? 0 : s21_strlen(string);
  if (start_index > src_str_len) return s21_NULL;
  char *res_str =
      (char *)malloc(sizeof(char) * (src_str_len + ins_str_len + 1));
  if (!res_str) return s21_NULL;
  char *res = res_str;

  for (s21_size_t i = 0; i <= src_str_len; i++, res_str++) {
    if (i == start_index) {
      if (string) {
        for (; *string; string++, res_str++) {
          *res_str = *string;
        }
      }
      if (src_string) *res_str = src_string[i];
    } else {
      if (src_string) *res_str = src_string[i];
    }
  }
  res[src_str_len + ins_str_len] = '\0';
  return res;
}*/

// 5.4
void *s21_trim(const char *src_string, const char *trim_chars) {
  if (!src_string) return s21_NULL;
  s21_size_t start_ind = 0, end_ind = 0;
  for (s21_size_t i = 0, flag = 1; i < s21_strlen(src_string) && flag; i++) {
    flag = 0;
    for (s21_size_t j = 0; j < s21_strlen(trim_chars); j++) {
      if (src_string[i] == trim_chars[j]) flag = 1;
    }
    if (!flag) start_ind = i;
  }
  for (s21_size_t i = s21_strlen(src_string) - 1, flag = 1;
       i >= start_ind && flag; i--) {
    flag = 0;
    for (s21_size_t j = 0; j < s21_strlen(trim_chars); j++) {
      if (src_string[i] == trim_chars[j]) flag = 1;
    }
    if (!flag) end_ind = i;
  }
  s21_size_t res_len = end_ind - start_ind + 1;
  char *res_str = (char *)malloc(sizeof(char) * (res_len + 1));
  for (s21_size_t i = 0; i <= res_len; i++) {
    res_str[i] = src_string[start_ind + i];
  }
  res_str[res_len] = '\0';
  return res_str;
}