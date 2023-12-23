#include <QApplication>

#include "view/s21_calc_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::CalcModel calc_model;
  s21::CalcController calc_controller(&calc_model);
  s21::CalcView calc_view(&calc_controller);

  setlocale(LC_NUMERIC, "C");
  calc_view.show();

  return a.exec();
}
