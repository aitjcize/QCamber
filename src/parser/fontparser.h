#ifndef __FONT_PARSER_H__
#define __FONT_PARSER_H__

#include "parser.h"
#include "record.h"

class FontDataStore: public DataStore {
public:
  void putXSize(const QStringList& param);
  void putYSize(const QStringList& param);
  void putOffset(const QStringList& param);
  void charStart(const QStringList& param);
  void charLineData(const QStringList& param);
  void charEnd(void);

  qreal offset(void);
  qreal xsize(void);
  qreal ysize(void);
  CharRecord* charRecord(const char tchar);

  virtual void dump(void);

private:
  qreal m_xsize, m_ysize;
  qreal m_offset;
  QMap<char, CharRecord*> m_records;

  CharRecord* m_currentChar;
};

class FontParser: public Parser {
public:
  FontParser(const QString& filename);
  virtual ~FontParser();
  
  virtual FontDataStore* parse(void);
};

#endif /* __FONT_PARSER_H__ */
