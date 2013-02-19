#ifndef __LAYERGRAPHICSEFFECT__
#define __LAYERGRAPHICSEFFECT__

#include <QGraphicsEffect>

class LayerGraphicsEffect: public QGraphicsEffect {
public:
  LayerGraphicsEffect(QObject* parent = 0);

  void setOpacity(qreal opacity);
  void setDoComposite(bool status);

protected:
  virtual void draw(QPainter* painter);

private:
  qreal m_opacity;
  bool m_isFullyOpaque;
  bool m_isFullyTransparent;
  bool m_doComposite;
};

#endif /* __LAYERGRAPHICSEFFECT__ */
