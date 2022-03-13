#include "main_window.h"

MainWindow::MainWindow() :
    QMainWindow(nullptr),
    widget_(new QWidget(this)),
    layout_(new QGridLayout()) {
  resize(minimal_size_);
  setMinimumSize(minimal_size_);

  SetupWidgets();

  setCentralWidget(widget_);

  ConnectWidgets();
}

void MainWindow::ConnectWidgets() {

}

void MainWindow::SetupWidgets() {
  actions_list_ = new QListWidget(widget_);

  label_ = new QLabel(widget_);
  label_->setText("Name: ");

  calendar_ = new QCalendarWidget(widget_);
  calendar_->setLocale(QLocale::English);
  calendar_->setFirstDayOfWeek(Qt::DayOfWeek::Monday);

  name_edit_ = new QLineEdit(widget_);

  time_edit_ = new QTimeEdit(widget_);

  add_button_ = new QPushButton(widget_);
  add_button_->setText("Add");

  layout_->addWidget(actions_list_, 0, 2, 4, 1);
  layout_->addWidget(label_, 0, 0);
  layout_->addWidget(name_edit_, 0, 1);
  layout_->addWidget(calendar_, 1, 0, 1, 2);
  layout_->addWidget(time_edit_, 2, 0, 1, 2);
  layout_->addWidget(add_button_, 3, 0, 1, 2);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 2);
  layout_->setColumnStretch(2, 3);

  widget_->setLayout(layout_);
}
