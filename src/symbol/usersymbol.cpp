#include "usersymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

extern Context ctx;

UserSymbol::UserSymbol(QString def):
    Symbol(def, def), m_def(def)
{
  static bool first = true;
  QString path = ctx.loader->absPath("symbols/" + def + "/features");
  if (first) {
    path = "features";
  }
  FeaturesParser parser(path);
  m_ds = parser.parse();

  if (first) {
    first = false;
    ctx.cfds = m_ds;
  }
  m_records = m_ds->records();
}

QRectF UserSymbol::boundingRect() const
{
  return bounding;
}

void UserSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  QPainterPath path;
  addShape(path);

  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawPath(path);

  bounding = path.boundingRect();
}

void UserSymbol::addShape(QPainterPath& path)
{
  for (QList<Record*>::const_iterator it = m_records.begin();
      it != m_records.end(); ++it) {
    Record* rec = *it;
    rec->addShape(path, pos().x(), -pos().y());
  }
}
