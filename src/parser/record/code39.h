#ifndef __CODE_39_H__
#define __CODE_39_H__

#include <QChar>
#include <QMap>
#include <QString>

struct code39map {
  QChar tchar;
  QString pattern;
};

class Code39 {
public:
  static void initPatterns(void);
  static QString encode(QString text, bool fasc=false);

private:
  static QMap<QChar, QString> s_patterns;
  static QMap<QChar, QString> s_fascmap;
};

#endif /* __CODE_39_H__ */
