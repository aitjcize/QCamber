/**
 * @file   symbolfactory.h
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
  static Symbol* create(const QString& def, const Polarity& polarity,
      const AttribData& attrib) {
    QRegExp rx("([a-z_+]+).*");
    if (!rx.exactMatch(def)) {
      return new UserSymbol(def, polarity, attrib);
    }

    QString prefix = rx.capturedTexts()[1];
    try {
      if (prefix == "r") {
        return new RoundSymbol(def, polarity, attrib);
      } else if (prefix == "s") {
        return new SquareSymbol(def, polarity, attrib);
      } else if (prefix == "rect") {
        return new RectangleSymbol(def, polarity, attrib);
      } else if (prefix == "oval") {
        return new OvalSymbol(def, polarity, attrib);
      } else if (prefix == "di") {
        return new DiamondSymbol(def, polarity, attrib);
      } else if (prefix == "oct") {
        return new OctagonSymbol(def, polarity, attrib);
      } else if (prefix == "donut_r") {
        return new DonutRSymbol(def, polarity, attrib);
      } else if (prefix == "donut_s") {
        return new DonutSSymbol(def, polarity, attrib);
      } else if (prefix == "tri") {
        return new TriangleSymbol(def, polarity, attrib);
      } else if (prefix == "hex_l") {
        return new HorizontalHexagonSymbol(def, polarity, attrib);
      } else if (prefix == "hex_s") {
        return new VerticalHexagonSymbol(def, polarity, attrib);
      } else if (prefix == "bfr") {
        return new ButterflySymbol(def, polarity, attrib);
      } else if (prefix == "bfs") {
        return new SquareButterflySymbol(def, polarity, attrib);
      } else if (prefix == "oval_h") {
        return new HalfOvalSymbol(def, polarity, attrib);
      } else if (prefix == "ths") {
        return new RoundThermalSquareSymbol(def, polarity, attrib);
      } else if (prefix == "thr") {
        return new RoundThermalRoundSymbol(def, polarity, attrib);
      } else if (prefix == "s_ths") {
        return new SquareThermalSymbol(def, polarity, attrib);
      } else if (prefix == "s_tho") {
        return new SquareThermalOpenCornersSymbol(def, polarity, attrib);
      } else if (prefix == "sr_ths") {
        return new SquareRoundThermalSymbol(def, polarity, attrib);
      } else if (prefix == "rc_ths") {
        return new RectangularThermalSymbol(def, polarity, attrib);
      } else if (prefix == "rc_tho") {
        return new RectangularThermalOpenCornersSymbol(def, polarity, attrib);
      } else if (prefix == "el") {
        return new EllipseSymbol(def, polarity, attrib);
      } else if (prefix == "moire") {
        return new MoireSymbol(def, polarity, attrib);
      } else if (prefix == "hole") {
        return new HoleSymbol(def, polarity, attrib);
      } else if (prefix == "null") {
        return new NullSymbol(def, polarity, attrib);
      } else {
        return new UserSymbol(def, polarity, attrib);
      }
    } catch (InvalidSymbolException) {
      return new UserSymbol(def, polarity, attrib);
    }
  }
};

#endif /* __SYMBOL_FACTORY_H__ */
