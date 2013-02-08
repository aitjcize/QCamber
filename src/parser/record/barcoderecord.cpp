#include "record.h"

#include <QPainterPath>

#include "featuresparser.h"
#include "symbolfactory.h"

BarcodeRecord::BarcodeRecord(FeaturesDataStore* ds, const QStringList& param):
  TextRecord(ds, QStringList())
{
  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  barcode = param[++i];
  font = param[++i];
  polarity = (param[++i] == "P")? P: N;
  orient = (Orient)param[++i].toInt();
  e = param[++i];
  w = param[++i].toDouble();
  h = param[++i].toDouble();
  fasc = (param[++i] == "Y");
  cs = (param[++i] == "Y");
  bg = (param[++i] == "Y");
  astr = (param[++i] == "Y");
  astr_pos = (param[++i] == "T")? BarcodeRecord::T : BarcodeRecord::B;
  text = "";
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
}

QPainterPath BarcodeRecord::painterPath(void)
{
}

void BarcodeRecord::add(QGraphicsScene* scene)
{
}
