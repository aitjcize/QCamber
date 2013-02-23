#ifndef __NOTES_H__
#define __NOTES_H__

#include "symbol.h"

class Notes: public Symbol {
public:
  Notes(QString step, QString layer);
  virtual ~Notes();

  bool empty(void);

private:
  bool m_empty;
};

#endif /* __NOTES_H__ */
