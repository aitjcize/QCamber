#include "usersymbol.h"

#include <QtGui>
#include <QRegExp>

#include "cachedparser.h"
#include "context.h"

UserSymbol::UserSymbol(QString def, Polarity polarity):
  Symbol(def, def, polarity), m_def(def)
{
  QString path = ctx.loader->featuresPath("symbols/" + def);
  FeaturesDataStore* ds = CachedFeaturesParser::parse(path);

  for (QList<Record*>::const_iterator it = ds->records().begin();
      it != ds->records().end(); ++it) {
    Symbol* symbol = (*it)->createSymbol();
    addChild(symbol);
    m_symbols.append(symbol);
  }

  setHandlesChildEvents(true);
}

UserSymbol::~UserSymbol()
{
}
