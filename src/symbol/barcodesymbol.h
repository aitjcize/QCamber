/**
 * @file   barcodesymbol.h
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

#ifndef __BARCODESYMBOL_H__
#define __BARCODESYMBOL_H__

#include "symbol.h"

#include <QtWidgets>

#include "record.h"
#include "textsymbol.h"

class BarcodeSymbol: public TextSymbol {
public:
  BarcodeSymbol(const BarcodeRecord* rec);

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget);
  virtual QString infoText(void);
  virtual QString longInfoText(void);
  virtual QPainterPath painterPath(void);

private:
  QString m_barcode;
  QString m_e;
  qreal m_w, m_h;
  bool m_fasc;
  bool m_cs;
  bool m_bg;
  bool m_astr;
  BarcodeRecord::AstrPos m_astr_pos;
};

#endif /* __BARCODESYMBOL_H__ */
