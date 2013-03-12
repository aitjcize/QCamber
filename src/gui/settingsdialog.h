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

  void accept(void);

public slots:
  void chooseColor(QWidget* widget);
  void on_loadSystemColor_clicked(void);
  void on_loadUserColor_clicked(void);
  void on_saveUserColor_clicked(void);

protected:
  void reloadColorToolButoonColor(void);
  void updateColorToolButtonColor(QToolButton* but);

private:
  Ui::SettingsDialog *ui;
  QSignalMapper* m_sigMapper;
};

#endif // __SETTINGSDIALOG_H__
