#include <QDebug>
#include <QPainter>
#include <cmath>
#include <QMatrix>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void LineRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  QString sym_name = ds->symbolNameMap()[sym_num];
  qreal radius = (qreal)sym_name.right(sym_name.length()-1).toDouble()/2/1000;
  QPointF p1s(xs, -ys), p1e(xe, -ye), po (ox, oy), p2s, p2e, ps, pe;
  p1s += po;p1e += po;
  ps = p2s = p1s;
  pe = p2e = p1e;

  QPointF delta;
  if(xs == xe){//vertical line
    delta.setX(1);
    delta.setY(0);
  }else{
    qreal m = (ye-ys)/(xe-xs);
    qreal angle = qAtan(m);
    delta.setX(-qSin(angle));
    delta.setY(-qCos(angle));
  }
  delta*= radius;
  p1s += delta;
  p1e += delta;
  p2s -= delta;
  p2e -= delta;

  path.moveTo(p1s);
  path.lineTo(p1e);
  path.lineTo(p2e);
  path.lineTo(p2s);
  path.lineTo(p1s);
  if(sym_name[0]=='r'){
    //QPointF pbr, ptl;
    //if(m>0){
    //}
    path.addEllipse(ps, radius, radius);
    path.addEllipse(pe, radius, radius);
  }
}

void LineRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new LineSymbol(this);
  scene->addItem(symbol);
}
