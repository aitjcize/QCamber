#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "symbol.h"
#include "ovalsymbol.h"
#include "rectanglesymbol.h"
#include "roundsymbol.h"
#include "diamondsymbol.h"
#include "octagonsymbol.h"
#include "donutrsymbol.h"
#include "squaresymbol.h"
#include "surfacesymbol.h"
#include "arcsymbol.h"
#include "usersymbol.h"
#include "linesymbol.h"
#include "trianglesymbol.h"

#include <QRegExp>

class SymbolFactory {
public:
  static Symbol* create(QString def) {
    QRegExp rx("([a-z_+]+).*");
    if (!rx.exactMatch(def)) {
      return new UserSymbol(def);
    }

    QString prefix = rx.capturedTexts()[1];
    try {
      if (prefix == "r") {
        return new RoundSymbol(def);
      } else if (prefix == "s") {
        return new SquareSymbol(def);
      } else if (prefix == "rect") {
        return new RectangleSymbol(def);
      } else if (prefix == "oval") {
        return new OvalSymbol(def);
      } else if (prefix == "di") {
        return new DiamondSymbol(def);
      } else if (prefix == "oct") {
        return new OctagonSymbol(def);
      } else if (prefix == "donut_r") {
        return new DonutRSymbol(def);
      } else if (prefix == "tri") {
        return new TriangleSymbol(def);
      } else {
        return new UserSymbol(def);
      }
    } catch (InvalidSymbolException) {
      return new UserSymbol(def);
    }
  }
};

#endif /* __SYMBOL_FACTORY_H__ */
