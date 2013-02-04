#ifndef __RECORD_H__
#define __RECORD_H__

#include <QPainterPath>

typedef enum { P = 0, N } Polarity;
typedef enum { N_0 = 0, N_90, N_180, N_270, M_0, M_90, M_180, M_270 } Orient;

struct Record {
  virtual void addShape(QPainterPath& path) = 0;
};


struct SurfaceOperation {
  typedef enum { SEGMENT = 0, CURVE } OpType;

  virtual void addShape(QPainterPath& path);
  
  OpType type;
  qreal x, y;
  qreal xe, ye;
  qreal xc, yc;
  bool cw;
};

struct LineRecord: public Record {
  virtual void addShape(QPainterPath& path);

  qreal xs, ys;
  qreal xe, ye;
  int sym_num;
  Polarity polarity;
  int dcode;
};

struct PadRecord: public Record {
  virtual void addShape(QPainterPath& path);

  qreal x, y;
  int sym_num;
  Polarity polarity;
  int dcode;
  Orient orient;
};

struct ArcRecord: public Record {
  virtual void addShape(QPainterPath& path);

  qreal xs, ys;
  qreal xe, ye;
  qreal xc, yc;
  int sym_num;
  Polarity polarity;
  int dcode;
  bool cw;
};

struct TextRecord: public Record {
  virtual void addShape(QPainterPath& path);
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

  virtual void addShape(QPainterPath& path);

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

struct PolygonRecord {
  typedef enum { I = 0, H } PolyType;
  virtual void addShape(QPainterPath& path);

  qreal xbs, ybs;
  PolyType poly_type;
  QList<SurfaceOperation*> operations;
};

struct SurfaceRecord: public Record {
  virtual void addShape(QPainterPath& path);

  Polarity polarity;
  int dcode;
  QList<PolygonRecord*> polygons;
  PolygonRecord* currentRecord;
};

#endif /* __RECORD_H__ */
