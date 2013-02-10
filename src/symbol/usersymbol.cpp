#include "usersymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

//#define TEST_USER_SYMBOL

extern Context ctx;

UserSymbol::UserSymbol(QString def, Polarity polarity):
    Symbol(def, def, polarity), m_def(def)
{
  static bool first = true;
  QString path = ctx.loader->absPath("symbols/" + def + "/features");

#ifdef TEST_USER_SYMBOL
  if (first) {
    path = "features";
    first = false;
  }
#endif

  FeaturesParser parser(path);
  m_ds = parser.parse();
  m_records = m_ds->records();

  painterPath();
}

QPainterPath UserSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_cachedPath.setFillRule(Qt::WindingFill);

  for (QList<Record*>::const_iterator it = m_records.begin();
      it != m_records.end(); ++it) {
    Record* rec = *it;
    m_cachedPath.addPath(rec->painterPath());
  }

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
