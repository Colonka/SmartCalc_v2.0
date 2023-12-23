#include "s21_calc_view.h"

#include "ui_s21_calc_view.h"

namespace s21 {
CalcView::CalcView(s21::CalcController *controller_ptr, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView), controller_(controller_ptr) {
  ui->setupUi(this);

  ui->doubleSpinBox_X->setMinimum(-1000000);
  ui->doubleSpinBox_X->setMaximum(1000000);
  ui->doubleSpinBox_credit_sum->setMaximum(10000000);

  cd = QDate::currentDate();
  ui->date_credit_start->setDate(cd);

  ui->radioButton_ann->setChecked(1);

  ui->spinBox_X_min->setMinimum(-1000000);
  ui->spinBox_X_min->setMaximum(1000000);
  ui->spinBox_X_max->setMaximum(1000000);
  ui->spinBox_X_max->setMinimum(-1000000);
  ui->spinBox_Y_min->setMinimum(-1000000);
  ui->spinBox_Y_min->setMaximum(1000000);
  ui->spinBox_Y_max->setMaximum(1000000);
  ui->spinBox_Y_max->setMinimum(-1000000);

  ui->spinBox_X_min->setValue(-10);
  ui->spinBox_X_max->setValue(10);
  ui->spinBox_Y_min->setValue(-5);
  ui->spinBox_Y_max->setValue(5);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_opened_scob, SIGNAL(clicked()), this,
          SLOT(digit_buttons()));
  connect(ui->pushButton_closed_scob, SIGNAL(clicked()), this,
          SLOT(digit_buttons()));
  connect(ui->pushButton_division, SIGNAL(clicked()), this,
          SLOT(digit_buttons()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digit_buttons()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_x_sign, SIGNAL(clicked()), this, SLOT(button_X()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigon_func()));
  connect(ui->pushButton_degree_sign, SIGNAL(clicked()), this,
          SLOT(trigon_func()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(button_equal()));
  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(button_delete()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(button_AC()));
  connect(ui->pushButton_build_graph, SIGNAL(clicked()), this,
          SLOT(button_build_graph()));

  this->setWindowTitle("s21_calc_2.0");
}

CalcView::~CalcView() { delete ui; }

//=======Slots=======//

void CalcView::button_build_graph() {
  if (isClickedX == true) {
    if (ui->widget->graph()) {
      ui->widget->graph(0)->data()->clear();
      x.clear();
      y.clear();
    }
    QByteArray lab = input_real.toLocal8Bit();
    char *input_str = lab.data();
    char *output_str = new char[1000];
    if (controller_->check_input(input_str, output_str)) {
      char *output_rpn = new char[1000];
      controller_->rpn(output_str, output_rpn);
      h = 0.01;
      Xbegin = ui->spinBox_X_min->value();
      Xend = ui->spinBox_X_max->value();
      Ybegin = ui->spinBox_Y_min->value();
      Yend = ui->spinBox_Y_max->value();
      double RES = 0.0;
      for (X = Xbegin; X <= Xend; X += h) {
        x.push_back(X);
        if ((controller_->rpn_calculation(output_rpn, X, &RES)) == 2) {
          ui->label_equation_result->setText("NAN");
          break;
        }
        y.push_back(RES);
      }
      ui->widget->xAxis->setRange(Xbegin, Xend);
      ui->widget->yAxis->setRange(Ybegin, Yend);
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x, y);
      ui->widget->replot();
    } else {
      ui->label_equation_result->setText("INVALID INPUT");
    }
  }
}

void CalcView::button_X() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label_equation;
  new_label_equation = ui->label_equation->text() + button->text();
  input_real = input_real + button->text();
  ui->label_equation->setText(new_label_equation);
  isClickedX = true;
}

void CalcView::digit_buttons() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label_equation;
  new_label_equation = ui->label_equation->text() + button->text();
  input_real = input_real + button->text();
  ui->label_equation->setText(new_label_equation);
}

void CalcView::trigon_func() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label_equation;
  new_label_equation = ui->label_equation->text() + button->text() + '(';
  input_real = input_real + button->text() + '(';
  ui->label_equation->setText(new_label_equation);
}

