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

#include <optional>
#include <set>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 private:
  void ConnectWidgets();
  void SetupWidgets();
  void UpdateActionsList();

  void UpdateActionName(const QString& new_name);
  void UpdateActionDate(const QDate& date);
  void UpdateActionTime(const QTime& time);

  QWidget* widget_;
  QGridLayout* layout_;

  QListWidget* actions_list_;
  QLabel* label_;
  QCalendarWidget* calendar_;
  QLineEdit* name_edit_;
  QTimeEdit* time_edit_;
  QPushButton* add_button_;

  std::optional<QDate> action_date_;
  std::optional<QTime> action_time_;
  std::optional<QString> action_name_;

  struct Action {
    QDateTime date_time;
    QString name;

    QString ToString() const;

    bool operator<(const Action& other) const;
  };

  std::multiset<Action> actions_;

  QSize minimal_size_{1000, 500};
};
