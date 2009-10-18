
#ifndef GUI_FILECHOOSER_H
#define GUI_FILECHOOSER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

class QLineEdit;
class QPushButton;

class FileChooser : public QWidget
{
  Q_OBJECT

  Q_ENUMS( Mode )
  Q_PROPERTY( Mode mode READ mode WRITE setMode )
  Q_PROPERTY( QString fileName READ fileName WRITE setFileName )

public:
  FileChooser( QWidget *parent = 0);
  FileChooser(const FileChooser &object);

  enum Mode { File, Directory };

  QString fileName() const;
  Mode mode() const;
  QString getPath();
  void setPath(const QString &path);

public slots:
  void setFileName( const QString &fn );
  void setMode( Mode m );

signals:
  void fileNameChanged( const QString & );

private slots:
  void chooseFile();

private:
  QLineEdit *m_lineEdit;
  QPushButton *m_button;
  QString m_path;
  Mode m_md;
};

#endif