void CalcView::button_AC() {
  QString new_label_equation;
  new_label_equation = "";
  ui->label_equation->setText(new_label_equation);
  ui->label_equation_result->setText(new_label_equation);
  input_real = "";
  isClickedX = false;
  if (ui->widget->graph()) {
    ui->widget->graph(0)->data()->clear();
    x.clear();
    y.clear();
    Xbegin = ui->spinBox_X_min->value();
    Xend = ui->spinBox_X_max->value();
    Ybegin = ui->spinBox_Y_min->value();
    Yend = ui->spinBox_Y_max->value();
    ui->widget->xAxis->setRange(Xbegin, Xend);
    ui->widget->yAxis->setRange(Ybegin, Yend);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  }
}

void CalcView::button_equal() {
  QByteArray lab = input_real.toLocal8Bit();
  char *input_str = lab.data();
  double result;
  int code_calc = controller_->calculation(
      input_str, ui->doubleSpinBox_X->value(), &result);
  if (code_calc == 1) {
    QString result_q = QString::number(result, 'g', 8);
    ui->label_equation_result->setText(result_q);
  } else if (code_calc == 0) {
    ui->label_equation_result->setText("INVALID INPUT");
  } else if (code_calc == 2) {
    ui->label_equation_result->setText("NAN");
  }
}

void CalcView::button_delete() {
  if (!ui->label_equation->text().isEmpty()) {
    if (ui->label_equation->text().endsWith("x")) {
      isClickedX = false;
    }
    QString new_label_equation;
    bool endsArray3char = false;
    bool endsArray4char = false;
    QString array3char[] = {"cos(", "sin(", "log(", "tan(", "mod("};
    QString array4char[] = {"acos(", "asin(", "atan(", "sqrt("};
    for (int i = 0; i < 4; i++) {
      if (ui->label_equation->text().endsWith(array4char[i])) {
        endsArray4char = true;
        break;
      }
    }
    for (int i = 0; i < 5; i++) {
      if (ui->label_equation->text().endsWith(array3char[i])) {
        endsArray3char = true;
        break;
      }
    }
    if (endsArray4char) {
      new_label_equation = ui->label_equation->text().chopped(5);
      input_real = ui->label_equation->text().chopped(5);
    } else if (endsArray3char) {
      new_label_equation = ui->label_equation->text().chopped(4);
      input_real = ui->label_equation->text().chopped(4);
    } else if (ui->label_equation->text().endsWith("ln")) {
      new_label_equation = ui->label_equation->text().chopped(2);
      input_real = ui->label_equation->text().chopped(2);
    } else {
      new_label_equation = ui->label_equation->text().chopped(1);
      input_real = ui->label_equation->text().chopped(1);
    }
    ui->label_equation->setText(new_label_equation);
  }
}

