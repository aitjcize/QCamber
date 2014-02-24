/**
 * @file   symbolpool.cpp
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

#include "symbolpool.h"

SymbolPool* SymbolPool::m_instance = NULL;

SymbolPool::SymbolPool()
{

}

SymbolPool::~SymbolPool()
{
  for (QMap<QString, Symbol*>::iterator it = m_cache.begin();
      it != m_cache.end(); ++it) {
    delete it.value();
  }
  m_instance = NULL;
}

SymbolPool* SymbolPool::instance()
{
  if (!m_instance) {
    m_instance = new SymbolPool;
  }
  return m_instance;
}

Symbol* SymbolPool::get(const QString& def, const Polarity& polarity,
    const AttribData& attrib)
{
  if (m_cache.find(def) != m_cache.end()) {
    return m_cache[def];
  }

  Symbol* symbol = SymbolFactory::create(def, polarity, attrib);

  if (symbol) {
    m_cache[def] = symbol;
  }

  return symbol;
}
