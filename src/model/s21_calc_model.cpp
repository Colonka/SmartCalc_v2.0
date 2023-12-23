#include "s21_calc_model.h"

//===============Main method============//
namespace s21 {
int CalcModel::calculation(char *input_string, double x, double *resultic) {
  int res = 1;
  char initial_string[1000];
  char rpn_string[1000];
  bool check = check_input(input_string, initial_string);
  if (check) {
    infix_to_rpn(initial_string, rpn_string);
    res = rpn_calculation(rpn_string, x, resultic);
  } else {
    res = 0;
  }
  return res;
}

int CalcModel::rpn_calculation(char *input, double x, double *result) {
  std::stack<vtype> *stack = new std::stack<vtype>;
  int error = 1;
  for (int i = 0; input[i] != '\0'; i++) {
    if (isNumber(input[i])) {  // If number
      double number = 0;
      i += string_to_num(&input[i], &number);
      vtype num = {' ', number};
      stack->push(num);
    } else if (input[i] == 'x') {
      vtype NUM = {' ', x};
      stack->push(NUM);
    } else if (isOper(input[i])) {  // Function for operator
      try {
        oper(input[i], *stack);
      } catch (std::out_of_range &ex) {
        error = 2;
      }
    } else if (isFunc(input[i])) {  // Function for function
      try {
        func(input[i], *stack);
      } catch (std::out_of_range &ex) {
        error = 2;
      }
    }
  }
  if ((stack->empty() == false)) *result = stack->top().v;  // Writing value
  delete stack;
  return error;
}

//===============Method checking input string============//

bool CalcModel::check_input(char *in_equation, char *out_equation) {
  int scob = 0, flag = 1;
  char c[2];
  c[1] = '\0';
  if (in_equation[0] != ')' && in_equation[0] != '*' && in_equation[0] != '/' &&
      in_equation[0] != '+' && in_equation[0] != '%') {
    for (int i = 0; in_equation[i] != '\0'; i++) {
      if (in_equation[i] == '(' || in_equation[i] == ')') {
        check_bracket(&in_equation[i], &scob, out_equation);
      } else if (isNumber(in_equation[i])) {
        int count = 0;
        number_check(&in_equation[i], &count, out_equation);
        i += count - 1;
        count = 0;
      } else if (in_equation[i] == 's' || in_equation[i] == 'c' ||
                 in_equation[i] == 't' || in_equation[i] == 'a' ||
                 in_equation[i] == 'l' || in_equation[i] == 'm') {
        if ((isNumber(in_equation[i - 1]) || in_equation[i - 1] == ')') &&
            in_equation[i] != 'm') {
          c[0] = '*';
          strcat(out_equation, c);
        }
        i += check_trigon(&in_equation[i], out_equation);
      } else if (in_equation[i] == '*' || in_equation[i] == '/' ||
                 in_equation[i] == '+' || in_equation[i] == '^') {
        c[0] = in_equation[i];
        strcat(out_equation, c);
      } else if (in_equation[i] == 'x') {
        c[0] = in_equation[i];
        strcat(out_equation, c);
      } else if (in_equation[i] == '-') {
        if (i == 0) {
          c[0] = '?';
          strcat(out_equation, c);
        } else {
          check_minus(&in_equation[i], out_equation);
        }
      }
    }
  } else {
    flag = 0;
  }
  if (scob != 0) flag = 0;
  return flag;
}

//========Method reversing string to reverse polish notation==========//

void CalcModel::infix_to_rpn(char *input, char *output) {
  vtype temp = {' ', 0.0};
  std::stack<vtype> *stack = new std::stack<vtype>;
  int count = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == ')' &&
        (stack->empty() == false)) {    // check closing bracket
      while (stack->top().op != '(') {  // pop untill open bracket
        output[count++] = stack->top().op;
        if ((stack->empty() == false)) stack->pop();
        output[count++] = ' ';
      }
      if ((stack->empty() == false)) stack->pop();  // destroy opened bracket
    } else if (input[i] == '(') {                   // push opening bracket
      temp.op = '(';
      stack->push(temp);
    } else if (isNumber(input[i])) {  // output number
      int j = 0;
      while (isNumber(input[i + j])) {
        output[count++] = input[i + (j++)];
      }
      i += j - 1;
      output[count++] = ' ';
    } else if (input[i] == 'x') {  // output x
      if (isNumber(input[i - 1])) {
        output[count++] = '*';
        output[count++] = ' ';
      }
      output[count++] = input[i];
      output[count++] = ' ';
    } else if (isOper(input[i]) ||
               isFunc(input[i])) {  // output operator and func
      while ((stack->empty() == false) &&
             (prec(stack->top().op) > prec(input[i]) ||
              (prec(stack->top().op) == prec(input[i]) && input[i] != '^'))) {
        output[count++] = stack->top().op;
        if ((stack->empty() == false)) stack->pop();
        output[count++] = ' ';
      }
      temp.op = input[i];
      stack->push(temp);  // push last
    }
  }
  do {
    if ((stack->empty() == false)) {
      output[count++] = stack->top().op;
      stack->pop();
    }
    output[count++] = ' ';
  } while ((stack->empty() == false));  // clear
  output[count] = '\0';                 // add \0
  delete stack;
}

