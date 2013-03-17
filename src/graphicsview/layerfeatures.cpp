#include "layerfeatures.h"

#include <QDebug>

#include "cachedparser.h"
#include "context.h"

LayerFeatures::LayerFeatures(QString step, QString path, bool stepRepeat):
  Symbol("features"), m_step(step), m_path(path), m_scene(NULL),
  m_stepRepeatLoaded(false), m_showStepRepeat(stepRepeat)
{
  setHandlesChildEvents(true);

  m_ds = CachedFeaturesParser::parse(ctx.loader->absPath(path.arg(step)));

  for (QList<Record*>::const_iterator it = m_ds->records().begin();
      it != m_ds->records().end(); ++it) {
    m_symbols.append((*it)->createSymbol());
  }

  if (m_showStepRepeat) {
    loadStepAndRepeat();
  }
}

LayerFeatures::~LayerFeatures()
{
  for (int i = 0; i < m_repeats.size(); ++i) {
    delete m_repeats[i];
  }
}

void LayerFeatures::loadStepAndRepeat(void)
{
  QString path = ctx.loader->absPath(QString("steps/%1/stephdr").arg(m_step));
  StructuredTextDataStore* hds = CachedStructuredTextParser::parse(path);

  StructuredTextDataStore::BlockIterPair ip = hds->getBlocksByKey(
      "STEP-REPEAT");

  qreal top_active, bottom_active, left_active, right_active;

#define GET(key) (QString::fromStdString(hds->get(key)))
  try {
    m_x_datum = GET("X_DATUM").toDouble();
    m_y_datum = GET("Y_DATUM").toDouble();
    m_x_origin = GET("X_ORIGIN").toDouble();
    m_y_origin = GET("Y_ORIGIN").toDouble();

    top_active = GET("TOP_ACTIVE").toDouble();
    bottom_active = GET("BOTTOM_ACTIVE").toDouble();
    left_active = GET("LEFT_ACTIVE").toDouble();
    right_active = GET("RIGHT_ACTIVE").toDouble();

    m_activeRect.setX(m_activeRect.x() + left_active);
    m_activeRect.setY(m_activeRect.y() + top_active);
    m_activeRect.setWidth(m_activeRect.width() - right_active);
    m_activeRect.setHeight(m_activeRect.height() - bottom_active);
  } catch(StructuredTextDataStore::InvalidKeyException) {
  }

  if (ip.first == ip.second) {
    m_activeRect = QRectF();
  }
#undef GET

#define GET(key) (QString::fromStdString(it->second->get(key)))
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    QString name = GET("NAME").toLower();
    qreal x = GET("X").toDouble();
    qreal y = GET("Y").toDouble();
    qreal dx = GET("DX").toDouble();
    qreal dy = GET("DY").toDouble();
    int nx = GET("NX").toInt();
    int ny = GET("NY").toInt();
    qreal angle = GET("ANGLE").toDouble();
    bool mirror = (GET("MIRROR") == "YES");

    for (int i = 0; i < nx; ++i) {
      for (int j = 0; j < ny; ++j) {
        LayerFeatures* step = new LayerFeatures(name, m_path, true);
        step->m_virtualParent = this;
        step->setPos(QPointF(x + dx * i, -(y + dy * j)));

        QTransform trans;
        if (mirror) {
          trans.scale(-1, 1);
        }
        trans.rotate(angle);
        trans.translate(-step->x_datum(), step->y_datum());
        step->setTransform(trans);
        m_repeats.append(step);
      }
    }
  }
#undef GET

  if (m_scene) {
    for (QList<LayerFeatures*>::iterator it = m_repeats.begin();
        it != m_repeats.end(); ++it) {
      (*it)->addToScene(m_scene);
    }
  }

  m_stepRepeatLoaded = true;
}

QRectF LayerFeatures::boundingRect() const
{
  return QRectF();
}

void LayerFeatures::addToScene(QGraphicsScene* scene)
{
  m_scene = scene;

  for (int i = 0; i < m_symbols.size(); ++i) {
    scene->addItem(m_symbols[i]);
  }

  for (QList<LayerFeatures*>::iterator it = m_repeats.begin();
      it != m_repeats.end(); ++it) {
    (*it)->addToScene(scene);
    (*it)->setVisible(m_showStepRepeat);
  }
}

void LayerFeatures::setTransform(const QTransform& matrix, bool combine)
{
  for (int i = 0; i < m_symbols.size(); ++i) {
    Symbol* symbol = m_symbols[i];
    QTransform trans;
    QPointF o = transform().inverted().map(symbol->pos());
    trans.translate(-o.x(), -o.y());
    trans = matrix * trans;
    trans.translate(o.x(), o.y());
    symbol->setTransform(symbol->transform() * trans, false);
  }

  for (QList<LayerFeatures*>::iterator it = m_repeats.begin();
      it != m_repeats.end(); ++it) {
    QTransform trans;
    QPointF o = transform().inverted().map(pos());
    trans.translate(-o.x(), -o.y());
    trans = matrix * trans;
    trans.translate(o.x(), o.y());
    (*it)->setTransform(trans, combine);
  }

  QGraphicsItem::setTransform(matrix, true);
}

