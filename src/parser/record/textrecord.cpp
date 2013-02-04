#include "record.h"

#include <QDebug>
#include <QDateTime>
#include <cmath>
#include <QString>
void TextRecord::addShape(QPainterPath& path)
{
}

QString TextRecord::dynamicText(QString text)
{
  QString dynText = text;
  const QDate &Date = QDate::currentDate();
  const QTime &Time = QTime::currentTime();
  dynText.replace("$$date-ddmmyy", QString("").sprintf("%02d/%02d/%02d", Date.day(), Date.month(), Date.year()%100));
  dynText.replace("$$date", QString("").sprintf("%02d/%02d/%02d", Date.month(), Date.day(), Date.year()%100));
  dynText.replace("$$time", QString("").sprintf("%02d:%02d", Time.hour(), Time.minute()));
  //TODO fill with correct text
  dynText.replace("$$job", "Current_Job");
  dynText.replace("$$step", "Step");
  dynText.replace("$$layer", "Layer");


  dynText.replace("$$x_mm", QString("%1").arg(x*25.4));
  dynText.replace("$$y_mm", QString("%1").arg(y*25.4));

  dynText.replace("$$x", QString("%1").arg(x));
  dynText.replace("$$y", QString("%1").arg(y));
  //TODO attr_name
  return dynText;
}
