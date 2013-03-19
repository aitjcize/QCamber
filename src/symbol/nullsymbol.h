#ifndef __NULLSYMBOL_H__
#define __NULLSYMBOL_H__

#include "symbol.h"

class NullSymbol: public Symbol {
public:

  NullSymbol(const QString& def, const Polarity& polarity,
      const AttribData& attrib);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  int m_ext;
};

#endif /* __NULLSYMBOL_H__ */
