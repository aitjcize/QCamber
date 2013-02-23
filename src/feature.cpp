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

  m_layerEffect = new LayerGraphicsEffect();
  setGraphicsEffect(m_layerEffect);
}

Features::~Features()
{
  delete m_ds;
}

void Features::setOpacity(qreal opacity)
{
  m_layerEffect->setOpacity(opacity);
}

void Features::setDoComposite(bool status)
{
  m_layerEffect->setDoComposite(status);
}
