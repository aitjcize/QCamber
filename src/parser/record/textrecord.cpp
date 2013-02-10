#include "record.h"

#include <QPainterPath>
#include <QDateTime>
#include <QString>

#include "featuresparser.h"
#include "symbolfactory.h"

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
  text = dynamicText(param[++i]);
  version = param[++i].toInt();

  symbol = new TextSymbol(this);
}

QString TextRecord::dynamicText(QString text)
{
  QString dynText = text;
  const QDate &Date = QDate::currentDate();
  const QTime &Time = QTime::currentTime();
  dynText.replace("$$date-ddmmyy", QString("").sprintf("%02d/%02d/%02d",
        Date.day(), Date.month(), Date.year()%100), Qt::CaseInsensitive);
  dynText.replace("$$date", QString("").sprintf("%02d/%02d/%02d",
        Date.month(), Date.day(), Date.year()%100), Qt::CaseInsensitive);
  dynText.replace("$$time", QString("").sprintf("%02d:%02d",
        Time.hour(), Time.minute()), Qt::CaseInsensitive);
  //TODO fill with correct text
  dynText.replace("$$job", "Current_Job", Qt::CaseInsensitive);
  dynText.replace("$$step", "Step", Qt::CaseInsensitive);
  dynText.replace("$$layer", "Layer", Qt::CaseInsensitive);

  dynText.replace("$$x_mm", QString("%1").arg(x*25.4), Qt::CaseInsensitive);
  dynText.replace("$$y_mm", QString("%1").arg(y*25.4), Qt::CaseInsensitive);

  dynText.replace("$$x", QString("%1").arg(x), Qt::CaseInsensitive);
  dynText.replace("$$y", QString("%1").arg(y), Qt::CaseInsensitive);
  //TODO attr_name

  return dynText;
}

QPainterPath TextRecord::painterPath(void)
{
  QPainterPath path = symbol->painterPath();

  qreal rad = (orient % 4) * 90;
  QMatrix mat;
  if (orient >= M_0) {
    mat.scale(-1, 1);
  }
  mat.rotate(rad);
  path = mat.map(path);

  path.translate(x, -y);
  return path;
}

void TextRecord::add(QGraphicsScene* scene)
{
  symbol->setPos(x, -y);
  scene->addItem(symbol);
}
