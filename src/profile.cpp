#include "profile.h"
#include "feature.h"
#include "context.h"

#include <QDebug>

extern Context ctx;

Profile::Profile(QString path): Symbol("profile")
{
  Features* profile = new Features(ctx.loader->absPath(path));
  addToGroup(profile);
  addToSymbols(profile);
  m_edgeBounding = profile->boundingRect();

  StructuredTextParser stephdr_parser(path.replace("profile", "stephdr"));
  StructuredTextDataStore* hds = stephdr_parser.parse();

  StructuredTextDataStore::BlockIterPair ip = hds->getBlocksByKey(
      "STEP-REPEAT");

  qreal x_datum, y_datum, x_origin, y_origin, top_active, bottom_active,
        left_active, right_active;

  try {
#define GET(key) (QString::fromStdString(hds->get(key)))
    x_datum = GET("X_DATUM").toDouble();
    y_datum = GET("Y_DATUM").toDouble();
    x_origin = GET("X_ORIGIN").toDouble();
    y_origin = GET("Y_ORIGIN").toDouble();

    top_active = GET("TOP_ACTIVE").toDouble();
    bottom_active = GET("BOTTOM_ACTIVE").toDouble();
    left_active = GET("LEFT_ACTIVE").toDouble();
    right_active = GET("RIGHT_ACTIVE").toDouble();
#undef GET

    m_edgeBounding.setX(m_edgeBounding.x() + left_active);
    m_edgeBounding.setY(m_edgeBounding.y() + top_active);
    m_edgeBounding.setWidth(m_edgeBounding.width()-left_active-right_active);
    m_edgeBounding.setHeight(m_edgeBounding.height()-top_active-bottom_active);
  } catch(StructuredTextDataStore::InvalidKeyException) {
  }

  if (ip.first == ip.second) {
    m_edgeBounding = QRectF();
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
        step->setPos(x_datum + x+ dx * i, -(y_datum + y + dy * j));
        step->rotate(angle);
        addToGroup(step);
        addToSymbols(step);
      }
    }

#undef GET
  }
}

void Profile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  QVector<qreal> dashes;
  dashes << 4 << 4;
  m_pen.setStyle(Qt::DashLine);
  m_pen.setDashPattern(dashes);

  Symbol::paint(painter, option, widget);
}

QPainterPath Profile::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_cachedPath.addRect(m_edgeBounding);

  m_valid = true;

  return m_cachedPath;
}
