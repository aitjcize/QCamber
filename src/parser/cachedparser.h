#ifndef __CACHED_PARSER_H__
#define __CACHED_PARSER_H__

#include <QMap>
#include <QString>

#include "parser.h"
#include "featuresparser.h"
#include "fontparser.h"

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

#endif /* __CACHED_PARSER_H__ */
