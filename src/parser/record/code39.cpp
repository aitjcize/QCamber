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

struct code39map c39fm[] = {
  { 0, "%U" },
  { 1, "$A" },
  { 2, "$B" },
  { 3, "$C" },
  { 4, "$D" },
  { 5, "$E" },
  { 6, "$F" },
  { 7, "$G" },
  { 8, "$H" },
  { 9, "$I" },
  { 10, "$J" },
  { 11, "$K" },
  { 12, "$L" },
  { 13, "$M" },
  { 14, "$N" },
  { 15, "$O" },
  { 16, "$P" },
  { 17, "$Q" },
  { 18, "$R" },
  { 19, "$S" },
  { 20, "$T" },
  { 21, "$U" },
  { 22, "$V" },
  { 23, "$W" },
  { 24, "$X" },
  { 25, "$Y" },
  { 26, "$Z" },
  { 27, "%A" },
  { 28, "%B" },
  { 29, "%C" },
  { 30, "%D" },
  { 31, "%E" },
  { 32, " "} ,
  { 33, "/A" },
  { 34, "/B" },
  { 35, "/C" },
  { 36, "/D" },
  { 37, "/E" },
  { 38, "/F" },
  { 39, "/G" },
  { 40, "/H" },
  { 41, "/I" },
  { 42, "/J" },
  { 43, "/K" },
  { 44, "/L" },
  { 45, "-" },
  { 46, "." },
  { 47, "/O" },
  { 48, "0" },
  { 49, "1" },
  { 50, "2" },
  { 51, "3" },
  { 52, "4" },
  { 53, "5" },
  { 54, "6" },
  { 55, "7" },
  { 56, "8" },
  { 57, "9" },
  { 58, "/Z" },
  { 59, "%F" },
  { 60, "%G" },
  { 61, "%H" },
  { 62, "%I" },
  { 63, "%J" },
  { 64, "%V" },
  { 65, "A" },
  { 66, "B" },
  { 67, "C" },
  { 68, "D" },
  { 69, "E" },
  { 70, "F" },
  { 71, "G" },
  { 72, "H" },
  { 73, "I" },
  { 74, "J" },
  { 75, "K" },
  { 76, "L" },
  { 77, "M" },
  { 78, "N" },
  { 79, "O" },
  { 80, "P" },
  { 81, "Q" },
  { 82, "R" },
  { 83, "S" },
  { 84, "T" },
  { 85, "U" },
  { 86, "V" },
  { 87, "W" },
  { 88, "X" },
  { 89, "Y" },
  { 90, "Z" },
  { 91, "%K" },
  { 92, "%L" },
  { 93, "%M" },
  { 94, "%N" },
  { 95, "%O" },
  { 96, "%W" },
  { 97, "+A" },
  { 98, "+B" },
  { 99, "+C" },
  { 100, "+D" },
  { 101, "+E" },
  { 102, "+F" },
  { 103, "+G" },
  { 104, "+H" },
  { 105, "+I" },
  { 106, "+J" },
  { 107, "+K" },
  { 108, "+L" },
  { 109, "+M" },
  { 110, "+N" },
  { 111, "+O" },
  { 112, "+P" },
  { 113, "+Q" },
  { 114, "+R" },
  { 115, "+S" },
  { 116, "+T" },
  { 117, "+U" },
  { 118, "+V" },
  { 119, "+W" },
  { 120, "+X" },
  { 121, "+Y" },
  { 122, "+Z" },
  { 123, "%P" },
  { 124, "%Q" },
  { 125, "%R" },
  { 126, "%S" },
  { 127, "%T" },
};

QMap<QChar, QString> Code39::s_patterns;
QMap<QChar, unsigned> Code39::s_checksum;
QMap<unsigned, QChar> Code39::s_checksum_inv;
QMap<QChar, QString> Code39::s_fascmap;

void Code39::initPatterns(void)
{
  for (unsigned i = 0; i < sizeof(c39m) / sizeof(c39m[0]); ++i) {
    s_patterns[c39m[i].tchar] = c39m[i].pattern;
    s_checksum[c39m[i].tchar] = i;
    s_checksum_inv[i] = c39m[i].tchar;
  }

  for (unsigned i = 0; i < sizeof(c39fm) / sizeof(c39fm[0]); ++i) {
    s_fascmap[c39fm[i].tchar] = c39fm[i].pattern;
  }
}

QString Code39::encode(QString text, bool checksum, bool fasc)
{
  QString pattern = s_patterns['*'] + "w";
  unsigned sum = 0;

  if (fasc) {
    QString expended;
    for (int i = 0; i < text.length(); ++i) {
      expended += s_fascmap[text[i]];
    }
    text = expended;
  } else {
    text = text.toUpper();
  }

  for (int i = 0; i < text.length(); ++i) {
    if (s_patterns.find(text[i]) != s_patterns.end()) {
      pattern += s_patterns[text[i]] + "w";
      if (!fasc && checksum) {
        sum += s_checksum[text[i]];
      }
    }
  }
  /*
  if (checksum) {
    pattern += "w" + s_patterns[s_checksum_inv[sum % 43]];
  }
  */
  pattern += s_patterns['*'];

  return pattern;
}
