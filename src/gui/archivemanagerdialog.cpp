#include "archivemanagerdialog.h"
#include "ui_archivemanagerdialog.h"

#include <QtGui>

#include "context.h"
#include "jobmatrix.h"
#include "settings.h"
#include "structuredtextparser.h"

ArchiveManagerDialog::ArchiveManagerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArchiveManagerDialog)
{
  ui->setupUi(this);

  m_rootDirName = SETTINGS->get("System", "RootDir").toString();

  if (m_rootDirName.isEmpty()) {
    m_rootDirName = QCoreApplication::applicationDirPath() + "/Jobs";
    SETTINGS->set("System", "RootDir", m_rootDirName);
  }

  QDir jobsDir(m_rootDirName);
  if (!jobsDir.exists()) {
    QDir::root().mkdir(m_rootDirName);
  }

  m_model = new QFileSystemModel;
  m_model->setRootPath(m_rootDirName);

  ui->listView->setModel(m_model);
  ui->listView->setRootIndex(m_model->index(m_rootDirName));
}

ArchiveManagerDialog::~ArchiveManagerDialog()
{
  delete ui;
  delete m_model;
} 

void ArchiveManagerDialog::on_browseButton_clicked(void)
{
  QFileDialog diag(NULL, "Choose a tarball", "",
      "ODB++ database (*.tgz *.tar.gz)");
  diag.exec();

  QString sel = diag.selectedFiles()[0];
  if (sel.endsWith(".tgz") || sel.endsWith(".tar.gz")) {
    ui->filenameLineEdit->setText(sel);
  }
}

void ArchiveManagerDialog::on_importButton_clicked(void)
{
  QString filename = ui->filenameLineEdit->text();

  if (filename.isEmpty()) {
    QMessageBox::critical(this, "Error", "No filename specified!");
    return;
  }

  QString jobName =  QFileInfo(filename).baseName();

  QDir jobsDir(m_rootDirName);
  if (!jobsDir.mkdir(jobName)) {
    QMessageBox::critical(this, "Error", "Job with same name exists!");
    return;
  }

  QString extractDir = jobsDir.absoluteFilePath(jobName);

  QStringList args;
#ifdef Q_WS_WIN
  filename.replace(":", "");
  filename.prepend('/');
#endif
  args << "xf" << filename << "--strip-components=1" << "-C" << extractDir;

  int ret = QProcess::execute(TAR_COMMAND, args);

  if (ret != 0) {
    QMessageBox::critical(this, "Error",
        QString("Error when decompressing `%1'").arg(filename));
    recurRemove(extractDir);
  }
}

void ArchiveManagerDialog::on_removeButton_clicked(void)
{
  QString name = m_model->data(ui->listView->currentIndex()).toString();

  int ret = QMessageBox::question(this,"Confirm",
      QString("Are you sure you want to remove `%1'").arg(name),
        QMessageBox::Yes, QMessageBox::No);

  if (ret != QMessageBox::Yes)
    return;

  recurRemove(m_rootDirName + "/" + name);
}

void ArchiveManagerDialog::on_setRootButton_clicked(void)
{
  QFileDialog diag(NULL, "Choose a directory", m_rootDirName);
  diag.setFileMode(QFileDialog::Directory);
  diag.setOption(QFileDialog::ShowDirsOnly);

  if (diag.exec()) {
    m_rootDirName = diag.selectedFiles()[0];
    SETTINGS->set("System", "RootDir", m_rootDirName);

    m_model->setRootPath(m_rootDirName);
    ui->listView->setModel(m_model);
    ui->listView->setRootIndex(m_model->index(m_rootDirName));
  }
}

void ArchiveManagerDialog::on_listView_doubleClicked(const QModelIndex& index)
{
  QString name = m_model->data(index).toString();
  ctx.loader = new ArchiveLoader(m_rootDirName + "/" + name);

  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();

  JobMatrix* jobMatirx = new JobMatrix(0, ds);
  jobMatirx->SetMatrix();
  jobMatirx->show();
}

bool ArchiveManagerDialog::recurRemove(const QString& dirname)
{
  bool result = true;
  QDir dir(dirname);

  if (dir.exists(dirname)) {
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
          QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files,
          QDir::DirsFirst)) {
      if (info.isDir()) {
        result = recurRemove(info.absoluteFilePath());
      }
      else {
        result = QFile::remove(info.absoluteFilePath());
      }

      if (!result) {
        return result;
      }
    }
    result = dir.rmdir(dirname);
  }
  return result;
}
