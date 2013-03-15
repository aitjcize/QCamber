#include "usersymbol.h"

#include <QtGui>
#include <QRegExp>

#include "context.h"

UserSymbol::UserSymbol(QString def, Polarity polarity):
  Symbol(def, def, polarity), m_def(def)
{
  QString path = ctx.loader->featuresPath("symbols/" + def);

  FeaturesParser parser(path);
  m_ds = parser.parse();

  for (QList<Record*>::const_iterator it = m_ds->records().begin();
      it != m_ds->records().end(); ++it) {
    Symbol* symbol = (*it)->createSymbol();
    addChild(symbol);
    m_symbols.append(symbol);
  }

  setHandlesChildEvents(true);
}

UserSymbol::~UserSymbol()
{
}
