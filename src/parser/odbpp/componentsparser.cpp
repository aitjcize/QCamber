#include "componentsparser.h"
#include "packageparser.h"
#include "cachedparser.h"
#include "record.h"
#include "context.h"

#include <QtCore>
#include <QtDebug>
#include <QRegularExpression>

ComponentsParser::ComponentsParser(const QString& filename) : Parser(filename)
{
}

ComponentsParser::~ComponentsParser()
{
}

ComponentsDataStore* ComponentsParser::parse(void)
{
  QFile file(m_fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  ComponentsDataStore* ds = new ComponentsDataStore;

  QRegularExpression rx("^.*/steps/([^/]+)/layers/.*");
  QRegularExpressionMatch m = rx.match(m_fileName);
  if (m.hasMatch()) {
    QString step = m.captured(1);
    ds->setStepName(step);
    QString pkgPath = ctx.loader->absPath(QString("steps/%1/eda/data").arg(step));
    ds->setPackages(CachedPackageParser::parse(pkgPath));
  }

  while (!file.atEnd()) {
    QString line = file.readLine().trimmed();
    if (line.startsWith("CMP")) {
      QString record = line.section(';',0,0).trimmed();
      QStringList p = record.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      ComponentRecord* rec = new ComponentRecord(ds, p);
      ds->putRecord(rec);
    }
  }
  return ds;
}
