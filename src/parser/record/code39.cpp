#include "code39.h"

#include <QtCore>

struct code39map c39m[] = {
  { '0', "NnNwWnWnN" },
  { '1', "WnNwNnNnW" },
  { '2', "NnWwNnNnW" },
  { '3', "WnWwNnNnN" },
  { '4', "NnNwWnNnW" },
  { '5', "WnNwWnNnN" },
  { '6', "NnWwWnNnN" },
  { '7', "NnNwNnWnW" },
  { '8', "WnNwNnWnN" },
  { '9', "NnWwNnWnN" },
  { 'A', "WnNnNwNnW" },
  { 'B', "NnWnNwNnW" },
  { 'C', "WnWnNwNnN" },
  { 'D', "NnNnWwNnW" },
  { 'E', "WnNnWwNnN" },
  { 'F', "NnWnWwNnN" },
  { 'G', "NnNnNwWnW" },
  { 'H', "WnNnNwWnN" },
  { 'I', "NnWnNwWnN" },
  { 'J', "NnNnWwWnN" },
  { 'K', "WnNnNnNwW" },
  { 'L', "NnWnNnNwW" },
  { 'M', "WnWnNnNwN" },
  { 'N', "NnNnWnNwW" },
  { 'O', "WnNnWnNwN" },
  { 'P', "NnWnWnNwN" },
  { 'Q', "NnNnNnWwW" },
  { 'R', "WnNnNnWwN" },
  { 'S', "NnWnNnWwN" },
  { 'T', "NnNnWnWwN" },
  { 'U', "WwNnNnNnW" },
  { 'V', "NwWnNnNnW" },
  { 'W', "WwWnNnNnN" },
  { 'X', "NwNnWnNnW" },
  { 'Y', "WwNnWnNnN" },
  { 'Z', "NwWnWnNnN" },
  { '-', "NwNnNnWnW" },
  { '.', "WwNnNnWnN" },
  { ' ', "NwWnNnWnN" },
  { '$', "NwNwNwNnN" },
  { '/', "NwNwNnNwN" },
  { '+', "NwNnNwNwN" },
  { '%', "NnNwNwNwN" },
  { '*', "NwNnWnWnN" },
};

QMap<QChar, QString> Code39::s_patterns;

void Code39::initPatterns(void)
{
  for (unsigned i = 0; i < sizeof(c39m) / sizeof(c39m[0]); ++i) {
    s_patterns[c39m[i].tchar] = c39m[i].pattern;
  }
}

QString Code39::encode(QString text)
{
  QString pattern = s_patterns['*'] + "w";

  for (int i = 0; i < text.length(); ++i) {
    if (text[i].isLower()) {
      pattern += s_patterns['+'] + "w";
      text[i] = text[i].toUpper();
    }
    if (s_patterns.find(text[i]) != s_patterns.end()) {
      pattern += s_patterns[text[i]] + "w";
    }
  }
  pattern += s_patterns['*'];

  return pattern;
}
