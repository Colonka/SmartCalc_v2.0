#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>

#ifndef SRC_S21_CALCMODEL_H_
#define SRC_S21_CALCMODEL_H_

// Функции

// ? - унарный минус
// i - sin
// o - cos
// t - tan
// q - sqrt
// n - ln
// g - log
// d - asin
// v - acos
// y - atan

// Приоритеты

// () - 1
// +- - 2
// */ - 3
// ^ или функции - 4

/**
 * @brief union хранящий элемент уравнения
 * @param op - оператор
 * @param v - число
 */
struct vtype {
  char op;   // Operator
  double v;  // Value
};

namespace s21 {
class CalcModel {
 public:
  //===============Method checking input string============//

  /**
   * @brief Метод осуществляющий проверку на валидность входящей в модель строки
   * @param in_equation указатель на входящую строку уравнения
   * @param out_equation указатель на входящую строку уравнения
   * @return код ошибки 0 - invalid input, 1 - ok
   */
  bool check_input(char *in_equation, char *out_equation);

  //========Method reversing string to reverse polish notation==========//

  /**
   * @brief Метод осуществляющий перевод строки уравнения в обратную польскую
   * нотацию
   * @param input указатель на входящую строку уравнения
   * @param output указатель на выходную строку уравнения
   */
  void infix_to_rpn(char *input, char *output);

  //===============Main method============//

  /**
   * @brief Метод осуществляющий рассчет (полный цикл)
   * @param input_string указатель на входящую строку уравнения
   * @param x - значение х
   * @param resultic - ответ
   * @return 0 - invalid input, 1 - ok, 2 - nan
   */
  int calculation(char *input_string, double x, double *resultic);

  /**
   * @brief Метод осуществляющий вычисление строки вида обратной польской
   * нотации
   * @param input указатель на входную строку
   * @param x значение аргумента x
   * @param result результат вычисления
   * @return код ошибки  1 - ok, 2 - nan
   */
  int rpn_calculation(char *input, double x, double *result);

  //===============Credit calculation methods============//

  /**
   * @brief Функция вызова расчета кредита (аннуитетный)
   * @param sum - сумма кредита
   * @param time - срок
   * @param percent - годовая процентная ставкa
   * @param month_pay - указатель на переменную ежемесячного платежа
   * @param overpay - указатель на переменную суммы переплаты
   * @param common_pay - указатель на переменную общей выплаты
   */
  void credit_ann(double sum, int time, double percent, double *month_pay,
                  double *overpay, double *common_pay);

  /**
   * @brief Функция вызова расчета кредита (дифферинциальный)
   * @param sum - сумма кредита
   * @param time - срок
   * @param percent - годовая процентная ставкa
   * @param remainder - остаток тела кредита
   * @param month_pay - указатель на переменную ежемесячного платежа
   * @param overpay - указатель на переменную суммы переплат
   * @param cur_m - текущий месяц
   */
  void credit_diff(double sum, int time, double percent, double remainder,
                   double *month_pay, double *overpay, int cur_m);

 private:
  //===============Support methods for calculation===============//

  /**
   * @brief Вспомогательный метод для расчета кредита (дифферинциальный)
   * @param sum - сумма кредита
   * @param time - срок
   * @param percent - годовая процентная ставкa
   * @param remainder - остаток тела кредита
   * @param month_pay - указатель на переменную ежемесячного платежа
   * @param overpay - указатель на переменную суммы переплат
   * @param cur_m - текущий месяц
   */
  void credit_diff_support(double sum, int time, double percent,
                           double remainder, double *month_pay, double *overpay,
                           int cur_m);

  /**
   * @brief Вспомогательный метод осуществляющий оперции вычисления операторов
   * @param ch индетификатор оператора
   * @param top ссылка на стэк процесса вычисления
   */
  void oper(char ch, std::stack<vtype> &stack);

