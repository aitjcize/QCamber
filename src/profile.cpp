#include "profile.h"
#include "context.h"

#include <QDebug>
#include <QTransform>

Profile::Profile(QString path): Symbol("profile")
{
  setHandlesChildEvents(true);

  m_profile = new Features(ctx.loader->absPath(path));
  addChild(m_profile);
  m_activeRect = m_profile->boundingRect();

  StructuredTextParser stephdr_parser(path.replace("profile", "stephdr"));
  StructuredTextDataStore* hds = stephdr_parser.parse();

  StructuredTextDataStore::BlockIterPair ip = hds->getBlocksByKey(
      "STEP-REPEAT");

  qreal top_active, bottom_active, left_active, right_active;

  try {
#define GET(key) (QString::fromStdString(hds->get(key)))
    m_x_datum = GET("X_DATUM").toDouble();
    m_y_datum = GET("Y_DATUM").toDouble();
    m_x_origin = GET("X_ORIGIN").toDouble();
    m_y_origin = GET("Y_ORIGIN").toDouble();

    top_active = GET("TOP_ACTIVE").toDouble();
    bottom_active = GET("BOTTOM_ACTIVE").toDouble();
    left_active = GET("LEFT_ACTIVE").toDouble();
    right_active = GET("RIGHT_ACTIVE").toDouble();
#undef GET

    m_activeRect.setX(m_activeRect.x() + left_active);
    m_activeRect.setY(m_activeRect.y() + top_active);
    m_activeRect.setWidth(m_activeRect.width() - right_active);
    m_activeRect.setHeight(m_activeRect.height() - bottom_active);
  } catch(StructuredTextDataStore::InvalidKeyException) {
    m_x_datum = m_y_datum = m_x_origin = m_y_origin = 0;
  }

  if (ip.first == ip.second) {
    m_activeRect = QRectF();
  }

  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
#define GET(key) (QString::fromStdString(it->second->get(key)))
    QString name = GET("NAME");
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
        QString path = QString("steps/%1/profile").arg(name.toLower());
        Profile* step = new Profile(ctx.loader->absPath(path));
        step->setPos(-step->x_datum() + x + dx * i,
                    -(-step->y_datum() + y + dy * j));
        step->rotate(angle);
        if (mirror) {
          QTransform trans;
          trans.scale(-1, 1);
          step->setTransform(trans);
        }
        addChild(step);
      }
    }

#undef GET
  }

  delete hds;
}

Profile::~Profile()
{
  delete m_profile;
}

qreal Profile::x_datum(void)
{
  return m_x_datum;
}

qreal Profile::y_datum(void)
{
  return m_y_datum;
}

void Profile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  QVector<qreal> dashes;
  dashes << 4 << 4;
  m_pen.setStyle(Qt::DashLine);
  m_pen.setDashPattern(dashes);
  m_brush = QBrush(Qt::transparent);

  Symbol::paint(painter, option, widget);
}

QPainterPath Profile::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_cachedPath.addRect(m_activeRect);

  m_valid = true;

  return m_cachedPath;
}

void Profile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mousePressEvent(event);
}

void Profile::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}
