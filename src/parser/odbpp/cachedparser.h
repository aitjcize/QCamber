/**
 * @file   cachedparser.h
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

#ifndef __CACHED_PARSER_H__
#define __CACHED_PARSER_H__

#include <QMap>
#include <QString>

#include "datastore.h"
#include "featuresparser.h"
#include "fontparser.h"
#include "parser.h"
#include "structuredtextparser.h"

template <typename P, typename D>
class CachedParser {
public:
  virtual ~CachedParser();
  static D* parse(QString filename);

private:
  D* realParse(QString filename);

private:
  static CachedParser<P, D>* m_instance;
  QMap<QString, D*> m_cache;
};

template <typename P, typename D>
CachedParser<P, D>* CachedParser<P, D>::m_instance = NULL;

template <typename P, typename D>
CachedParser<P, D>::~CachedParser<P, D>()
{
  for (typename QMap<QString, D*>::iterator it = m_cache.begin();
      it != m_cache.end(); ++it) {
    delete it.value();
  }
  m_instance = NULL;
}

template <typename P, typename D>
D* CachedParser<P, D>::parse(QString filename)
{
  if (!m_instance) {
    m_instance = new CachedParser<P, D>;
  }

  return m_instance->realParse(filename);
}

template <typename P, typename D>
D* CachedParser<P, D>::realParse(QString filename)
{
  if (m_cache.find(filename) != m_cache.end()) {
    return m_cache[filename];
  }

  P parser(filename);
  D* ds = parser.parse();
  m_cache[filename] = ds;

  return ds;
}

typedef CachedParser<FeaturesParser, FeaturesDataStore> CachedFeaturesParser;
typedef CachedParser<FontParser, FontDataStore> CachedFontParser;
typedef CachedParser<StructuredTextParser, StructuredTextDataStore> CachedStructuredTextParser;

#endif /* __CACHED_PARSER_H__ */
