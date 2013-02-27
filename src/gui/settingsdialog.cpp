#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QtGui>

#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
  ui->setupUi(this);

  m_sigMapper = new QSignalMapper;;

#define MAP(mapper, name) \
  (mapper)->setMapping(ui->name, ui->name); \
  connect(ui->name, SIGNAL(clicked()), mapper, SLOT(map())); \
  updateColorToolButtonColor(ui->name);

  MAP(m_sigMapper, colorBG);
  MAP(m_sigMapper, colorC1);
  MAP(m_sigMapper, colorC2);
  MAP(m_sigMapper, colorC3);
  MAP(m_sigMapper, colorC4);
  MAP(m_sigMapper, colorC5);
  MAP(m_sigMapper, colorC6);
#undef MAP

  connect(m_sigMapper, SIGNAL(mapped(QWidget*)),
      this, SLOT(chooseColor(QWidget*)));
}

SettingsDialog::~SettingsDialog()
{
  delete ui;
}

void SettingsDialog::accept(void)
{
  hide();
}

void SettingsDialog::chooseColor(QWidget* widget)
{
  QToolButton* but = qobject_cast<QToolButton*>(widget);
  QString colorName = but->text();
  QColorDialog selector;
  QColor color(SETTINGS->get("Color", colorName).toString());
  color = selector.getColor(color);
  if (color.isValid()) {
    SETTINGS->set("Color", colorName, color.name());
    updateColorToolButtonColor(but);
  }
}

void SettingsDialog::updateColorToolButtonColor(QToolButton* but)
{
  QString tmpl("QToolButton { background-color: %1; color: %2; }");
  QColor fg(SETTINGS->get("Color", but->text()).toString());
  QColor bg(255 - fg.red(), 255 - fg.green(), 255 - fg.blue(), 25);
  but->setStyleSheet(tmpl.arg(fg.name()).arg(bg.name()));
}
