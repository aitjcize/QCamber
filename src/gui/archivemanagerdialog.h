#ifndef __ARCHIVEMANAGERDIALOG_H__
#define __ARCHIVEMANAGERDIALOG_H__

#include <QFileSystemModel>
#include <QWidget>

#ifdef Q_WS_WIN
# define TAR_CMD "./tar"
# define GZIP_CMD "./gzip"
#else
# define TAR_CMD "tar"
# define GZIP_CMD "gzip"
#endif

namespace Ui {
class ArchiveManagerDialog;
}

class ArchiveManagerDialog : public QWidget
{
  Q_OBJECT
    
public:
  explicit ArchiveManagerDialog(QWidget *parent = 0);
  ~ArchiveManagerDialog();

public slots:
  void on_browseButton_clicked(void);
  void on_importButton_clicked(void);
  void on_removeButton_clicked(void);
  void on_setRootButton_clicked(void);
  void on_listView_doubleClicked(const QModelIndex& index);

private:
  int execute(QString cmd, QStringList args);
  bool recurRemove(const QString& dirname);
    
private:
  Ui::ArchiveManagerDialog *ui;
  QFileSystemModel* m_model;
  QString m_rootDirName;
};

#endif // __ARCHIVEMANAGERDIALOG_H__