  /**
   * @brief Вспомогательный метод осуществляющий оперции вычисления функций
   * @param ch индетификатор оператора
   * @param top ссылка на стэк процесса вычисления
   */
  void func(char ch, std::stack<vtype> &stack);

  /**
   * @brief Метод перевода числа из строкового вида в числовой
   * @param str указатель на входную строку
   * @param x результат перевода
   */
  int string_to_num(char *str, double *x);

  //===============Support methods for checking_input==========

  /**
   * @brief Метод осуществляющий проверку при встрече в строке числа
   * @param form указатель на место во входящей строке уравнения
   * @param count - счеткик прочтенных символов строки
   * @param out_equation - указатель на выходную строку уравнения
   */
  void number_check(char *form, int *count, char *out_equation);

  /**
   * @brief Метод осуществляющий проверку при встрече знака 'e'
   * @param form указатель на исходную строку
   * @param chis указатель на строку числа до обработки 'e'
   * @param chis_after - указатель на строку числа после обработки 'e'
   * @param len_after_e - количество пройденных токенов после е
   */
  void check_eps(char *form, char *chis, char *chis_after, int *len_after_e);

  /**
   * @brief Вспомогательный метод осуществляющий проверку при положительном 'e'
   * @param chis указатель на строку числа до обработки 'e'
   * @param chis_after - указатель на строку числа после обработки 'e'
   * @param ptr - количество пройденных токенов после е
   * @param num - разряд степени
   * @param is_dot - указывает на дробность обрабатываемого числа
   */
  void check_eps_plus(char *chis, char *chis_after, int *ptr, double *num,
                      bool is_dot);

  /**
   * @brief Вспомогательный метод осуществляющий проверку при отрицательном 'e'
   * @param chis указатель на строку числа до обработки 'e'
   * @param chis_after - указатель на строку числа после обработки 'e'
   * @param ptr - количество пройденных токенов после е
   * @param num - разряд степени
   */
  void check_eps_minus(char *chis, char *chis_after, int *ptr, int num);

  /**
   * @brief Метод осуществляющий проверку при встрече символа тригон-ой
   * функции
   * @param form указатель на место во входящей строке уравнения
   * @param result указатель на выходную строку уравнения
   * @return количество пройденных токенов строки
   */
  int check_trigon(const char *form, char *result);

  /**
   * @brief Метод осуществляющий проверку при встрече знака "-"(оператор или
   * унарный)
   * @param form указатель на место во входящей строке уравнения
   * @param out_equation - указатель на выходную строку уравнения
   */
  void check_minus(char *form, char *out_equation);

  /**
   * @brief Вспомогательный метод для проверки при встрече знака "-"
   * @param form указатель на место во входящей строке уравнения
   * @return код знака "-" - 0 - оператор, 1 - унарный минус
   */
  bool afterminus(char *form);

  /**
   * @brief Метод осуществляющий проверку количества открытых и закрытых скобок
   * уравнения
   * @param form указатель на место во входящей строке уравнения
   * @param scob указатель на флаг четности
   * @param out_equation - указатель на выходную строку уравнения
   */
  void check_bracket(const char *form, int *scob, char *out_equation);

  //===============Support methods for detecting token's definition==========

  /**
   * @brief Метод осуществляющий проверку является ли токен функцией
   * @param x - токен
   * @return - 1 - явлется, 0 - не является
   */
  bool isFunc(char x);

  /**
   * @brief Метод осуществляющий проверку является ли токен оператором
   * @param x - токен
   * @return - 1 - явлется, 0 - не является
   */
  bool isOper(char x);

  /**
   * @brief Метод осуществляющий проверку является ли токен числом
   * @param x - токен
   * @return - 1 - int, 2 - double, 0 - не является
   */
  int isNumber(char x);

  //===============Support methods for reversin to polish notation==========

  /**
   * @brief Метод осуществляющий определение приоритетности токена
   * @param x - токен
   * @return - значение приоритетности
   */
  int prec(char x);
};
}  // namespace s21
#endif  // SRC_S21_CALCMODEL_H_
