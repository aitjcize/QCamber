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
  /*
  if (first) {
    path = "features";
  }
  */
  FeaturesParser parser(path);
  m_ds = parser.parse();

  /*
  if (first) {
    first = false;
    ctx.cfds = m_ds;
  }
  */
  m_records = m_ds->records();

  painterPath();
}

QPainterPath UserSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_valid = true;

  m_cachedPath.setFillRule(Qt::WindingFill);

  for (QList<Record*>::const_iterator it = m_records.begin();
      it != m_records.end(); ++it) {
    Record* rec = *it;
    m_cachedPath.addPath(rec->painterPath());
  }

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
