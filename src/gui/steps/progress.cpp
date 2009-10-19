/*
 * wlan Ljubljana firmware flasher
 **/
#include "progress.h"
#include <math.h>


QString ProgressBar::text() const {
  return m_text;
}

void ProgressBar::setText(const QString &text) {
  m_text = text;

}

ProgressStep::ProgressStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, int min, int max)
  : InstructionsStep(stepId, title, instructions, image)
{
  m_min = min < max ? min : max;
  m_max = min > max ? min : max;

  m_progress.setMinimum(m_min);
  m_progress.setMaximum(m_max);

  addWidget(&m_progress);
  setMessage("Processing");
  setBusy();


  emit completeChanged();

}

void ProgressStep::setProgress(int progress) {
  if (m_progress.maximum() == 0 && m_progress.minimum() == 0) {
    m_progress.setMinimum(m_min);
    m_progress.setMaximum(m_max);
  }

  m_progress.setValue(progress);
  emit completeChanged();
}

void ProgressStep::setMessage(const QString &message) {
  if (message.isEmpty()) {
    m_progress.setText("");
    m_progress.setTextVisible(false);
  }

  m_progress.setText(message);
  m_progress.setTextVisible(true);
}

void ProgressStep::setBusy() {
  m_progress.setMinimum(0);
  m_progress.setMaximum(0);
}

bool ProgressStep::isComplete() const {
  return m_progress.value() >= m_progress.maximum();
}
