#include "../model/s21_calc_model.h"
#include "gtest/gtest.h"

TEST(test_calculation, mult_miss_1) {
  s21::CalcModel model_;
  char ex[20] = "5cos(x)";
  double res = 0.0;
  double true_res = 5.0;
  model_.calculation(ex, 0, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, mult_miss_2) {
  s21::CalcModel model_;
  char ex[20] = "(5+1)cos(x)";
  double res = 0.0;
  double true_res = 6.0;
  model_.calculation(ex, 0, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, eps_1) {
  s21::CalcModel model_;
  char ex[20] = "123e3 + 456";
  double res = 0.0;
  double true_res = 123456.0;
  model_.calculation(ex, 1, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, eps_2) {
  s21::CalcModel model_;
  char ex[20] = "1.235e2 + 456";
  double res = 0.0;
  double true_res = 579.5;
  model_.calculation(ex, 1, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, eps_3) {
  s21::CalcModel model_;
  char ex[20] = "1.235e2 + 456e2";
  double res = 0.0;
  double true_res = 45723.5;
  model_.calculation(ex, 1, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, eps_4) {
  s21::CalcModel model_;
  char ex[30] = "1.235e2 + 1234.56e-2";
  double res = 0.0;
  double true_res = 135.8456;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e5);
}

TEST(test_calculation, eps_5) {
  s21::CalcModel model_;
  char ex[30] = "0.00235e2 + 12.34e-4";
  double res = 0.0;
  double true_res = 0.236234;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, plus_1) {
  s21::CalcModel model_;
  char ex[10] = "25+15";
  double res = 0.0;
  double true_res = 40.0;
  model_.calculation(ex, 1, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, plus_2) {
  s21::CalcModel model_;
  char ex[10] = "-25+(-15)";
  double res = 0.0;
  double true_res = -40.0;
  model_.calculation(ex, 1, &res);
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, plus_3) {
  s21::CalcModel model_;
  char ex[20] = "25.65+(-15.54)";
  double res = 0.0;
  double true_res = 10.11;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, plus_4) {
  s21::CalcModel model_;
  char ex[50] = "-25.5555553+15.4444441";
  double res = 0.0;
  double true_res = -10.1111112;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

// MINUS

TEST(test_calculation, minus_1) {
  s21::CalcModel model_;
  char ex[50] = "25-15";
  double res = 0.0;
  double true_res = 10.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, minus_2) {
  s21::CalcModel model_;
  char ex[50] = "25-(-15)";
  double res = 0.0;
  double true_res = 40.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, minus_3) {
  s21::CalcModel model_;
  char ex[50] = "-25-(-15)";
  double res = 0.0;
  double true_res = -10.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, minus_4) {
  s21::CalcModel model_;
  char ex[50] = "-25.666-15.334";
  double res = 0.0;
  double true_res = -41.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

// MULT

TEST(test_calculation, mult_1) {
  s21::CalcModel model_;
  char ex[50] = "20*5";
  double res = 0.0;
  double true_res = 100.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, mult_2) {
  s21::CalcModel model_;
  char ex[50] = "-20.15*(-0.554)";
  double res = 0.0;
  double true_res = 11.1631;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, mult_3) {
  s21::CalcModel model_;
  char ex[50] = "-25465.56*155.41";
  double res = 0.0;
  double true_res = -3957602.6796;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

// DIVISION

TEST(test_calculation, div_1) {
  s21::CalcModel model_;
  char ex[50] = "-25465.56/155.41";
  double res = 0.0;
  double true_res = -163.860498;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, div_2) {
  s21::CalcModel model_;
  char ex[50] = "-25465.56/(-155.41)";
  double res = 0.0;
  double true_res = -163.8604980;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, div_3) {
  s21::CalcModel model_;
  char ex[50] = "-25465.56/0";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, div_4) {
  s21::CalcModel model_;
  char ex[50] = "-25465.56/(-0.41)";
  double res = 0.0;
  double true_res = 62111.12195;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

// mod

TEST(test_calculation, mod_1) {
  s21::CalcModel model_;
  char ex[50] = "3mod2";
  double res = 0.0;
  double true_res = 1.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, mod_2) {
  s21::CalcModel model_;
  char ex[50] = "2mod2";
  double res = 0.0;
  double true_res = 0.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, mod_3) {
  s21::CalcModel model_;
  char ex[50] = "2mod0";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

// degree

TEST(test_calculation, deg_1) {
  s21::CalcModel model_;
  char ex[50] = "2^(1.53)";
  double res = 0.0;
  double true_res = 2.8878583;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, deg_2) {
  s21::CalcModel model_;
  char ex[50] = "-2^(-1.53)";
  double res = 0.0;
  double true_res = -0.3462773;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, deg_3) {
  s21::CalcModel model_;
  char ex[50] = "2^(-1.53)";
  double res = 0.0;
  double true_res = 0.3462773;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, deg_4) {
  s21::CalcModel model_;
  char ex[50] = "-2^(1.53)";
  double res = 0.0;
  double true_res = -2.8878583;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

// sqrt

TEST(test_calculation, sqrt_1) {
  s21::CalcModel model_;
  char ex[50] = "sqrt(16)";
  double res = 0.0;
  double true_res = 4.0;
  model_.calculation(ex, 1, &res);
  EXPECT_DOUBLE_EQ(res, true_res);
}

TEST(test_calculation, sqrt_2) {
  s21::CalcModel model_;
  char ex[50] = "sqrt(23.56)";
  double res = 0.0;
  double true_res = 4.8538644;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, sqrt_3) {
  s21::CalcModel model_;
  char ex[50] = "sqrt(23.56)";
  double res = 0.0;
  double true_res = 4.8538644;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, sqrt_4) {
  s21::CalcModel model_;
  char ex[50] = "sqrt(-4)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_NEAR(res, true_res, 10e6);
}

// trigon

TEST(test_calculation, sin_1) {
  s21::CalcModel model_;
  char ex[50] = "sin(3.56)";
  double res = 0.0;
  double true_res = -0.4063057;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, sin_2) {
  s21::CalcModel model_;
  char ex[50] = "sin(x)";
  double res = 0.0;
  double true_res = 0.8414709;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, asin_1) {
  s21::CalcModel model_;
  char ex[50] = "asin(0.95)";
  double res = 0.0;
  double true_res = 1.2532358;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, asin_2) {
  s21::CalcModel model_;
  char ex[50] = "asin(1.01)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, cos_1) {
  s21::CalcModel model_;
  char ex[50] = "cos(3.56)";
  double res = 0.0;
  double true_res = -0.9137372;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, acos_1) {
  s21::CalcModel model_;
  char ex[50] = "acos(0.95)";
  double res = 0.0;
  double true_res = 0.3175604;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, acos_2) {
  s21::CalcModel model_;
  char ex[50] = "acos(1.01)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, tan_1) {
  s21::CalcModel model_;
  char ex[50] = "tan(3.56)";
  double res = 0.0;
  double true_res = 0.4446636;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, atan_1) {
  s21::CalcModel model_;
  char ex[50] = "atan(3.56)";
  double res = 0.0;
  double true_res = 1.2969542;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

// log

TEST(test_calculation, log_1) {
  s21::CalcModel model_;
  char ex[50] = "log(3.56)";
  double res = 0.0;
  double true_res = 0.5514499;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, log_2) {
  s21::CalcModel model_;
  char ex[50] = "log(-0.1)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, log_3) {
  s21::CalcModel model_;
  char ex[50] = "log(0.0)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, ln_1) {
  s21::CalcModel model_;
  char ex[50] = "ln(3.56)";
  double res = 0.0;
  double true_res = 1.2697605;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, ln_2) {
  s21::CalcModel model_;
  char ex[50] = "ln(-0.1)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

TEST(test_calculation, ln_3) {
  s21::CalcModel model_;
  char ex[50] = "ln(0.0)";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 2;
  EXPECT_EQ(res, true_res);
}

// credit

TEST(test_calculation, credit_ann_monthly) {
  s21::CalcModel model_;
  int time = 24;
  double percent = 10.0;
  double sum = 300000.0;
  double monthly_pay = 0.0;
  double monthly_pay_true = 13843.48;
  double overpay = 0.0;
  double common_pay = 0.0;
  model_.credit_ann(sum, time, percent, &monthly_pay, &overpay, &common_pay);
  EXPECT_NEAR(monthly_pay, monthly_pay_true, 1e2);
}

TEST(test_calculation, credit_ann_overpay) {
  s21::CalcModel model_;
  int time = 24;
  double percent = 10.0;
  double sum = 300000.0;
  double monthly_pay = 0.0;
  double overpay = 0.0;
  double overpay_true = 32243.52;
  double common_pay = 0.0;
  model_.credit_ann(sum, time, percent, &monthly_pay, &overpay, &common_pay);
  EXPECT_NEAR(overpay, overpay_true, 1e-1);
}

TEST(test_calculation, credit_ann_common_pay) {
  s21::CalcModel model_;
  int time = 24;
  double percent = 10.0;
  double sum = 300000.0;
  double monthly_pay = 0.0;
  double overpay = 0.0;
  double common_pay = 0.0;
  double common_pay_true = 332243.52;
  model_.credit_ann(sum, time, percent, &monthly_pay, &overpay, &common_pay);
  EXPECT_NEAR(common_pay, common_pay_true, 1e-1);
}

TEST(test_calculation, credit_diff_test) {
  s21::CalcModel model_;
  int time = 12;
  double percent = 24.0;
  double sum = 300000.0;
  double *monthly_pay = new double[12];
  double *monthly_pay_true = new double[12];
  monthly_pay_true[0] = 31000.0;
  for (int j = 1; j < time; j++) {
    monthly_pay_true[j] = monthly_pay_true[j - 1] - 500;
  }
  double overpay = 0.0;
  double overpay_true = 39000.0;
  double common_pay = 0.0;
  double common_pay_true = 339000.0;
  double remainder = sum;
  int cur_m = 0;
  model_.credit_diff(sum, time, percent, remainder, monthly_pay, &overpay,
                     cur_m);
  for (int i = 0; i < time; i++) {
    EXPECT_NEAR(monthly_pay[i], monthly_pay_true[i], 1e-1);
  }
  common_pay = overpay + sum;
  EXPECT_NEAR(overpay, overpay_true, 1e-1);
  EXPECT_NEAR(common_pay, common_pay_true, 1e-1);
  delete[] monthly_pay;
  delete[] monthly_pay_true;
}

// HARD TESTS

TEST(test_calculation, hard_1) {
  s21::CalcModel model_;
  char ex[100] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double res = 0.0;
  double true_res = -1.83907152908;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, hard_2) {
  s21::CalcModel model_;
  char ex[100] = "(ln(50)+100)mod(2+2.5)+(lg(100)*20)^(2+2)+sqrt(25)";
  double res = 0.0;
  double true_res = 2560005.412023;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, hard_3) {
  s21::CalcModel model_;
  char ex[100] = "acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)";
  double res = 0.0;
  double true_res = 1.593531;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

TEST(test_calculation, hard_4) {
  s21::CalcModel model_;
  char ex[100] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double res = 0.0;
  double true_res = 10.0;
  model_.calculation(ex, 1, &res);
  EXPECT_NEAR(res, true_res, 10e6);
}

// invalid_inpu_test

TEST(test_calculation, invalid_input_1) {
  s21::CalcModel model_;
  char ex[50] = "ln(0.0";
  double res_res;
  int res = model_.calculation(ex, 1, &res_res);
  int true_res = 0;
  EXPECT_EQ(res, true_res);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}