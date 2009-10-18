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

int FilesList::getCount() {
  return m_titleList.size();
}

QString FilesList::getTitle(int i) {
  return m_titleList[i];
}

bool FilesList::isRequired(int i) {
  return m_requiredList[i];
}

bool FilesList::isValid(int i, const QString &file) {

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
    FileChooser *chooser = new FileChooser(&m_panel);
    connect( chooser, SIGNAL( fileNameChanged( const QString & ) ), this, SLOT( fileNameChanged( const QString & ) ) );
    layout->addRow(label, chooser);
    m_choosers.append(chooser);
  }

  addWidget(&m_panel);
  validatePage();
}

QString FilesStep::getFile(int i) {
  return m_choosers[i]->fileName();
}

bool FilesStep::isComplete() {
  bool valid = true;
  for (int i = 0; i < m_list.getCount(); i++) {
    QString file = m_choosers[i]->fileName();
    if (m_list.isRequired(i) && (file == NULL || file.isEmpty())) {
      valid = false;
      continue;
    }

    valid &= m_list.isValid(i, file);
  }
  printf(valid ? "yes\n" : "no\n");
  return valid;
}

void FilesStep::fileNameChanged(const QString& filename) {
  FileChooser* s = (FileChooser*) sender();
  //int i = m_choosers.indefOf(s);
  printf("in\n");
  emit completeChanged();
}

