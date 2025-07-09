#include "s21_sprintf.h"

#include "s21_string.h"

#define CON_NUMBERS "0123456789"

int s21_sprintf(char *string, const char *format, ...) {
  char *str_start = string;
  va_list factor;
  va_start(factor, format);
  s21_size_t position = 0, res = 1;
  while (format[position] && res) {
    if (format[position] == '%') {
      if (format[position + 1] == '%') {
        *string = format[position];
        string++;
        position = position + 2;
      } else {
        position++;
        struct s21_format_node temp;
        res = s21_parsing_format((char *)format, &position, &temp);
        char *temp_char = s21_NULL;
        if (res && temp.spec == 1) {
          temp_char = s21_formatted_char(temp, factor);
        }
        if (res && temp.spec == 2) {
          temp_char = s21_formatted_int(temp, factor);
        }
        if (res && temp.spec == 3) {
          temp_char = s21_formatted_float(temp, factor);
        }
        if (res && temp.spec == 4) {
          const char *arg_str = va_arg(factor, char *);
          if (!arg_str)
            res = 0;
          else
            temp_char = s21_formatted_str(temp, arg_str, s21_strlen(arg_str));
        }
        if (res && temp.spec == 5) {
          temp_char = s21_formatted_unsing_int(temp, factor);
        }
        if (temp_char) {
          for (int i = 0; temp_char[i]; i++) {
            *string = temp_char[i];
            string++;
          }
        } else
          res = 0;
        free(temp_char);
      }
    } else {
      *string = format[position];
      string++;
      position++;
    }
  }
  if (!res) string = str_start;
  *string = '\0';
  va_end(factor);
  return s21_strlen(str_start);
}

int s21_parsing_format(const char *string, s21_size_t *start_pos,
                       struct s21_format_node *dest_format) {
  if (!string) return 0;
  int res = 1, flags_read = 1, width_read = 1, accuracy_read = 1;
  s21_size_t string_len = s21_strlen(string), pos = *start_pos;
  s21_prep_format_node(dest_format);

  while (flags_read && pos < string_len) {
    if ((string[pos] == '-') || (string[pos] == '+') || (string[pos] == ' ')) {
      if (string[pos] == '-') dest_format->flag_minus = 1;
      if (string[pos] == '+') dest_format->flag_plus = 1;
      if (string[pos] == ' ') dest_format->flag_space = 1;
      pos++;
    } else
      flags_read = 0;
  }

  while (width_read && pos < string_len && res) {
    if (string[pos] > 47 && string[pos] < 58) {
      dest_format->flag_width = 1;
      if (!s21_parse_str_to_int(string, &pos, &(dest_format->width))) res = 0;
    }
    width_read = 0;
  }

  while (accuracy_read && pos < string_len && res) {
    if (string[pos] == '.') {
      pos++;
      if (string[pos] > 47 && string[pos] < 58) {
        dest_format->flag_accuracy = 1;
        if (!s21_parse_str_to_int(string, &pos, &(dest_format->accuracy)))
          res = 0;
      } else
        res = 0;
    }
    accuracy_read = 0;
  }

  if (string[pos] == 'l') {
    dest_format->len_l = 1;
    pos++;
  } else if (string[pos] == 'h') {
    dest_format->len_h = 1;
    pos++;
  }
  if (string[pos] == 'c') {
    dest_format->spec = 1;
  } else if (string[pos] == 'd') {
    dest_format->spec = 2;
  } else if (string[pos] == 'f') {
    dest_format->spec = 3;
  } else if (string[pos] == 's') {
    dest_format->spec = 4;
  } else if (string[pos] == 'u') {
    dest_format->spec = 5;
  } else
    res = 0;
  pos++;

  if (res) res = s21_find_format_errors(dest_format);
  if (res) *start_pos = pos;
  return res;
}

void s21_prep_format_node(struct s21_format_node *format) {
  format->flag_minus = 0;
  format->flag_plus = 0;
  format->flag_space = 0;
  format->flag_width = 0;
  format->width = 0;
  format->flag_accuracy = 0;
  format->accuracy = 0;
  format->len_h = 0;
  format->len_l = 0;
  format->spec = 0;
}

// int spec c = 1, d = 2, f = 3, s = 4, u = 5
int s21_find_format_errors(struct s21_format_node *dest_format) {
  int res = 1;
  if (dest_format->flag_plus && dest_format->flag_space) res = 0;
  if (dest_format->flag_plus && dest_format->spec == 1) res = 0;
  if (dest_format->flag_plus && dest_format->spec == 4) res = 0;
  if (dest_format->flag_plus && dest_format->spec == 5) res = 0;
  if (dest_format->flag_space && dest_format->spec == 1) res = 0;
  if (dest_format->flag_space && dest_format->spec == 4) res = 0;
  if (dest_format->flag_space && dest_format->spec == 5) res = 0;
  if (dest_format->flag_accuracy && dest_format->spec == 1) res = 0;
  if (dest_format->flag_accuracy == 0 && dest_format->spec == 2)
    dest_format->accuracy = 1;
  if (dest_format->flag_accuracy == 0 && dest_format->spec == 3)
    dest_format->accuracy = 6;
  if (dest_format->flag_accuracy == 0 && dest_format->spec == 5)
    dest_format->accuracy = 1;
  if (dest_format->len_h && dest_format->len_l) res = 0;
  if (dest_format->len_h && dest_format->spec == 1) res = 0;
  if (dest_format->len_h && dest_format->spec == 3) res = 0;
  if (dest_format->len_h && dest_format->spec == 4) res = 0;
  return res;
}

