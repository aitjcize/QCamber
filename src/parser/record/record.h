#ifndef __RECORD_H__
#define __RECORD_H__

#include <QPainterPath>
#include <QGraphicsScene>
#include <QStringList>

#include "symbol.h"

class DataStore;
class FeaturesDataStore;
class FontDataStore;

typedef enum { N_0 = 0, N_90, N_180, N_270, M_0, M_90, M_180, M_270 } Orient;

struct Record {
  Record(DataStore* _ds): ds(_ds) {}
  virtual ~Record() { delete symbol; }

  virtual void add(QGraphicsScene* scene) {
    scene->addItem(symbol);
  }
  virtual void addToGroup(QGraphicsItemGroup* group) {
    group->addToGroup(symbol);
  }

  Symbol* symbol;
  DataStore* ds;
};


struct LineRecord: public Record {
  LineRecord(FeaturesDataStore* ds, const QStringList& param);

  qreal xs, ys;
  qreal xe, ye;
  int sym_num;
  Polarity polarity;
  int dcode;
};

struct PadRecord: public Record {
  PadRecord(FeaturesDataStore* ds, const QStringList& param);
  virtual void add(QGraphicsScene* scene);
  virtual void addToGroup(QGraphicsItemGroup* group);

  qreal x, y;
  int sym_num;
  Polarity polarity;
  int dcode;
  Orient orient;
};

struct ArcRecord: public Record {
  ArcRecord(FeaturesDataStore* ds, const QStringList& param);

  qreal xs, ys;
  qreal xe, ye;
  qreal xc, yc;
  int sym_num;
  Polarity polarity;
  int dcode;
  bool cw;
};

struct TextRecord: public Record {
  TextRecord(FeaturesDataStore* ds, const QStringList& param);
  virtual QString dynamicText(QString);
  virtual void add(QGraphicsScene* scene);
  virtual void addToGroup(QGraphicsItemGroup* group);

  qreal x, y;
  QString font;
  Polarity polarity;
  Orient orient;
  qreal xsize, ysize;
  qreal width_factor;
  QString text;
  int version;
};

struct BarcodeRecord: public TextRecord {
  typedef enum { T = 0, B } AstrPos;

  BarcodeRecord(FeaturesDataStore* ds, const QStringList& param);
  virtual void add(QGraphicsScene* scene);
  virtual void addToGroup(QGraphicsItemGroup* group);

  QString barcode;
  QString e;
  qreal w, h;
  bool fasc;
  bool cs;
  bool bg;
  bool astr;
  AstrPos astr_pos;
};

struct SurfaceOperation {
  typedef enum { SEGMENT = 0, CURVE } OpType;

  OpType type;
  qreal x, y;
  qreal xe, ye;
  qreal xc, yc;
  bool cw;
};

struct PolygonRecord {
  typedef enum { I = 0, H } PolyType;

  PolygonRecord(const QStringList& param);
  virtual QPainterPath painterPath(void);

  qreal xbs, ybs;
  PolyType poly_type;
  QList<SurfaceOperation*> operations;
};

struct SurfaceRecord: public Record {
  SurfaceRecord(FeaturesDataStore* ds, const QStringList& param);
  void initSymbol(void);

  Polarity polarity;
  int dcode;
  QList<PolygonRecord*> polygons;
  PolygonRecord* currentRecord;
};

struct CharLineRecord {
  typedef enum { R = 0, S } ShapeType;

  CharLineRecord(FontDataStore* ds, const QStringList& param);
  QPainterPath painterPath(qreal width_factor);

  FontDataStore* ds;
  qreal xs, ys;
  qreal xe, ye;
  Polarity polarity;
  ShapeType shape;
  qreal width;
};

struct CharRecord {
  CharRecord(FontDataStore* ds, const QStringList& param);
  QPainterPath painterPath(qreal width_factor);
  
  FontDataStore* ds;
  char tchar;
  QList<CharLineRecord*> lines;
  Symbol* symbol;
};

#endif /* __RECORD_H__ */
