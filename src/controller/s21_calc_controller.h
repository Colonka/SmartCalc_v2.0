#ifndef SRC_S21_CALC_CONTROLLER_H_
#define SRC_S21_CALC_CONTROLLER_H_

#include "../model/s21_calc_model.h"

namespace s21 {
class CalcController {
 private:
  CalcModel *model_;

 public:
  CalcController() = delete;
  CalcController(CalcModel *model) : model_(model) {}

  bool check_input(char *in_equation, char *out_equation) {
    return model_->check_input(in_equation, out_equation);
  }

  void rpn(char *input, char *output) { model_->infix_to_rpn(input, output); }

  int calculation(char *input_string, double x, double *resultic) {
    return model_->calculation(input_string, x, resultic);
  }

  int rpn_calculation(char *input, double x, double *result) {
    return model_->rpn_calculation(input, x, result);
  }

  void credit_ann(double sum, int time, double percent, double *month_pay,
                  double *overpay, double *common_pay) {
    model_->credit_ann(sum, time, percent, month_pay, overpay, common_pay);
  }

  void credit_diff(double sum, int time, double percent, double remainder,
                   double *month_pay, double *overpay, int cur_m) {
    model_->credit_diff(sum, time, percent, remainder, month_pay, overpay,
                        cur_m);
  }
};
}  // namespace s21

#endif
