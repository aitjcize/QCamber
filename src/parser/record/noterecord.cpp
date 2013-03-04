#include "record.h"

#include "notesparser.h"
#include "notesymbol.h"
#include "symbolfactory.h"

NoteRecord::NoteRecord(NotesDataStore* ds, const QStringList& param):
  Record(ds)
{
  int i = 0;
  timestamp = param[i++].toInt();
  user = param[i++];
  x = param[i++].toDouble();
  y = param[i++].toDouble();
  text = QString(param[param.size() - 1]).replace("\\n", "\n").trimmed();

  symbol = new NoteSymbol(this);
}

void NoteRecord::prepare(void)
{
  symbol->setPos(x, -y);
}
