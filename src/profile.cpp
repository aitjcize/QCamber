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
  qDebug() << profile->boundingRect();

  StructuredTextParser stephdr_parser(path.replace("profile", "stephdr"));
  StructuredTextDataStore* hds = stephdr_parser.parse();

  StructuredTextDataStore::BlockIterPair ip = hds->getBlocksByKey(
      "STEP-REPEAT");

#define GET(key) (QString::fromStdString(hds->get(key)))
  qreal x_datum = GET("X_DATUM").toDouble();
  qreal y_datum = GET("Y_DATUM").toDouble();
  qreal x_origin = GET("X_ORIGIN").toDouble();
  qreal y_origin = GET("Y_ORIGIN").toDouble();
#undef GET

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
