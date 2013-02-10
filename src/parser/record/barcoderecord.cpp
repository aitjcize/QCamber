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
  text = dynamicText(param[++i]);

  symbol = new BarcodeSymbol(this);
}

QPainterPath BarcodeRecord::painterPath(void)
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

void BarcodeRecord::add(QGraphicsScene* scene)
{
  symbol->setPos(x, -y);
  scene->addItem(symbol);
}
