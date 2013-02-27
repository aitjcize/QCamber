#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
  ui->setupUi(this);
  ui->precision->setValue(
      Settings::instance()->get("Display", "Precision").toInt());
}

SettingsDialog::~SettingsDialog()
{
  delete ui;
}

void SettingsDialog::accept(void)
{
  Settings::instance()->set("Display", "Precision", ui->precision->value());
  hide();
}