void CalcView::on_pushButton_credit_count_clicked() {
  // Создание и заполнение таблицы результата расчета
  double sum = ui->doubleSpinBox_credit_sum->value();
  int com_time = ui->spinBox_credit_time->value();
  double percent = ui->doubleSpinBox_credit_percent->value();
  if (com_time != 0 && sum != 0.0 && percent != 0.0) {
    QDate sd = ui->date_credit_start->date();
    int start_month = sd.month();
    int start_year = sd.year();
    int current_month = cd.month();
    int current_year = cd.year();
    int spent_months =
        time_from_start(start_month, start_year, current_month, current_year);
    int remainder_time = ui->spinBox_credit_time->value() - spent_months;
    table = new QTableWidget;
    table->setRowCount(remainder_time + 2);
    table->setColumnCount(2);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setHorizontalHeaderLabels(QStringList() << "Месяц"
                                                   << "Сумма платежа");
    for (int i = 0; i < 2; i++) {
      table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    for (int j = 0; j < remainder_time; j++) {
      set_credit_date(current_month, current_year, &date_credit);
      QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(date_credit));
      table->setItem(j, 0, item);
      if (current_month != 12) {
        current_month++;
      } else {
        current_month = 1;
        current_year++;
      }
    }
    QTableWidgetItem *item_summury =
        new QTableWidgetItem(tr("%1").arg("Итого общая выплата:"));
    item_summury->setBackground(QColor(255, 128, 128));
    table->setItem(remainder_time, 0, item_summury);
    QTableWidgetItem *item_summury_over =
        new QTableWidgetItem(tr("%1").arg("Итого общая переплата:"));
    item_summury_over->setBackground(QColor(255, 128, 128));
    table->setItem(remainder_time + 1, 0, item_summury_over);
    // Расчет
    double overpay, common_pay;
    if (ui->radioButton_ann->isChecked()) {  // Аннуитентный
      double month_pay;
      controller_->credit_ann(sum, com_time, percent, &month_pay, &overpay,
                              &common_pay);
      for (int j = 0; j <= remainder_time; j++) {
        QTableWidgetItem *item_month_pay = new QTableWidgetItem;
        item_month_pay->setData(Qt::DisplayRole,
                                QVariant(QString::number(month_pay, 'f', 2)));
        table->setItem(j, 1, item_month_pay);
      }
    } else {  // Дифференциированный
      double remainder = sum;
      double *month_pay = (double *)malloc(sizeof(double) * com_time);
      int cur_m = 0;
      controller_->credit_diff(sum, com_time, percent, remainder, month_pay,
                               &overpay, cur_m);
      int tmp = com_time - remainder_time;
      for (int j = 0; j < remainder_time; j++) {
        QTableWidgetItem *item_month_pay = new QTableWidgetItem();
        item_month_pay->setData(
            Qt::DisplayRole, QVariant(QString::number(month_pay[tmp], 'f', 2)));
        table->setItem(j, 1, item_month_pay);
        tmp++;
      }
      common_pay = overpay + sum;
      free(month_pay);
    }
    QTableWidgetItem *item_summury_pay = new QTableWidgetItem();
    item_summury_pay->setData(Qt::DisplayRole,
                              QVariant(QString::number(common_pay, 'f', 2)));
    item_summury_pay->setBackground(QColor(255, 128, 128));
    table->setItem(remainder_time, 1, item_summury_pay);
    QTableWidgetItem *item_summury_overpay = new QTableWidgetItem();
    item_summury_overpay->setData(Qt::DisplayRole,
                                  QVariant(QString::number(overpay, 'f', 2)));
    item_summury_overpay->setBackground(QColor(255, 128, 128));
    table->setItem(remainder_time + 1, 1, item_summury_overpay);
    table->show();
  } else {
    if (sum == 0.0)
      QMessageBox::warning(this, " ", "Сумма кредита должна быть больше 0");
    if (com_time == 0)
      QMessageBox::warning(this, " ", "Срок кредита должен быть больше 0");
    if (percent == 0.0)
      QMessageBox::warning(this, " ",
                           "Процент по кредиту должен быть больше 0");
  }
}

int CalcView::time_from_start(int st_m, int st_y, int cr_m, int cr_y) {
  int months = 0;
  while ((st_y != cr_y)) {
    if (st_m != 12) {
      st_m++;
    } else {
      st_m = 1;
      st_y++;
    }
    months = months + 1;
  }
  while (st_m != cr_m) {
    st_m++;
    months++;
  }
  return months;
}

void CalcView::set_credit_date(int month, int year, QString *res) {
  QString year_tmp = QString::number(year);
  ;
  if (month == 1) {
    *res = "Январь";
  } else if (month == 2) {
    *res = "Февраль";
  } else if (month == 3) {
    *res = "Март";
  } else if (month == 4) {
    *res = "Апрель";
  } else if (month == 5) {
    *res = "Май";
  } else if (month == 6) {
    *res = "Июнь";
  } else if (month == 7) {
    *res = "Июль";
  } else if (month == 8) {
    *res = "Август";
  } else if (month == 9) {
    *res = "Сентябрь";
  } else if (month == 10) {
    *res = "Октябрь";
  } else if (month == 11) {
    *res = "Ноябрь";
  } else if (month == 12) {
    *res = "Декабрь";
  }
  *res = *res + " " + year_tmp;
}
}  // namespace s21
