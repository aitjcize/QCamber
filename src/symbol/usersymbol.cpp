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
  QString path = ctx.loader->featuresPath("symbols/" + def);

#ifdef TEST_USER_SYMBOL
  if (first) {
    path = "features";
    first = false;
  }
#endif

  FeaturesParser parser(path);
  m_ds = parser.parse();
  m_records = m_ds->records();

  for (QList<Record*>::const_iterator it = m_records.begin();
      it != m_records.end(); ++it) {
    Record* rec = *it;
    rec->addToChild(this);
  }

  setHandlesChildEvents(true);
}
