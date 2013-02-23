#include "feature.h"

#include "context.h"
#include <typeinfo>

extern Context ctx;

Features::Features(QString path): Symbol("features")
{
  FeaturesParser parser(path);
  m_ds = parser.parse();

  for (QList<Record*>::const_iterator it = m_ds->records().begin();
      it != m_ds->records().end(); ++it) {
    Record* rec = *it;
    rec->addToChild(this);
  }
}

Features::~Features()
{
  delete m_ds;
}
