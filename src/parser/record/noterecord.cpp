#include "record.h"

#include "notesparser.h"
#include "notesymbol.h"
#include "symbolfactory.h"

NoteRecord::NoteRecord(NotesDataStore* ds, const QStringList& param):
  Record(ds, AttribData())
{
  int i = 0;
  timestamp = param[i++].toInt();
  user = param[i++];
  x = param[i++].toDouble();
  y = param[i++].toDouble();
  text = QString(param[param.size() - 1]).replace("\\n", "\n").trimmed();
}

Symbol* NoteRecord::createSymbol(void) const
{
  Symbol* symbol = new NoteSymbol(this);
  symbol->setPos(x, -y);
  return symbol;
}
