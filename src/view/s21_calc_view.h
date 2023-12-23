#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QDateTime>
#include <QDialog>
#include <QHBoxLayout>
#include <QLocale>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <Qvector>

#include "../controller/s21_calc_controller.h"

namespace s21 {

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(CalcController *controller_ptr, QWidget *parent = nullptr);
  ~CalcView();

 private:
  Ui::CalcView *ui;
  CalcController *controller_;

  bool isClickedX = false;
  QString input_real;
  double h, X;
  int Xbegin, Xend, Ybegin, Yend;
  QVector<double> x, y;
  QTableWidget *table;
  QString date_credit;
  std::string date_credit_str;
  QDate cd;

 private slots:
  /**
   * @brief Функция обработки нажатия кнопок цифр и простых операторов
   */
  void digit_buttons();
  /**
   * @brief Функция обработки нажатия кнопок тригонометрических функция
   */
  void trigon_func();
  /**
   * @brief Функция обработки нажатия кнопки посимвольного удаления
   */
  void button_delete();
  /**
   * @brief Функция обработки нажатия кнопки удаления всей строки
   */
  void button_AC();
  /**
   * @brief Функция обработки нажатия кнопки печати символа "х"
   */
  void button_X();
  /**
   * @brief Функция обработки нажатия кнопки символа "="
   */
  void button_equal();
  /**
   * @brief Функция обработки нажатия кнопки построения графика
   */
  void button_build_graph();
  /**
   * @brief Функция обработки нажатия кнопки расчета кредита
   */
  void on_pushButton_credit_count_clicked();
  /**
   * @brief Вспомогательная функция для заполнения столбца "Месяц"
   * @param month - номер месяца
   * @param month - номер года
   * @param res - указатель на переменную храняющую данные месяца и года в
   * строковом формате
   */
  void set_credit_date(int month, int year, QString *res);
  /**
   * @brief Функция для расчета количества месяцев прошедших с начала кредита до
   * текущего месяца
   * @param st_m - номер месяца начала кредита
   * @param st_y - номер года начала кредита
   * @param cr_m - номер месяца начала кредита
   * @param cr_y - номер года начала кредита
   * @return  количество месяцев прошедших с даты начала кредита по текущцю дату
   */
  int time_from_start(int st_m, int st_y, int cr_m, int cr_y);
};
}  // namespace s21
#endif  // CALCVIEW_H
