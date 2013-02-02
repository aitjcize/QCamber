#include "usersymbol.h"

#include <QtGui>
#include <QRegExp>

#include "parser.h"

#include <iostream>
using std::cout;
using std::endl;

UserSymbol::UserSymbol(QString def):
    Symbol(def, def), m_def(def)
{
}

QRectF UserSymbol::boundingRect() const
{
  return bounding;
}

void UserSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  QPainterPath path;
  addShape(path);
  painter->drawPath(path);
  //testDraw(*painter);
}

void UserSymbol::addShape(QPainterPath& path)
{
  Parser parser("features", Parser::LINE_RECORD);
  LineRecordDataStore* ds = (LineRecordDataStore*)parser.parse();
  LineRecordDataStore::DataType& data = ds->data();

  //path.setFillRule(Qt::WindingFill);

  for(LineRecordDataStore::DataType::iterator it = data.begin();
      it != data.end(); ++it) {
    LineRecordDataStore::ElementType& line = (*it);
    QString op = QString::fromStdString(line[0]);
    if (op.startsWith("#")) {
      continue;
    }
#define P(x) (QString::fromStdString(line[(x)]).toDouble() * 10000)

    qreal lx, ly;
    if (op == "OB") {
      lx = P(1); ly = P(2);
      path.moveTo(lx, -ly);
    } else if (op == "OS") {
      lx = P(1); ly = P(2);
      path.lineTo(lx, -ly);
    } else if (op == "OC") {
      qreal sx = lx, sy = ly;
      qreal ex = P(1), ey = P(2);
      qreal cx = P(3), cy = P(4);

      qreal sax = sx - cx, say = sy - cy;
      qreal eax = ex - cx, eay = ey - cy;

      qreal rs = sqrt(sax * sax + say * say);
      qreal re = sqrt(eax * eax + eay * eay);

      qreal sa = atan(say / sax);
      qreal ea = atan(eay / eax);

      if (ea <= 0 && (eax < 0)) {
        ea += M_PI;
      } else if (ea > 0 && (eax < 0 || eay < 0)) {
        ea += M_PI;
      }

      if (sa <= 0 && (sax < 0)) {
        sa += M_PI;
      } else if (sa > 0 && (sax < 0 || say < 0)) {
        sa += M_PI;
      }

      if (line[5] == "Y") {
        if (sa < ea) {
          sa += 2 * M_PI;
        }
        for (qreal a = sa; a >= ea; a -= 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          path.lineTo(cx + rad * cos(a), -(cy + rad * sin(a)));
        }
      } else {
        if (ea < sa) {
          ea += 2 * M_PI;
        }
        for (qreal a = sa; a <= ea; a += 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          path.lineTo(cx + rad * cos(a), -(cy + rad * sin(a)));
        }
      }
      path.lineTo(ex, -ey);
      lx = ex; ly = ey;
    }
  }
  path.closeSubpath();
  
  bounding = path.boundingRect();
}

void UserSymbol::testDraw(QPainter& painter)
{
  Parser parser("features", Parser::LINE_RECORD);
  LineRecordDataStore* ds = (LineRecordDataStore*)parser.parse();
  LineRecordDataStore::DataType& data = ds->data();


  for(LineRecordDataStore::DataType::iterator it = data.begin();
      it != data.end(); ++it) {
    LineRecordDataStore::ElementType& line = (*it);
    QString op = QString::fromStdString(line[0]);
    if (op.startsWith("#")) {
      continue;
    }
#define P(x) (QString::fromStdString(line[(x)]).toDouble() * 10000)

    qreal lx, ly;
    if (op == "OB") {
      lx = P(1); ly = P(2);
    } else if (op == "OS") {
      painter.drawLine(lx, -ly, P(1), -P(2));
      lx = P(1); ly = P(2);
    } else if (op == "OC") {
      qreal sx = lx, sy = ly;
      qreal ex = P(1), ey = P(2);
      qreal cx = P(3), cy = P(4);

      qreal sax = sx - cx, say = sy - cy;
      qreal eax = ex - cx, eay = ey - cy;

      qreal rs = sqrt(sax * sax + say * say);
      qreal re = sqrt(eax * eax + eay * eay);

      qreal sa = atan(say / sax);
      qreal ea = atan(eay / eax);

      if (ea <= 0 && (eax < 0)) {
        ea += M_PI;
      } else if (ea > 0 && (eax < 0 || eay < 0)) {
        ea += M_PI;
      }

      if (sa <= 0 && (sax < 0)) {
        sa += M_PI;
      } else if (sa > 0 && (sax < 0 || say < 0)) {
        sa += M_PI;
      }

      lx = sx; ly = sy;
      if (line[5] == "Y") {
        if (sa < ea) {
          sa += 2 * M_PI;
        }
        for (qreal a = sa; a >= ea; a -= 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          painter.drawLine(lx, -ly, cx + rad * cos(a), -(cy + rad * sin(a)));
          lx = cx + rad * cos(a); ly = cy + rad * sin(a);
        }
      } else {
        if (ea < sa) {
          ea += 2 * M_PI;
        }
        for (qreal a = sa; a <= ea; a += 0.01) {
          qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
          painter.drawLine(lx, -ly, cx + rad * cos(a), -(cy + rad * sin(a)));
          lx = cx + rad * cos(a); ly = cy + rad * sin(a);
        }
      }
      painter.drawLine(lx, -ly, ex, -ey);
      lx = ex; ly = ey;
    }
  }

  /*
    qreal lx, ly;
    qreal cx = 0, cy = 0;
    qreal sx = -100, sy = 0;
    qreal ex = -70.7106, ey = -70.7106;

    qreal sax = sx - cx, say = sy - cy;
    qreal eax = ex - cx, eay = ey - cy;

    qreal rs = sqrt(sax * sax + say * say);
    qreal re = sqrt(eax * eax + eay * eay);

    qreal sa = atan(say / sax);
    qreal ea = atan(eay / eax);

    if (ea <= 0 && (eax < 0)) {
      ea += M_PI;
    } else if (ea > 0 && (eax < 0 || eay < 0)) {
      ea += M_PI;
    }

    if (sa <= 0 && (sax < 0)) {
      sa += M_PI;
    } else if (sa > 0 && (sax < 0 || say < 0)) {
      sa += M_PI;
    }

    lx = sx; ly = sy;
    if (true) {
      qDebug() << sa << ea;
      if (sa < ea) {
        sa += 2 * M_PI;
      }
      qDebug() << sa << ea;
      for (qreal a = sa; a >= ea; a -= 0.01) {
        qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
        painter.drawLine(lx, -ly, cx + rad * cos(a), -(cy + rad * sin(a)));
        lx = cx + rad * cos(a); ly = cy + rad * sin(a);
      }
    } else {
      if (ea < sa) {
        ea += 2 * M_PI;
      }
      for (qreal a = sa; a >= ea; a -= 0.01) {
        qreal rad = (rs * (ea - a) + re * (a - sa)) / (ea - sa);
        painter.drawLine(lx, ly, cx + rad * cos(a), cy + rad * sin(a));
        lx = cx + rad * cos(a); ly = cy + rad * sin(a);
      }
    }
    painter.drawLine(lx, ly, ex, ey);
    lx = ex; ly = ey;
  */
}
