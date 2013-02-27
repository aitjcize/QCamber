#ifndef __SETTINGSDIALOG_H__
#define __SETTINGSDIALOG_H__

#include <QDialog>
#include <QSignalMapper>
#include <QToolButton>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = 0);
  ~SettingsDialog();

  void updateColorToolButtonColor(QToolButton* but);

  void accept(void);

public slots:
  void chooseColor(QWidget* widget);

private:
  Ui::SettingsDialog *ui;
  QSignalMapper* m_sigMapper;
};

#endif // __SETTINGSDIALOG_H__
