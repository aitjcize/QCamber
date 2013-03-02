#include "clickablelabel.h"

#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget *parent)
  :QLabel(parent)
{
}

ClickableLabel::ClickableLabel(const QString &text, QWidget *parent)
  :QLabel(text, parent)
{
}

void ClickableLabel::setColor(QString fg, QString bg)
{
  QString tmpl("QLabel { background-color: %1; color: %2; }");
  setStyleSheet(tmpl.arg(fg).arg(bg));
}

void ClickableLabel::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton) {
    emit clicked();
  }
}
