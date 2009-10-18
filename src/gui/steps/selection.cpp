/*
 * wlan Ljubljana firmware flasher
 **/
#include "selection.h"

SelectionStep::SelectionStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, QStringList items)
  : InstructionsStep(stepId, title, instructions, image)
{

  foreach (QString str, items) 
    m_selector.addItem(str);

  m_selector.setCurrentIndex(0);

  addWidget(&m_selector);
}

int SelectionStep::getSelection() {
  return m_selector.currentIndex();
}


