#ifndef __RECORD_H__
#define __RECORD_H__

#include <QPainterPath>
#include <QGraphicsScene>

#include "symbol.h"

class FeaturesDataStore;

typedef enum { P = 0, N } Polarity;
typedef enum { N_0 = 0, N_90, N_180, N_270, M_0, M_90, M_180, M_270 } Orient;

struct Record {
  Record(FeaturesDataStore* _ds): ds(_ds) {}
  virtual ~Record() { delete symbol; }

  virtual QPainterPath painterPath(void) {
    return symbol->painterPath();
  }
  virtual void add(QGraphicsScene* scene) {
    scene->addItem(symbol);
  }
  virtual void initSymbol() = 0;

  Symbol* symbol;
  FeaturesDataStore* ds;
};


struct LineRecord: public Record {
  LineRecord(FeaturesDataStore* ds): Record(ds) {}
  virtual void initSymbol();

  qreal xs, ys;
  qreal xe, ye;
  int sym_num;
  Polarity polarity;
  int dcode;
};

struct PadRecord: public Record {
  PadRecord(FeaturesDataStore* ds): Record(ds) {}
  virtual QPainterPath painterPath(void);
  virtual void add(QGraphicsScene* scene);
  virtual void initSymbol();

  qreal x, y;
  int sym_num;
  Polarity polarity;
  int dcode;
  Orient orient;
};

struct ArcRecord: public Record {
  ArcRecord(FeaturesDataStore* ds): Record(ds) {}
  virtual void initSymbol();

  qreal xs, ys;
  qreal xe, ye;
  qreal xc, yc;
  int sym_num;
  Polarity polarity;
  int dcode;
  bool cw;
};

struct TextRecord: public Record {
  TextRecord(FeaturesDataStore* ds): Record(ds) {}
  virtual QString dynamicText(QString);
  virtual QPainterPath painterPath(void);
  virtual void add(QGraphicsScene* scene);
  virtual void initSymbol() {}

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

  BarcodeRecord(FeaturesDataStore* ds): TextRecord(ds) {}
  virtual QPainterPath painterPath(void);
  virtual void add(QGraphicsScene* scene) ;

  QString barcode;
  QString font;
  Polarity polarity;
  Orient orient;
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

  virtual QPainterPath painterPath(void);

  qreal xbs, ybs;
  PolyType poly_type;
  QList<SurfaceOperation*> operations;
};

struct SurfaceRecord: public Record {
  SurfaceRecord(FeaturesDataStore* ds): Record(ds) {}
  virtual void initSymbol();

  Polarity polarity;
  int dcode;
  QList<PolygonRecord*> polygons;
  PolygonRecord* currentRecord;
};

#endif /* __RECORD_H__ */
