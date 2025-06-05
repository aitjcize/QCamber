#include "packageparser.h"

#include <QtCore>
#include <QRegularExpression>
#include <QtDebug>

PackageParser::PackageParser(const QString& filename) : Parser(filename)
{
}

PackageParser::~PackageParser()
{
}

PackageDataStore* PackageParser::parse(void)
{
  QFile file(m_fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  PackageDataStore* ds = new PackageDataStore;
  int index = -1;
  PackageDataStore::PackageInfo info;
  PackageDataStore::PackageInfo::PinInfo currentPin;
  bool inPin = false;
  QPainterPath path;

  auto finalizePath = [&]() {
    if (path.elementCount() == 0)
      return;
    if (inPin) {
      currentPin.path.addPath(path);
    } else {
      info.bodyPath.addPath(path);
    }
    path = QPainterPath();
  };

  auto finalizePin = [&]() {
    if (inPin) {
      finalizePath();
      info.pins.append(currentPin);
      inPin = false;
    }
  };

  while (!file.atEnd()) {
    QString line = file.readLine().trimmed();

    if (line.startsWith("PKG")) {
      finalizePin();
      if (index >= 0)
        ds->addPackage(index, info);

      ++index;
      info = PackageDataStore::PackageInfo();
      info.bodyPath = QPainterPath();
      info.pins.clear();
      QString record = line.section(';', 0, 0).trimmed();
      QStringList p = record.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (p.size() >= 7) {
        info.name = p[1];
        info.pitch = p[2].toDouble();
        info.xmin = p[3].toDouble();
        info.ymin = p[4].toDouble();
        info.xmax = p[5].toDouble();
        info.ymax = p[6].toDouble();
      }
    } else if (line.startsWith("PIN")) {
      finalizePin();
      QString record = line.section(';', 0, 0).trimmed();
      QStringList p = record.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (p.size() >= 5) {
        currentPin = PackageDataStore::PackageInfo::PinInfo();
        currentPin.number = p[1].toInt();
        currentPin.x = p[3].toDouble();
        currentPin.y = p[4].toDouble();
        currentPin.path = QPainterPath();
        inPin = true;
      }
    } else if (line.startsWith("CT")) {
      finalizePath();
    } else if (line.startsWith("OB")) {
      QStringList p = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (p.size() >= 3) {
        qreal x = p[1].toDouble();
        qreal y = p[2].toDouble();
        path.moveTo(x, -y);
      }
    } else if (line.startsWith("OS")) {
      QStringList p = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (p.size() >= 3) {
        qreal x = p[1].toDouble();
        qreal y = p[2].toDouble();
        path.lineTo(x, -y);
      }
    } else if (line.startsWith("OE")) {
      path.closeSubpath();
    } else if (line.startsWith("CE")) {
      finalizePath();
    } else if (line.startsWith("RC")) {
      QStringList p = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (p.size() >= 5) {
        qreal x = p[1].toDouble();
        qreal y = p[2].toDouble();
        qreal w = p[3].toDouble();
        qreal h = p[4].toDouble();
        QPainterPath rcPath;
        rcPath.addRect(QRectF(x, -y - h, w, h));
        if (inPin)
          currentPin.path.addPath(rcPath);
        else
          info.bodyPath.addPath(rcPath);
      }
    } else if (line.startsWith("CR")) {
      QStringList p = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (p.size() >= 4) {
        qreal x = p[1].toDouble();
        qreal y = p[2].toDouble();
        qreal r = p[3].toDouble();
        QPainterPath crPath;
        crPath.addEllipse(QPointF(x, -y), r, r);
        if (inPin)
          currentPin.path.addPath(crPath);
        else
          info.bodyPath.addPath(crPath);
      }
    }
  }

  finalizePin();
  if (index >= 0)
    ds->addPackage(index, info);

  return ds;
}