//===============Credit calculation methods============//

void CalcModel::credit_ann(double sum, int time, double percent,
                           double *month_pay, double *overpay,
                           double *common_pay) {
  double month_perc = percent / (12 * 100);
  double k_down = 1 - pow(1 + month_perc, -time);
  *month_pay = sum * month_perc / k_down;
  *common_pay = *month_pay * (double)time;
  *overpay = *common_pay - sum;
}

void CalcModel::credit_diff(double sum, int time, double percent,
                            double remainder, double *month_pay,
                            double *overpay, int cur_m) {
  for (int j = 0; j < time; j++) {
    this->credit_diff_support(sum, time, percent, remainder, month_pay, overpay,
                              cur_m);
    remainder = remainder - (sum / time);
    cur_m++;
  }
}

void CalcModel::credit_diff_support(double sum, int time, double percent,
                                    double remainder, double *month_pay,
                                    double *overpay, int cur_m) {
  double body = sum / time;
  double profit = remainder * (percent / 12 / 100);
  month_pay[cur_m] = body + profit;
  *overpay = *overpay + profit;
}

//===============Support methods for calculation===============//

void CalcModel::oper(char ch, std::stack<vtype> &stack) {
  vtype a, b, c;
  a = stack.top();
  if ((stack.empty() == 0)) stack.pop();
  b = stack.top();
  if ((stack.empty() == 0)) stack.pop();
  if (ch == '+') {
    c.v = a.v + b.v;
    stack.push(c);
  } else if (ch == '-') {
    c.v = b.v - a.v;
    stack.push(c);
  } else if (ch == '*') {
    c.v = a.v * b.v;
    stack.push(c);
  } else if (ch == '/') {
    if (a.v == 0) {
      throw std::out_of_range("Division by zero");
    } else {
      c.v = b.v / a.v;
      stack.push(c);
    }
  } else if (ch == '^') {
    c.v = pow(b.v, a.v);
    stack.push(c);
  } else if (ch == '%') {
    if (a.v == 0) {
      throw std::out_of_range("Division by zero");
    } else {
      c.v = (int)b.v % (int)a.v;
      stack.push(c);
    }
  }
}

void CalcModel::func(char ch, std::stack<vtype> &stack) {
  vtype a, b;
  a = stack.top();
  if ((stack.empty() == 0)) stack.pop();
  if (ch == '?') {
    b.v = a.v * (-1);
    stack.push(b);
  } else if (ch == 'i') {
    b.v = sin(a.v);
    stack.push(b);
  } else if (ch == 'o') {
    b.v = cos(a.v);
    stack.push(b);
  } else if (ch == 't') {
    if (cos(a.v) == 0) {
      throw std::out_of_range("NAN");
    } else {
      b.v = sin(a.v) / cos(a.v);
      stack.push(b);
    }
  } else if (ch == 'q') {
    if (a.v < 0) {
      throw std::out_of_range("NAN");
    } else {
      b.v = sqrt(a.v);
      stack.push(b);
    }
  } else if (ch == 'n') {
    if (a.v == 0.0) {
      throw std::out_of_range("NAN");
    } else if (a.v < 0) {
      throw std::out_of_range("NAN");
    } else {
      b.v = log(a.v);
      stack.push(b);
    }
  } else if (ch == 'g') {
    if (a.v == 0.0) {
      throw std::out_of_range("NAN");
    } else if (a.v < 0) {
      throw std::out_of_range("NAN");
    } else {
      b.v = log10(a.v);
      stack.push(b);
    }
  } else if (ch == 'd') {
    if (a.v > 1.0 || a.v < -1.0) {
      throw std::out_of_range("NAN");
    } else {
      b.v = asin(a.v);
      stack.push(b);
    }
  } else if (ch == 'v') {
    if (a.v > 1 || a.v < -1) {
      throw std::out_of_range("NAN");
    } else {
      b.v = acos(a.v);
      stack.push(b);
    }
  } else if (ch == 'y') {
    b.v = atan(a.v);
    stack.push(b);
  }
}