void LayerFeatures::setPos(QPointF pos)
{
  setPos(pos.x(), pos.y());
}

void LayerFeatures::setPos(qreal x, qreal y)
{
  QTransform trans = QTransform::fromTranslate(x, y);
  for (int i = 0; i < m_symbols.size(); ++i) {
    m_symbols[i]->setTransform(m_symbols[i]->transform() * trans, false);
  }

  for (QList<LayerFeatures*>::iterator it = m_repeats.begin();
      it != m_repeats.end(); ++it) {
    (*it)->setPos(x, y);
  }

  QGraphicsItem::setTransform(trans);
  QGraphicsItem::setPos(x, y);
}

void LayerFeatures::setVisible(bool status)
{
  for (int i = 0; i < m_symbols.size(); ++i) {
    m_symbols[i]->setVisible(status);
  }

  for (QList<LayerFeatures*>::iterator it = m_repeats.begin();
      it != m_repeats.end(); ++it) {
    (*it)->setVisible(status);
  }
}

void LayerFeatures::setShowStepRepeat(bool status)
{
  m_showStepRepeat = status;

  if (status && !m_stepRepeatLoaded) {
    loadStepAndRepeat();

    QList<QGraphicsItem*> items = m_scene->items();
    for (int i = 0; i < items.size(); ++i) {
      dynamic_cast<Symbol*>(items[i])->setPen(m_pen);
      dynamic_cast<Symbol*>(items[i])->setBrush(m_brush);
    }
  }

  for (QList<LayerFeatures*>::iterator it = m_repeats.begin();
      it != m_repeats.end(); ++it) {
    (*it)->setVisible(status);
  }
}

QTextEdit* LayerFeatures::symbolCount()
{
    QTextEdit *output = new QTextEdit;
    FeaturesDataStore::IDMapType nameMap;
    int total;
    total = 0;
    nameMap = m_ds->symbolNameMap();

    total += createSection(output,"Line",nameMap);
    total += createSection(output,"Pad",nameMap);
    total += createSection(output,"Arc",nameMap);
    total += createSection(output,"Surface",nameMap);
    total += createSection(output,"Text",nameMap);

    output->append("\n--------------------------------------");
    output->append(QString().sprintf("Total \t %20s \t %d"," ",total));
    output->setReadOnly(true);
    return output;
}

int LayerFeatures::createSection(QTextEdit *output,
            QString sectionTitle, FeaturesDataStore::IDMapType nameMap)
{
    FeaturesDataStore::CountMapType posCountMap,negCountMap;
    QString text;
    int local_total;
    local_total = 0;
    output->append(sectionTitle+
                   " List\n--------------------------------------");

    if(sectionTitle == "Line"){
        posCountMap = m_ds->posLineCountMap();
        negCountMap = m_ds->negLineCountMap();
    }else if(sectionTitle == "Pad"){
        posCountMap = m_ds->posPadCountMap();
        negCountMap = m_ds->negPadCountMap();
    }else if(sectionTitle == "Arc"){
        posCountMap = m_ds->posArcCountMap();
        negCountMap = m_ds->negArcCountMap();
    }else if(sectionTitle == "Surface"){
        text.sprintf("POS \t %20s \t %d"," ",
                     (local_total+=m_ds->posSurfaceCount()));
        output->append(text);
        text.sprintf("NEG \t %20s \t %d"," ",
                     (local_total+=m_ds->negSurfaceCount()));
        output->append(text);
        output->append(" ");
        return local_total;
    }else if(sectionTitle == "Text"){
        text.sprintf("POS \t %20s \t %d"," ",
                     (local_total+=m_ds->posTextCount()));
        output->append(text);
        text.sprintf("NEG \t %20s \t %d"," ",
                     (local_total+=m_ds->negTextCount()));
        output->append(text);
        output->append(" ");
        return local_total;
    }


    for(int i = 0;i < posCountMap.size();i++){
      if(posCountMap[i] != 0){
        text.sprintf("POS \t %20s \t %d",
                     nameMap[i].toAscii().data(),posCountMap[i]);
        output->append(text);
        local_total+=posCountMap[i];
      }
    }
    for(int i = 0;i < negCountMap.size();i++){
      if(negCountMap[i] != 0){
        text.sprintf("NEG \t %20s \t %d",
                     nameMap[i].toAscii().data(),negCountMap[i]);
        output->append(text);
        local_total+=negCountMap[i];
      }
    }
    output->append(text.sprintf("Total \t %20s \t %d","",local_total));
    output->append(" ");
    return local_total;
}
