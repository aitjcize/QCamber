#include "notesparser.h"

#include <QtCore>

void NotesDataStore::putRecord(QStringList args)
{
  m_records.append(new NoteRecord(this, args));
}

const QList<NoteRecord*>& NotesDataStore::records(void)
{
  return m_records;
}

void NotesDataStore::dump(void)
{
}

NotesParser::NotesParser(const QString& filename): Parser(filename)
{
}

NotesParser::~NotesParser()
{
}
  
NotesDataStore* NotesParser::parse(void)
{
  QFile file(m_fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  NotesDataStore* ds = new NotesDataStore;
  while (!file.atEnd()) {
    QString line = file.readLine();
    ds->putRecord(line.split(","));
  }

  return ds;
}
