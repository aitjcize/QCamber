#ifndef __NOTES_PARSER_H__
#define __NOTES_PARSER_H__

#include "parser.h"
#include "record.h"

class NotesDataStore: public DataStore {
public:
  void putRecord(QStringList args);
  const QList<NoteRecord*>& records(void);

  virtual void dump(void);

private:
  QList<NoteRecord*> m_records;
};

class NotesParser: public Parser {
public:
  NotesParser(const QString& filename);
  virtual ~NotesParser();
  
  virtual NotesDataStore* parse(void);
};

#endif /* __NOTES_PARSER_H__ */
