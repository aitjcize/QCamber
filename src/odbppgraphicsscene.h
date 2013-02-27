#ifndef __ODBPPGRAPHICSSCENE_H__
#define __ODBPPGRAPHICSSCENE_H__

#include <QGraphicsScene>
#include <QPointF>

#include "symbol.h"

class ODBPPGraphicsScene: public QGraphicsScene {
  Q_OBJECT

public:
  ODBPPGraphicsScene(QObject* parent = 0);
  void setAreaZoomEnabled(bool status);
  void updateSelection(Symbol* symbol);

  bool highlight(void);
  void setHighlight(bool status);
  void clearHighlight(void);

signals:
  void mouseMove(QPointF);
  void featureSelected(Symbol*);
  void rectSelected(QRectF);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
  QPointF m_rubberPS;
  QPointF m_rubberPE;
  bool m_areaZoomEnabled;
  bool m_highlight;
  QList<Symbol*> m_selectedSymbols;
};

#endif /* __ODBPPGRAPHICSSCENE_H__ */