int CalcModel::string_to_num(char *str, double *x) {
  int counter = 0;
  int found_point = 0;
  int point_counter = 0;
  while (1) {  // Parse micro string
    if (isNumber(str[counter]) == 1 && found_point == 0) {
      point_counter++;
      counter++;
    } else if (isNumber(str[counter]) == 2 && found_point == 0) {
      point_counter = counter;
      counter++;
      found_point = 1;
    } else if (isNumber(str[counter]) == 1 && found_point == 1) {
      counter++;
    } else {
      break;
    }
  }
  for (int i = 0; i < point_counter; i++) {
    *x += ((int)str[i] + 2) % 10 * pow(10, point_counter - i - 1);
  }  // Before dot
  for (int i = point_counter + 1; i < counter; i++) {
    *x += ((int)str[i] + 2) % 10 * (1. / pow(10, i - point_counter));
  }  // After dot
  return counter;
}

//===============Support methods for checking_input============//

void CalcModel::number_check(char *form, int *count, char *out_equation) {
  int g = 0, len = 0, len_after_dot = 0;
  bool check_e = 0;
  char chis[256];
  char c[2];
  c[1] = '\0';
  while (form[g] != '\0' && !isOper(form[g]) && form[g] != ')' &&
         form[g] != 'x') {
    if (isNumber(form[g])) {
      chis[g] = form[g];
      len++;
      g++;
    } else if (isNumber(form[g]) == 2) {  // "."
      chis[g] = form[g];
      g++;
      while (form[g] != '\0' && !isOper(form[g]) && form[g] != ')' &&
             form[g] != 'x') {
        if (isNumber(form[g])) {
          chis[g] = form[g];
          len_after_dot++;
          g++;
        } else {
          break;
        }
      }
      len_after_dot++;
    } else if (form[g] == 'e') {
      check_e = 1;
      char chis_after[256];
      chis[g] = '\0';
      int len_after_e = 0;
      check_eps(&form[g + 1], chis, chis_after, &len_after_e);
      for (int i = 0; chis_after[i] != '\0'; i++) {
        c[0] = chis_after[i];
        strcat(out_equation, c);
      }
      *count = len + len_after_dot + len_after_e + 1;
      break;
    } else {
      break;
    }
  }
  if (check_e == 0) {
    for (int i = 0; i < g; i++) {
      c[0] = chis[i];
      strcat(out_equation, c);
    }
    *count = len + len_after_dot;
  }
}

void CalcModel::check_eps(char *form, char *chis, char *chis_after,
                          int *len_after_e) {
  char sign = '+';
  int i = 0;
  bool is_dot = 0;
  if (form[i] == '-') {
    sign = '-';
    i++;
    ++*len_after_e;
  }
  double num = 0.0;
  *len_after_e = *len_after_e + string_to_num(&form[i], &num);
  int ptr = 0;
  for (int j = 0;; ++j) {
    if (chis[j] == '.') {
      is_dot = 1;
      break;
    }
    if (chis[j] == '\0') {
      break;
    }
    chis_after[j] = chis[j];
    ptr = j;
  }
  if (sign == '+') {
    check_eps_plus(chis, chis_after, &ptr, &num, is_dot);
  } else {
    check_eps_minus(chis, chis_after, &ptr, num);
  }
}

void CalcModel::check_eps_minus(char *chis, char *chis_after, int *ptr,
                                int num) {
  if (*ptr + 1 > num) {
    chis_after[num] = '.';
    int j = 0;
    for (int i = 0; chis[num + j + i] != '\0'; ++j) {
      if (chis[num + i + j] != '.') {
        chis_after[num + 1 + j] = chis[num + i + j];
      } else {
        chis_after[num + 1 + j] = chis[num + i + j + 1];
        ++i;
      }
    }
    chis_after[num + j + 3] = '\0';
  } else if (*ptr + 1 < num) {
    chis_after[0] = '0';
    chis_after[1] = '.';
    int j = 0;
    for (int i = 0; chis[j + i] != '\0'; ++j) {
      if (chis[i + j] != '.') {
        chis_after[2 + j] = chis[i + j];
      } else {
        ++i;
        chis_after[2 + j] = chis[i + j];
      }
    }
    chis_after[j + 2] = '\0';
  }
}

