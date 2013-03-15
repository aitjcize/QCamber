#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "symbol.h"
#include "butterflysymbol.h"
#include "diamondsymbol.h"
#include "donutrsymbol.h"
#include "donutssymbol.h"
#include "ellipsesymbol.h"
#include "halfovalsymbol.h"
#include "holesymbol.h"
#include "horizontalhexagonsymbol.h"
#include "moiresymbol.h"
#include "nullsymbol.h"
#include "octagonsymbol.h"
#include "ovalsymbol.h"
#include "rectanglesymbol.h"
#include "rectangularthermalopencornerssymbol.h"
#include "rectangularthermalsymbol.h"
#include "roundsymbol.h"
#include "roundthermalroundsymbol.h"
#include "roundthermalsquaresymbol.h"
#include "squarebutterflysymbol.h"
#include "squareroundthermalsymbol.h"
#include "squaresymbol.h"
#include "squarethermalopencornerssymbol.h"
#include "squarethermalsymbol.h"
#include "trianglesymbol.h"
#include "usersymbol.h"
#include "verticalhexagonsymbol.h"

#include "surfacesymbol.h"
#include "arcsymbol.h"
#include "textsymbol.h"
#include "barcodesymbol.h"
#include "linesymbol.h"

#include "notesymbol.h"
#include "originsymbol.h"

#include <QRegExp>

class SymbolFactory {
public:
  static Symbol* create(QString def, Polarity polarity) {
    QRegExp rx("([a-z_+]+).*");
    if (!rx.exactMatch(def)) {
      return new UserSymbol(def, polarity);
    }

    QString prefix = rx.capturedTexts()[1];
    try {
      if (prefix == "r") {
        return new RoundSymbol(def, polarity);
      } else if (prefix == "s") {
        return new SquareSymbol(def, polarity);
      } else if (prefix == "rect") {
        return new RectangleSymbol(def, polarity);
      } else if (prefix == "oval") {
        return new OvalSymbol(def, polarity);
      } else if (prefix == "di") {
        return new DiamondSymbol(def, polarity);
      } else if (prefix == "oct") {
        return new OctagonSymbol(def, polarity);
      } else if (prefix == "donut_r") {
        return new DonutRSymbol(def, polarity);
      } else if (prefix == "donut_s") {
        return new DonutSSymbol(def, polarity);
      } else if (prefix == "tri") {
        return new TriangleSymbol(def, polarity);
      } else if (prefix == "hex_l") {
        return new HorizontalHexagonSymbol(def, polarity);
      } else if (prefix == "hex_s") {
        return new VerticalHexagonSymbol(def, polarity);
      } else if (prefix == "bfr") {
        return new ButterflySymbol(def, polarity);
      } else if (prefix == "bfs") {
        return new SquareButterflySymbol(def, polarity);
      } else if (prefix == "oval_h") {
        return new HalfOvalSymbol(def, polarity);
      } else if (prefix == "ths") {
        return new RoundThermalSquareSymbol(def, polarity);
      } else if (prefix == "thr") {
        return new RoundThermalRoundSymbol(def, polarity);
      } else if (prefix == "s_ths") {
        return new SquareThermalSymbol(def, polarity);
      } else if (prefix == "s_tho") {
        return new SquareThermalOpenCornersSymbol(def, polarity);
      } else if (prefix == "sr_ths") {
        return new SquareRoundThermalSymbol(def, polarity);
      } else if (prefix == "rc_ths") {
        return new RectangularThermalSymbol(def, polarity);
      } else if (prefix == "rc_tho") {
        return new RectangularThermalOpenCornersSymbol(def, polarity);
      } else if (prefix == "el") {
        return new EllipseSymbol(def, polarity);
      } else if (prefix == "moire") {
        return new MoireSymbol(def, polarity);
      } else if (prefix == "hole") {
        return new HoleSymbol(def, polarity);
      } else if (prefix == "null") {
        return new NullSymbol(def, polarity);
      } else {
        return new UserSymbol(def, polarity);
      }
    } catch (InvalidSymbolException) {
      return new UserSymbol(def, polarity);
    }
  }
};

#endif /* __SYMBOL_FACTORY_H__ */
