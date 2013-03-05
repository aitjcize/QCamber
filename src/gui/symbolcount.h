#ifndef SYMBOLCOUNT_H
#define SYMBOLCOUNT_H

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

namespace Ui {
class symbolcount;
}

class symbolcount : public QDialog
{
    Q_OBJECT
    
public:
    explicit symbolcount(QWidget *parent = 0);
    void addSymbolCount(QTextEdit *output);
    ~symbolcount();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::symbolcount *ui;
};

#endif // SYMBOLCOUNT_H
