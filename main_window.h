#pragma once

#include <QCalendarWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QTimeEdit>
#include <QTimer>

#include <memory>
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

  void ChangeNthActionState(int n);

  struct Action {
    Action(QDateTime date_time_, QString name_);
    enum class Status {
      kDefault,
      kDone,
      kOverdue
    };

    QDateTime date_time;
    QString name;
    Status status{Status::kDefault};

    QString ToString() const;

    bool IsPast() const;

    bool operator<(const Action& other) const;
  };

  struct Comparator {
    bool operator()(const std::unique_ptr<Action>& lhs,
                    const std::unique_ptr<Action>& rhs) const {
      return *lhs < *rhs;
    }
  };

  std::multiset<std::unique_ptr<Action>, Comparator> actions_;

  QTimer* timer_;

  QMediaPlayer* player_;

  QSize minimal_size_{1000, 500};
};
