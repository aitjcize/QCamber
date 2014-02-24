/**
 * @file   arcsymbol.h
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

#ifndef __ARCSYMBOL_H__
#define __ARCSYMBOL_H__

#include "symbol.h"
#include "record.h"

class ArcSymbol: public Symbol {
public:
  ArcSymbol(const ArcRecord* rec);

  virtual QString infoText(void);
  virtual QString longInfoText(void);
  virtual QPainterPath painterPath(void);

private:
  qreal m_xs, m_ys;
  qreal m_xe, m_ye;
  qreal m_xc, m_yc;
  int m_sym_num;
  int m_dcode;
  bool m_cw;
  QString m_sym_name;
};

#endif /* __ARCSYMBOL_H__ */
