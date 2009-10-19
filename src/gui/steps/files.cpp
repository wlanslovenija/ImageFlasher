/*
 * wlan Ljubljana firmware flasher
 **/
#include "files.h"

FilesList::FilesList() {

}

FilesList::~FilesList() {

}

void FilesList::addFile(const QString &title, bool required, ValidatorCallback validator) {
  m_requiredList.append(required);
  m_titleList.append(title);
  m_validatorList.append(validator);
}

int FilesList::getCount() const {
  return m_titleList.size();
}

QString FilesList::getTitle(int i) const {
  return m_titleList[i];
}

bool FilesList::isRequired(int i) const {
  return m_requiredList[i];
}

bool FilesList::isValid(int i, const QString &file) const {

  ValidatorCallback validator = m_validatorList[i];
  if (validator == NULL) return true;

  return validator(file);
}

FilesStep::FilesStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, FilesList &files)
  : InstructionsStep(stepId, title, instructions, image)
{
  m_list = files;
  QFormLayout *layout = new QFormLayout(&m_panel);
  m_panel.setLayout(layout);
  for (int i = 0; i < m_list.getCount(); i++) {
    QLabel *label = new QLabel(m_list.getTitle(i), &m_panel);
    QLabel *notice = new QLabel(" ", &m_panel);
    notice->setStyleSheet("color: red; font-size: 10px; text-align: center;");
    //QColor c = notice->palette().color(QPalette::Disabled, QPalette::Text);
    //notice->palette().setColor(QPalette::Text, c);
    FileChooser *chooser = new FileChooser(&m_panel);
    connect( chooser, SIGNAL( fileNameChanged( const QString & ) ), this, SLOT( fileNameChanged( const QString & ) ) );
    layout->addRow(label, chooser);
    layout->addRow(notice);
    m_choosers.append(chooser);
    m_notices.append(notice);
  }

  addWidget(&m_panel);
  emit completeChanged();
}

QString FilesStep::getFile(int i) {
  return m_choosers[i]->fileName();
}

bool FilesStep::isComplete() const {
  bool valid = true;
  for (int i = 0; i < m_list.getCount(); i++) {
    QString file = m_choosers[i]->fileName();
    if (m_list.isRequired(i) && (file == NULL || file.isEmpty())) {
      m_notices[i]->setText(tr("This field is required."));
      valid = false;
      continue;
    }
    bool v = m_list.isValid(i, file);
    if (!v) {
      m_notices[i]->setText(tr("This input is not valid."));
      valid = false;
      continue;
    }
    m_notices[i]->setText(" ");
  }

  return valid;
}

void FilesStep::fileNameChanged(const QString& filename) {
  FileChooser* s = (FileChooser*) sender();
  //int i = m_choosers.indefOf(s);

  emit completeChanged();
}

