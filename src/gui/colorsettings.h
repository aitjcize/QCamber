#ifndef COLORSETTINGS_H
#define COLORSETTINGS_H

#include <QDialog>
#include "config.h"
#include "clickablelabel.h"
#include "QSignalMapper"
#include "QList"
//extern Config cfg("config.ini");

#define N_COLOR 6

namespace Ui {
class ColorSettings;
}

class ColorSettings : public QDialog
{
  Q_OBJECT

public:
  explicit ColorSettings(QWidget *parent = 0);
  ~ColorSettings();

private slots:
  QColor openSelector(int index);

private:
  Ui::ColorSettings *ui;
  QSignalMapper *m_colorSignalMapper;
  QList<ClickableLabel*> m_labels;
};

#endif // COLORSETTINGS_H
