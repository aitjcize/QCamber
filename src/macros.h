#ifndef __MACROS_H__
#define __MACROS_H__

#define R2D (180.0 / M_PI)
#define D2R (M_PI / 180.0)

#define APPEND_ROW(root, header, data)                                      \
  ({                                                                        \
    QList<QStandardItem*> c;                                                \
    QStandardItem* item = new QStandardItem(header);                        \
    c.append(item);                                                         \
    c.append(new QStandardItem(data));                                      \
    root->appendRow(c);                                                     \
    item;                                                                   \
  })

#endif /* __MACROS_H__ */