s21_size_t s21_parse_str_to_int(const char *string, s21_size_t *start_position,
                                s21_size_t *result) {
  if (!string || !result) return 0;
  int res = 1;
  s21_size_t position = *start_position,
             len_num = s21_str_found_len(string + *start_position, CON_NUMBERS);
  char *num_str = (char *)malloc(sizeof(char) * (len_num + 1));
  if (num_str) {
    while (string[position] > 47 && string[position] < 58) {
      num_str[position - *start_position] = string[position];
      position++;
    }
    num_str[len_num] = '\0';
    *result = s21_str_to_int(num_str);
    free(num_str);
  } else
    res = 0;
  if (res) *start_position = position;
  return res;
}

char *s21_formatted_char(struct s21_format_node dest_format,
                         va_list started_factor) {
  int arg_char = 0;
  arg_char = va_arg(started_factor, int);

  if (!arg_char) return s21_NULL;
  const char tranced_char[2] = {arg_char, '\0'};
  char *result = s21_width_format(dest_format, tranced_char);
  return result;
}

char *s21_formatted_int(struct s21_format_node dest_format,
                        va_list started_factor) {
  long int agr_num = 0;
  if (dest_format.len_l)
    agr_num = va_arg(started_factor, long int);
  else
    agr_num = (long)va_arg(started_factor, int);
  if (!agr_num) agr_num = 0;

  char *result = s21_NULL;
  if (agr_num == 0 && (dest_format.flag_plus || dest_format.flag_space)) {
    if (dest_format.flag_plus) result = s21_width_format(dest_format, "+");
    if (dest_format.flag_space) result = s21_width_format(dest_format, " ");
  } else {
    int negative = (agr_num >= 0) ? 0 : 1;
    if (negative) agr_num = -agr_num;
    char *tranced_int = s21_int_to_str(agr_num);
    if (tranced_int) {
      char *accur_form =
          s21_accur_int_format(dest_format, tranced_int, negative);
      if (accur_form) {
        result = s21_width_format(dest_format, accur_form);
        free(accur_form);
      }
      free(tranced_int);
    }
  }
  return result;
}

char *s21_formatted_float(struct s21_format_node dest_format,
                          va_list started_factor) {
  double agr_num = 0.0;
  agr_num = va_arg(started_factor, double);
  if (agr_num == 0) agr_num = 0.0;
  int negative = (agr_num >= 0) ? 0 : 1;
  if (negative) agr_num = -agr_num;

  char *tranced_float = s21_float_to_str(agr_num, dest_format.accuracy);
  if (negative) {
    char *temp = s21_insert(tranced_float, "-", 0);
    if (temp) {
      free(tranced_float);
      tranced_float = temp;
    }
  }
  if (!negative && dest_format.flag_plus) {
    char *temp = s21_insert(tranced_float, "+", 0);
    if (temp) {
      free(tranced_float);
      tranced_float = temp;
    }
  }
  if (!negative && dest_format.flag_space) {
    char *temp = s21_insert(tranced_float, " ", 0);
    if (temp) {
      free(tranced_float);
      tranced_float = temp;
    }
  }

  char *result = s21_NULL;
  if (tranced_float) {
    result = s21_width_format(dest_format, tranced_float);
    free(tranced_float);
  }
  return result;
}

char *s21_formatted_str(struct s21_format_node dest_format, const char *str,
                        s21_size_t len) {
  if (!str) return s21_NULL;
  s21_size_t full_len =
      (dest_format.flag_accuracy && dest_format.accuracy < len)
          ? dest_format.accuracy
          : len;
  char *temp = s21_new_str_char(' ', full_len), *result = s21_NULL;
  if (temp) {
    temp = s21_strncpy(temp, str, full_len);
    result = s21_width_format(dest_format, temp);
    free(temp);
  }
  return result;
}

char *s21_formatted_unsing_int(struct s21_format_node dest_format,
                               va_list started_factor) {
  s21_size_t agr_num = 0;
  if (dest_format.len_l)
    agr_num = va_arg(started_factor, s21_size_t);
  else
    agr_num = (s21_size_t)va_arg(started_factor, unsigned int);
  if (!agr_num) agr_num = 0;

  char *result = s21_NULL;
  if (agr_num == 0 && (dest_format.flag_plus || dest_format.flag_space)) {
    if (dest_format.flag_plus) result = s21_width_format(dest_format, "+");
    if (dest_format.flag_space) result = s21_width_format(dest_format, " ");
  } else {
    char *tranced_int = s21_int_to_str(agr_num);
    if (tranced_int) {
      char *accur_form = s21_accur_int_format(dest_format, tranced_int, 0);
      if (accur_form) {
        result = s21_width_format(dest_format, accur_form);
        free(accur_form);
      }
      free(tranced_int);
    }
  }
  return result;
}

