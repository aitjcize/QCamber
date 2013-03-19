#include "usersymbol.h"

#include <QtGui>
#include <QRegExp>

#include "cachedparser.h"
#include "context.h"

UserSymbol::UserSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
  Symbol(def, def, polarity, attrib), m_def(def)
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
