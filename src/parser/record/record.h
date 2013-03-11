#ifndef __RECORD_H__
#define __RECORD_H__

#include <QPainterPath>
#include <QGraphicsScene>
#include <QStringList>

#include "symbol.h"

class Features;
class DataStore;
class FeaturesDataStore;
class FontDataStore;
class NotesDataStore;

typedef enum { N_0 = 0, N_90, N_180, N_270, M_0, M_90, M_180, M_270 } Orient;

struct Record {
  Record(DataStore* _ds): ds(_ds) {}
  virtual ~Record() { }

  virtual void addToChild(Symbol* group) {
    group->addChild(symbol);
  }
  virtual void addToScene(QGraphicsScene* scene) {
    scene->addItem(symbol);
  }

  DataStore* ds;
  Symbol* symbol;
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

  void setTransform(void);
  virtual QString dynamicText(QString);

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
  virtual ~PolygonRecord();
  virtual QPainterPath painterPath(void);

  qreal xbs, ybs;
  PolyType poly_type;
  QList<SurfaceOperation*> operations;
};

struct SurfaceRecord: public Record {
  SurfaceRecord(FeaturesDataStore* ds, const QStringList& param);
  virtual ~SurfaceRecord();
  void initSymbol(void);

  Polarity polarity;
  int dcode;
  QList<PolygonRecord*> polygons;
  PolygonRecord* currentRecord;
};

struct CharLineRecord {
  typedef enum { R = 0, S } ShapeType;

  CharLineRecord(const QStringList& param);
  QPainterPath painterPath(qreal width_factor);

  qreal xs, ys;
  qreal xe, ye;
  Polarity polarity;
  ShapeType shape;
  qreal width;
};

struct CharRecord {
  CharRecord(FontDataStore* ds, const QStringList& param);
  virtual ~CharRecord();

  QPainterPath painterPath(qreal width_factor);
  
  FontDataStore* ds;
  char tchar;
  QList<CharLineRecord*> lines;
};

struct NoteRecord: public Record {
  NoteRecord(NotesDataStore* ds, const QStringList& param);

  int timestamp;
  QString user;
  qreal x, y;
  QString text;
};

#endif /* __RECORD_H__ */
