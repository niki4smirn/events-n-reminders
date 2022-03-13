#include "main_window.h"

#include <QMessageBox>

static const QString kEasterEggName = "Easter egg :)";

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
  connect(name_edit_,
          &QLineEdit::editingFinished, [&]() {
        UpdateActionName(name_edit_->text());
      });

  connect(calendar_,
          &QCalendarWidget::clicked, [&](const QDate& date) {
        UpdateActionDate(date);
        UpdateActionTime(time_edit_->time());
      });

  connect(time_edit_,
          &QTimeEdit::timeChanged, [&](const QTime& time) {
        UpdateActionTime(time);
      });

  connect(add_button_,
          &QPushButton::clicked, [&]() {
        if (action_name_.has_value() &&
            action_date_.has_value() &&
            action_time_.has_value()) {
          actions_.insert({{action_date_.value(), action_time_.value()},
                           action_name_.value()});
          UpdateActionsList();
        } else {
          QMessageBox msgBox;
          msgBox.setText("Check action info correctness (you cannot add nameless or past action).");
          msgBox.exec();
        }
      });
}

void MainWindow::SetupWidgets() {
  actions_list_ = new QListWidget(widget_);

  label_ = new QLabel(widget_);
  label_->setText("Name: ");

  calendar_ = new QCalendarWidget(widget_);
  calendar_->setLocale(QLocale::English);
  calendar_->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
  action_date_ = calendar_->selectedDate();

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

void MainWindow::UpdateActionsList() {
  actions_list_->clear();
  for (const auto& action : actions_) {
    auto* new_item = new QListWidgetItem(action.ToString(), actions_list_);
    new_item->setTextAlignment(Qt::AlignCenter);
    actions_list_->addItem(new_item);
  }
}

void MainWindow::UpdateActionName(const QString& new_name) {
  if (!new_name.isEmpty()) {
    if (new_name == kEasterEggName) {
      label_->setText("Oh... How did you know?");
    }
    action_name_ = new_name;
  } else {
    action_name_.reset();
  }
}

void MainWindow::UpdateActionDate(const QDate& date) {
  if (date >= QDateTime::currentDateTime().date()) {
    action_date_ = date;
  } else {
    action_date_.reset();
  }
}

void MainWindow::UpdateActionTime(const QTime& time) {
  if (action_date_.has_value() &&
      action_date_.value() == QDateTime::currentDateTime().date() &&
      time < QDateTime::currentDateTime().time()) {
    action_time_.reset();
  } else {
    action_time_ = time;
  }
}

bool MainWindow::Action::operator<(const MainWindow::Action& other) const {
  return date_time < other.date_time;
}

QString MainWindow::Action::ToString() const {
  return name + " (" + date_time.toString("hh:mm dd.MM.yyyy") + ")";
}
