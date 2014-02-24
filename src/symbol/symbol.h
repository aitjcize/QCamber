/**
 * @file   symbol.h
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

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdexcept>

#include <QBrush>
#include <QPen>
#include <QGraphicsItem>
#include <QMap>
#include <QPainter>
#include <QPainterPath>
#include <QString>

typedef QMap<QString, QString> AttribData;
typedef enum { P = 0, N } Polarity;
typedef enum { N_0 = 0, N_90, N_180, N_270, M_0, M_90, M_180, M_270 } Orient;

class InvalidSymbolException: public std::exception {
public:
  InvalidSymbolException(const char* msg): m_msg(msg) {}
  virtual const char* what() const throw() { return m_msg; }

private:
  const char* m_msg;
};

class Symbol: public virtual QGraphicsItem {
public:
  Symbol(QString name, QString pattern = QString(), Polarity polarity = P,
      AttribData attr = AttribData());
  virtual ~Symbol();

  QString name(void);
  virtual QString infoText(void);
  virtual QString longInfoText(void);
  AttribData attrib(void);

  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);
  virtual QPainterPath painterPath(void);

  void addChild(Symbol* symbol);
  void restoreColor(void);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);
  virtual QPainterPath shape() const {
    return const_cast<Symbol*>(this)->painterPath();
  };

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

protected:
  QString m_name;
  QString m_pattern;
  QRectF m_bounding;
  QPen m_pen;
  QBrush m_brush;
  QPen m_prevPen;
  QBrush m_prevBrush;
  Polarity m_polarity;
  bool m_selected;
  QList<Symbol*> m_symbols;
  AttribData m_attrib;
};

#endif /* __SYMBOL_H__ */
