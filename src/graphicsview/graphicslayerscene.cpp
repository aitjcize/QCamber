/**
 * @file   graphicslayerscene.cpp
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

#include "graphicslayerscene.h"

#include <QtWidgets>

#include "graphicslayer.h"

GraphicsLayerScene::GraphicsLayerScene(QObject* parent):
  QGraphicsScene(parent), m_highlight(false)
{
  setItemIndexMethod(NoIndex);
}

GraphicsLayerScene::~GraphicsLayerScene()
{
}

void GraphicsLayerScene::setGraphicsLayer(GraphicsLayer* layer)
{
  m_graphicsLayer = layer;
}

bool GraphicsLayerScene::highlight(void)
{
  return m_highlight;
}

void GraphicsLayerScene::setHighlightEnabled(bool status)
{
  m_highlight = status;

  if (!status) {
    clearHighlight();
  }
}

void GraphicsLayerScene::clearHighlight(void)
{
  for (int i = 0; i < m_selectedSymbols.size(); ++i) {
    m_selectedSymbols[i]->restoreColor();
  }
  m_selectedSymbols.clear();
  m_graphicsLayer->forceUpdate();
}

void GraphicsLayerScene::updateSelection(Symbol* symbol)
{
  clearHighlight();
  m_selectedSymbols.append(symbol);
  emit featureSelected(symbol);
}
