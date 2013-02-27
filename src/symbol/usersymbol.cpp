#include "usersymbol.h"

#include <QtGui>
#include <QRegExp>

#include "context.h"

UserSymbol::UserSymbol(QString def, Polarity polarity):
  Symbol(def, def, polarity), m_def(def)
{
  static bool first = true;
  QString path = ctx.loader->featuresPath("symbols/" + def);

  FeaturesParser parser(path);
  m_ds = parser.parse();
  QList<Record*> records = m_ds->records();

  for (QList<Record*>::const_iterator it = records.begin();
      it != records.end(); ++it) {
    Record* rec = *it;
    rec->addToChild(this);
  }

  setHandlesChildEvents(true);
}

UserSymbol::~UserSymbol()
{
  delete m_ds;
}
