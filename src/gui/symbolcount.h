#ifndef SYMBOLCOUNT_H
#define SYMBOLCOUNT_H

#include <QDialog>

namespace Ui {
class symbolcount;
}

class symbolcount : public QDialog
{
    Q_OBJECT
    
public:
    explicit symbolcount(QWidget *parent = 0);
    ~symbolcount();
    
private:
    Ui::symbolcount *ui;
};

#endif // SYMBOLCOUNT_H
