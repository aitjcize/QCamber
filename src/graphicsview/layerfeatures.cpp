#include "layerfeatures.h"

#include <QDebug>

#include "cachedparser.h"
#include "context.h"

LayerFeatures::LayerFeatures(QString step, QString path, bool stepRepeat):
  Symbol("features"), m_step(step), m_path(path), m_scene(NULL),
  m_stepRepeatLoaded(false), m_showStepRepeat(stepRepeat),
  m_reportModel(NULL)
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

  if (m_reportModel) {
    delete m_reportModel;
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

QStandardItemModel* LayerFeatures::reportModel(void)
{
  if (m_reportModel) {
    return m_reportModel;
  }

  m_reportModel = new QStandardItemModel;
  m_reportModel->setColumnCount(2);
  m_reportModel->setHeaderData(0, Qt::Horizontal, "name");
  m_reportModel->setHeaderData(1, Qt::Horizontal, "count");

  const FeaturesDataStore::IDMapType& nameMap = m_ds->symbolNameMap();
  FeaturesDataStore::CountMapType countMap;
  QStandardItem* root = m_reportModel->invisibleRootItem();
  QStandardItem* node = NULL;

  unsigned total = 0, n_nodes = 0;

  // Lines
  node = APPEND_ROW(root, "Lines", "");
  total = 0;

  countMap = m_ds->posLineCountMap();
  for (FeaturesDataStore::CountMapType::iterator it = countMap.begin();
      it != countMap.end(); ++it) {
    APPEND_ROW(node, nameMap[it.key()] + " POS", QString::number(it.value()));
    total += it.value();
  }
  countMap = m_ds->negLineCountMap();
  for (FeaturesDataStore::CountMapType::iterator it = countMap.begin();
      it != countMap.end(); ++it) {
    APPEND_ROW(node, nameMap[it.key()] + " NEG", QString::number(it.value()));
    total += it.value();
  }
  root->child(n_nodes++, 1)->setText(QString::number(total));

  // Pad
  node = APPEND_ROW(root, "Pad", "");
  total = 0;

  countMap = m_ds->posPadCountMap();
  for (FeaturesDataStore::CountMapType::iterator it = countMap.begin();
      it != countMap.end(); ++it) {
    APPEND_ROW(node, nameMap[it.key()] + " POS", QString::number(it.value()));
    total += it.value();
  }
  countMap = m_ds->negPadCountMap();
  for (FeaturesDataStore::CountMapType::iterator it = countMap.begin();
      it != countMap.end(); ++it) {
    APPEND_ROW(node, nameMap[it.key()] + " NEG", QString::number(it.value()));
    total += it.value();
  }
  root->child(n_nodes++, 1)->setText(QString::number(total));

  // Arc
  node = APPEND_ROW(root, "Arc", "");
  total = 0;

  countMap = m_ds->posPadCountMap();
  for (FeaturesDataStore::CountMapType::iterator it = countMap.begin();
      it != countMap.end(); ++it) {
    APPEND_ROW(node, nameMap[it.key()] + " POS", QString::number(it.value()));
    total += it.value();
  }
  countMap = m_ds->negPadCountMap();
  for (FeaturesDataStore::CountMapType::iterator it = countMap.begin();
      it != countMap.end(); ++it) {
    APPEND_ROW(node, nameMap[it.key()] + " NEG", QString::number(it.value()));
    total += it.value();
  }
  root->child(n_nodes++, 1)->setText(QString::number(total));

  // Surface
  node = APPEND_ROW(root, "Surface", "");
  APPEND_ROW(node, "POS", QString::number(m_ds->posSurfaceCount()));
  APPEND_ROW(node, "NEG", QString::number(m_ds->negSurfaceCount()));
  root->child(n_nodes++, 1)->setText(QString::number(
        m_ds->posSurfaceCount() + m_ds->negSurfaceCount()));

  // Text
  node = APPEND_ROW(root, "Text", "");
  APPEND_ROW(node, "POS", QString::number(m_ds->posTextCount()));
  APPEND_ROW(node, "NEG", QString::number(m_ds->negTextCount()));
  root->child(n_nodes++, 1)->setText(QString::number(
        m_ds->posTextCount() + m_ds->negTextCount()));

  // Barcode
  node = APPEND_ROW(root, "Barcode", "");
  APPEND_ROW(node, "POS", QString::number(m_ds->posBarcodeCount()));
  APPEND_ROW(node, "NEG", QString::number(m_ds->negBarcodeCount()));
  root->child(n_nodes++, 1)->setText(QString::number(
        m_ds->posBarcodeCount() + m_ds->negBarcodeCount()));

  return m_reportModel;
}