void CalcModel::check_eps_plus(char *chis, char *chis_after, int *ptr,
                               double *num, bool is_dot) {
  int dot_tmp = (is_dot) ? 2 : 1;
  for (; *num != 0 && chis[*ptr + dot_tmp] != '\0'; ++*ptr) {
    chis_after[*ptr + 1] = chis[*ptr + dot_tmp];
    *num = *num - 1;
  }
  if (*num == 0) {
    chis_after[*ptr + 1] = '.';
    for (; chis[*ptr + 2] != '\0'; ++*ptr) {
      chis_after[*ptr + 2] = chis[*ptr + 2];
    }
    chis_after[*ptr + 3] = '\0';
  } else {
    for (; *num >= 0; ++*ptr) {
      chis_after[*ptr + 1] = '0';
      --*num;
    }
    chis_after[*ptr] = '\0';
  }
}

int CalcModel::check_trigon(const char *form, char *result) {
  int i = 0, res = 2;
  char c[2];
  c[1] = '\0';
  if (form[i] == 's' && form[i + 1] == 'i' && form[i + 2] == 'n') {
    c[0] = 'i';  // sin
    strcat(result, c);
  }
  if (form[i] == 's' && form[i + 1] == 'q' && form[i + 2] == 'r' &&
      form[i + 3] == 't') {
    c[0] = 'q';  // sqrt
    strcat(result, c);
    res++;
  }
  if (form[i] == 'c' && form[i + 1] == 'o' && form[i + 2] == 's') {
    c[0] = 'o';  // cos
    strcat(result, c);
  }
  if (form[i] == 't' && form[i + 1] == 'a' && form[i + 2] == 'n') {
    c[0] = 't';  // tan
    strcat(result, c);
  }
  if (form[i] == 'l') {
    if (form[i + 1] == 'n') {
      c[0] = 'n';  // ln
      strcat(result, c);
      res--;
    }
    if (form[i + 1] == 'o' && form[i + 2] == 'g') {
      c[0] = 'g';  // log
      strcat(result, c);
    }
  }
  if (form[i] == 'a') {
    if (form[i + 1] == 's') {
      c[0] = 'd';  // asin
      strcat(result, c);
      res++;
    }
    if (form[i + 1] == 'c') {
      c[0] = 'v';  // acos
      strcat(result, c);
      res++;
    }
    if (form[i + 1] == 't') {
      c[0] = 'y';  // atan
      strcat(result, c);
      res++;
    }
  }
  if (form[i] == 'm') {
    c[0] = '%';
    strcat(result, c);
  }
  return res;
}

void CalcModel::check_minus(char *form, char *out_equation) {
  int i = 0;
  char c[2];
  c[1] = '\0';
  if (afterminus(&form[i]) &&
      (!isNumber(form[i - 1]) && !isFunc(form[i - 1]) &&
       !isOper(form[i - 1])) &&
      form[i - 1] != ')') {
    c[0] = '?';
    strcat(out_equation, c);
  } else {
    c[0] = '-';
    strcat(out_equation, c);
  }
}

bool CalcModel::afterminus(char *form) {
  bool res = 0;
  if (isNumber(form[1])) res = 1;
  if (form[1] == 's') res = 1;
  if (form[1] == 'c') res = 1;
  if (form[1] == 't') res = 1;
  if (form[1] == 'a') res = 1;
  if (form[1] == 'l') res = 1;
  if (form[1] == 'x') res = 1;
  if (form[-1] == '(') res = 1;
  if (form[1] == '(') res = 1;
  return res;
}

void CalcModel::check_bracket(const char *form, int *scob, char *out_equation) {
  int i = 0;
  char c[2];
  c[1] = '\0';
  if (form[i] == '(') {
    c[0] = form[i];
    strcat(out_equation, c);
    *scob = *scob + 1;
  } else {
    c[0] = form[i];
    strcat(out_equation, c);
    *scob = *scob - 1;
  }
}

//===============Support methods for detecting token's definition==========

bool CalcModel::isFunc(char x) {
  int res = 0;
  if (x == '?' || x == 'i' || x == 'o' || x == 't' || x == 'q' || x == 'g' ||
      x == 'n' || x == 'd' || x == 'v' || x == 'y')
    res = 1;
  return res;
}

bool CalcModel::isOper(char x) {
  int res = 0;
  if (x == '+' || x == '-' || x == '/' || x == '*' || x == '^' || x == '%')
    res = 1;
  return res;
}

int CalcModel::isNumber(char x) {
  int res = 0;
  if (x > 47 && x < 58) res = 1;
  if (x == '.') res = 2;
  return res;
}

//===============Support methods for reversin to polish notation==========

int CalcModel::prec(char x) {
  int res = 0;
  if (x == '(' || x == ')') res = 1;
  if (x == '+' || x == '-') res = 2;
  if (x == '*' || x == '/' || x == '%') res = 3;
  if (x == '^' || isFunc(x)) res = 4;
  return res;
}
}  // namespace s21
