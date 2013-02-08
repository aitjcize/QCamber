#include "record.h"

#include <QPainterPath>
#include <QDateTime>
#include <QString>

#include "featuresparser.h"
#include "symbolfactory.h"
#include "textsymbol.h"

TextRecord::TextRecord(FeaturesDataStore* ds, const QStringList& param):
  Record(ds)
{
  if (param.empty()) {
    return;
  }

  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  font = param[++i];
  polarity = (param[++i] == "P")? P: N;
  orient = (Orient)param[++i].toInt();
  xsize = param[++i].toDouble();
  ysize = param[++i].toDouble();
  width_factor = param[++i].toDouble();
  text = param[++i];
  /*
  int ends = -1;
  while(ends!=1){
    QString str(param[++i]);
    if(!ends)
      text += " ";
    else
      str.replace(QRegExp("^'"), "");
    str.replace("\\\\", _DOUBLE_SLASHES_);
    if(str.endsWith("\\'"))
        ends = 0;
    else if (str.endsWith("'"))
        ends = 1;
    else
        ends = 0;
    if(ends)
        str.replace(QRegExp("'$"), "");
    str.replace("\\'", "'");
    str.replace(_DOUBLE_SLASHES_, "\\");
    text += str;
  };
  */

  version = param[++i].toInt();

  symbol = new TextSymbol(this);
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

void TextRecord::add(QGraphicsScene* scene)
{
  scene->addItem(symbol);
}
