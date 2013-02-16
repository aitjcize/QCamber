#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "symbol.h"
#include "record.h"
#include "structuredtextparser.h"

class Profile: public Symbol {
public:
  Profile(QString path);

private:
  StructuredTextDataStore* m_ds;
};

#endif /* __PROFILE_H__ */
