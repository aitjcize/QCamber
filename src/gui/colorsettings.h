#ifndef COLORSETTINGS_H
#define COLORSETTINGS_H

#include <QDialog>
#include "config.h"
#include "mylabel.h"
#include "QSignalMapper"
#include "QList"
//extern Config cfg("config.ini");

#define COLOR_NUMBER 6

namespace Ui {
class ColorSettings;
}

class ColorSettings : public QDialog
{
  Q_OBJECT
  
public:
  explicit ColorSettings(QWidget *parent = 0);
  ~ColorSettings();
signals:
  void selected();
private slots:
  QColor openSelector(const QString color_config);
  void on_buttonBox_accepted();

private:
  Ui::ColorSettings *ui;
  QSignalMapper *colorSignalMapper;
  QList<myLabel*> label_list;
};

#endif // COLORSETTINGS_H
