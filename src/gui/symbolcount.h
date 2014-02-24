/**
 * @file   symbolcount.h
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
