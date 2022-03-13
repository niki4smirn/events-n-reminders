#pragma once

#include <QCalendarWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTimeEdit>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 private:
  void ConnectWidgets();
  void SetupWidgets();

  QWidget* widget_;
  QGridLayout* layout_;

  QListWidget* actions_list_;
  QLabel* label_;
  QCalendarWidget* calendar_;
  QLineEdit* name_edit_;
  QTimeEdit* time_edit_;
  QPushButton* add_button_;

  QDate action_date_;
  QTime action_time_;
  QString action_name_;

  QSize minimal_size_{1000, 500};
};
