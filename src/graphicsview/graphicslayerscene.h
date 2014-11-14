/**
 * @file   graphicslayerscene.h
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

#ifndef __GRAPHICSLAYERSCENE__
#define __GRAPHICSLAYERSCENE__

#include <QGraphicsScene>
#include <QList>

#include "symbol.h"

class GraphicsLayer;

class GraphicsLayerScene: public QGraphicsScene {
  Q_OBJECT

public:
  GraphicsLayerScene(QObject* parent = 0);
  virtual ~GraphicsLayerScene();

  void setGraphicsLayer(GraphicsLayer* layer);
  bool highlight(void);
  void setHighlightEnabled(bool status);
  void clearHighlight(void);

  void updateSelection(Symbol* symbol);

signals:
  void featureSelected(Symbol*);

private:
  GraphicsLayer* m_graphicsLayer;
  bool m_highlight;
  QList<Symbol*> m_selectedSymbols;
};

#endif /* __GRAPHICSLAYERSCENE__ */
