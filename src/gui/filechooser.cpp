
#include "filechooser.h"

FileChooser::FileChooser(QWidget *parent) : QWidget(parent), m_md( File ) , m_path(QString::null)
{
  QHBoxLayout *layout = new QHBoxLayout( this );
  layout->setMargin( 0 );

  m_lineEdit = new QLineEdit(this);
  layout->addWidget( m_lineEdit );

  connect( m_lineEdit, SIGNAL( textChanged( const QString & ) ), this, SIGNAL( fileNameChanged( const QString & ) ) );

  m_button = new QPushButton( "...", this);
  m_button->setFixedWidth( m_button->fontMetrics().width( " ... " ) );
  layout->addWidget( m_button );

  connect( m_button, SIGNAL( clicked() ), this, SLOT( chooseFile() ) );

  setFocusProxy( m_lineEdit );
}

FileChooser::FileChooser(const FileChooser &object) : QWidget(object.parentWidget()), m_md( File ), m_path(QString::null) {
  QHBoxLayout *layout = new QHBoxLayout( this );
  layout->setMargin( 0 );

  m_lineEdit = new QLineEdit(this);
  layout->addWidget( m_lineEdit );

  connect( m_lineEdit, SIGNAL( textChanged( const QString & ) ), this, SIGNAL( fileNameChanged( const QString & ) ) );

  m_button = new QPushButton( "...", this);
  m_button->setFixedWidth( m_button->fontMetrics().width( " ... " ) );
  layout->addWidget( m_button );

  connect( m_button, SIGNAL( clicked() ), this, SLOT( chooseFile() ) );

  setFocusProxy( m_lineEdit );
  setLayout(layout);
}

void FileChooser::setFileName( const QString &fn )
{
  m_lineEdit->setText( fn );
}

QString FileChooser::fileName() const
{
  return m_lineEdit->text();
}

FileChooser::Mode FileChooser::mode() const {
  return m_md;
}

void FileChooser::setMode( Mode m ) {
  m_md = m;
}

void FileChooser::chooseFile()
{
  QString fn;
  if ( mode() == File )
    fn = QFileDialog::getOpenFileName(this, QString::null, m_lineEdit->text().isEmpty() ? m_path : m_lineEdit->text() );
  else
    fn = QFileDialog::getExistingDirectory(this, QString::null, m_lineEdit->text().isEmpty() ? m_path : m_lineEdit->text());

  if ( !fn.isEmpty() ) {
    //m_path = 
    m_lineEdit->setText( fn );
    emit fileNameChanged( fn );
  }
}

QString FileChooser::getPath() {
  return m_path;
}

void FileChooser::setPath(const QString &path) {
  m_path = path;
}

