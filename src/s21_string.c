#include "s21_string.h"

// 1
void *s21_memchr(const void *string, int symbol, s21_size_t n) {
  void *res = (void *)string;
  int flag = 1;
  for (s21_size_t i = 0; i < n && *((unsigned char *)res) && flag; i++) {
    if (*((unsigned char *)res) == symbol)
      flag = 0;
    else
      res++;
  }
  if (flag) res = s21_NULL;
  return res;
}

// 2
int s21_memcmp(const void *string1, const void *string2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0, flag = 1; i < n && flag; i++) {
    if ((((unsigned char *)string1)[i]) != (((unsigned char *)string2)[i])) {
      res = ((unsigned char *)string1)[i] - ((unsigned char *)string2)[i];
      flag = 0;
    }
  }
  return res;
}

// 3
void *s21_memcpy(void *dest_string, const void *src_string, s21_size_t n) {
  void *res = (void *)dest_string;
  for (s21_size_t i = 0; i < n && ((unsigned char *)src_string)[i]; i++) {
    ((unsigned char *)dest_string)[i] = ((unsigned char *)src_string)[i];
  }
  return res;
}

// 4
void *s21_memset(void *string, int symbol, s21_size_t n) {
  void *res = (void *)string;
  for (s21_size_t i = 0; i < n; i++) {
    ((unsigned char *)string)[i] = symbol;
  }
  return res;
}

// 5
char *s21_strncat(char *dest_string, const char *src_string, s21_size_t n) {
  if (!dest_string) return s21_NULL;
  if (!src_string || n == 0) return dest_string;
  char *res = dest_string;
  dest_string += s21_strlen(dest_string);
  for (s21_size_t i = 0; i < n && *src_string;
       i++, dest_string++, src_string++) {
    *dest_string = *src_string;
  }
  dest_string++;
  *dest_string = '\0';
  return res;
}

// 6
char *s21_strchr(const char *string, int symbol) {
  if (!string) return s21_NULL;
  char *res = (char *)string;
  int flag = 1;
  for (; *res && flag;) {
    if (*res == symbol)
      flag = 0;
    else
      res++;
  }
  if (flag) res = s21_NULL;
  return res;
}

// 7
int s21_strncmp(const char *string1, const char *string2, s21_size_t n) {
  if (!string1) return -1;
  if (!string2) return 1;
  int res = 0, flag = 1;
  for (s21_size_t i = 0; i < n && flag && string1[i] && string2[i]; i++) {
    if (string1[i] != string2[i]) {
      flag = 0;
      res = string1[i] - string2[i];
    }
  }
  return res;
}

// 8
char *s21_strncpy(char *dest_string, const char *src_string, s21_size_t n) {
  if (!dest_string) return s21_NULL;
  if (!src_string) return dest_string;
  char *res = dest_string;
  for (s21_size_t i = 0; i < n && *src_string;
       i++, dest_string++, src_string++) {
    *dest_string = *src_string;
  }
  return res;
}

// 9
s21_size_t s21_strcspn(const char *string1, const char *string2) {
  if (!string1) return 0;
  if (!string2) return s21_strlen(string1);
  s21_size_t res = 0;
  for (int flag = 1; res < s21_strlen(string1) && flag;) {
    for (s21_size_t i = 0; i < s21_strlen(string2); i++) {
      if (string1[res] == string2[i]) flag = 0;
    }
    if (flag) res++;
  }
  return res;
}

// 10

// 11
s21_size_t s21_strlen(const char *string) {
  int len = 0;
  if (string) {
    for (; *(string + len); len++) {
    };
  }
  return len;
}

// 12
char *s21_strpbrk(const char *string1, const char *string2) {
  if (!string1 || !string2) return s21_NULL;
  int flag = 1;
  char *res = (char *)string1;
  for (; *res && flag;) {
    char *temp = (char *)string2;
    for (; *temp; temp++) {
      if (*res == *temp) flag = 0;
    }
    if (flag) res++;
  }
  if (flag) res = s21_NULL;
  return res;
}

// 13
char *s21_strrchr(const char *string, int symbol) {
  if (!string) return s21_NULL;
  char *res = (char *)string;
  res = res + s21_strlen(string);
  int flag = 1;
  for (int i = s21_strlen(string); i >= 0 && flag; i--) {
    if (*res == symbol)
      flag = 0;
    else
      res--;
  }
  if (flag) res = s21_NULL;
  return res;
}

// 14
char *s21_strstr(const char *string1, const char *string2) {
  if (!string1 || !string2) return s21_NULL;
  char *res = (char *)string1;
  int flag = 1;
  while (*res && flag) {
    int match = 1;
    char *cmp = (char *)string2;
    char *temp = res;
    if (*temp == *cmp) {
      while (*temp && *cmp && match) {
        if (*temp != *cmp) match = 0;
        temp++;
        cmp++;
      }
      if (match) flag = 0;
    }
    if (flag) res++;
  }
  if (flag) res = s21_NULL;
  return res;
}

// 15
char *s21_strtok(char *string, const char *delimiter) {
  static char *s21_SAVE_PTR = s21_NULL;
  if (!string) string = s21_SAVE_PTR;
  if (!delimiter) return string;
  char *res_string = string;
  s21_size_t pos = 0, len = s21_strlen(string);
  for (int flag = 1; pos < len && flag; pos++) {
    for (s21_size_t j = 0; j < s21_strlen(delimiter); j++) {
      if ((string[pos] == delimiter[j])) {
        flag = 0;
        string[pos] = '\0';
      }
    }
  }
  int flag = 1;
  if (pos == len) {
    s21_SAVE_PTR = s21_NULL;
    flag = 0;  // return res_string;}
  } else {
    for (; pos < len && flag; pos++) {
      flag = 0;
      for (s21_size_t j = 0; j < s21_strlen(delimiter); j++) {
        if ((string[pos] == delimiter[j])) {
          flag = 1;
          string[pos] = '\0';
        }
      }
      if (!flag) s21_SAVE_PTR = string + pos;
    }
  }
  if (flag) res_string = s21_NULL;
  return res_string;
}
