#ifndef __ARCHIVEMANAGERDIALOG_H__
#define __ARCHIVEMANAGERDIALOG_H__

#include <QFileSystemModel>
#include <QWidget>

#ifdef Q_WS_WIN
# define TAR_COMMAND "tools/tar.exe"
# define GZIP_COMMAND "tools/gzip.exe"
#else
# define TAR_COMMAND "tar"
# define GZIP_COMMAND "gzip"
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
  bool recurRemove(const QString& dirname);
    
private:
  Ui::ArchiveManagerDialog *ui;
  QFileSystemModel* m_model;
  QString m_rootDirName;
};

#endif // __ARCHIVEMANAGERDIALOG_H__