char *s21_width_format(struct s21_format_node dest_format,
                       const char *base_str) {
  if (!base_str) return s21_NULL;
  char *result = s21_NULL;
  s21_size_t new_len = 0;
  if (dest_format.width > s21_strlen(base_str))
    new_len = dest_format.width;
  else
    new_len = s21_strlen(base_str);
  result = s21_new_str_char(' ', new_len);
  if (result) {
    char *temp = result;
    s21_size_t offset = 0;
    if (!dest_format.flag_minus && (dest_format.width > s21_strlen(base_str)))
      offset = dest_format.width - s21_strlen(base_str);
    temp = temp + offset;
    s21_strncpy(temp, base_str, s21_strlen(base_str));
  }
  return result;
}

char *s21_accur_int_format(struct s21_format_node dest_format,
                           const char *base_str, int negative) {
  if (!base_str) return s21_NULL;
  char *result = s21_NULL;
  s21_size_t new_len = 0, offset = 0;
  if (negative || dest_format.flag_plus || dest_format.flag_space) new_len++;
  if (s21_strlen(base_str) > dest_format.accuracy) {
    new_len = new_len + s21_strlen(base_str);
  } else {
    new_len = new_len + dest_format.accuracy;
    offset = dest_format.accuracy - s21_strlen(base_str);
  }
  result = s21_new_str_char('0', new_len);
  if (result) {
    char *temp = result;
    if (negative) {
      *temp = '-';
      temp++;
    }
    if (!negative && dest_format.flag_space) {
      *temp = ' ';
      temp++;
    }
    if (!negative && dest_format.flag_plus) {
      *temp = '+';
      temp++;
    }
    temp = temp + offset;
    s21_strncpy(temp, base_str, s21_strlen(base_str));
  }
  return result;
}

char *s21_int_to_str(s21_size_t num) {
  s21_size_t temp = num, len = 0;
  while (temp > 0) {
    len++;
    temp /= 10;
  }
  char *result = (char *)malloc(sizeof(char) * (len + 1));
  if (result) {
    for (s21_size_t i = len - 1; num > 0; i--) {
      result[i] = num % 10 + '0';
      num /= 10;
    }
    result[len] = '\0';
  }
  return result;
}

s21_size_t s21_str_to_int(const char *num_str) {
  if (!num_str) return 0;
  int flag = 1;
  s21_size_t result = 0, len = s21_strlen(num_str);
  for (s21_size_t i = len - 1, k = 0; k < len && flag; i--, k++) {
    if (num_str[i] > 47 && num_str[i] < 58) {
      result = result + ((num_str[i] - 48) * (s21_size_t)pow(10, k));
    } else
      flag = 0;
  }
  if (!flag) result = 0;
  return result;
}

char *s21_float_to_str(double num, s21_size_t accuracy) {
  s21_size_t len = 0, full_len = 0;
  long temp_int = (long)floor(num);
  while (temp_int > 0) {
    len++;
    temp_int /= 10;
  }

  char *result = s21_NULL;
  if (accuracy != 0) {
    result = (char *)malloc(sizeof(char) * (len + 2 + accuracy));
    full_len = len + 1 + accuracy;
  } else {
    result = (char *)malloc(sizeof(char) * (len + 1));
    full_len = len;
  }

  if (result) {
    temp_int = (long)floor(num);
    for (long i = len - 1; i >= 0; i--) {
      result[i] = temp_int % 10 + '0';
      temp_int /= 10;
    }
    if (accuracy != 0) {
      double temp = num - floor(num);
      result[len] = '.';
      temp = temp * pow(10, accuracy);
      temp_int = (long)round(temp);
      for (s21_size_t i = 0, n = full_len - 1; i < accuracy; i++, n--) {
        result[n] = temp_int % 10 + '0';
        temp_int /= 10;
      }
    }
    result[full_len] = '\0';
  }
  if (len == 0) {
    char *temp = s21_insert(result, "0", 0);
    if (temp) {
      free(result);
      result = temp;
    }
  }

  return result;
}

s21_size_t s21_str_found_len(const char *string1, const char *string2) {
  if (!string1) return 0;
  if (!string2) return s21_strlen(string1);
  s21_size_t res = 0;
  for (int flag = 1; res < s21_strlen(string1) && flag;) {
    flag = 0;
    for (s21_size_t i = 0; i < s21_strlen(string2); i++) {
      if (string1[res] == string2[i]) flag = 1;
    }
    if (flag) res++;
  }
  return res;
}

char *s21_new_str_char(char symbol, s21_size_t len) {
  char *result = s21_NULL;
  result = (char *)malloc(sizeof(char) * (len + 1));
  if (result) {
    for (s21_size_t i = 0; i < len; i++) {
      result[i] = symbol;
    }
    result[len] = '\0';
  }
  return result;
}