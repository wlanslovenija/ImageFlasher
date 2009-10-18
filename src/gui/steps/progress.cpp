/*
 * wlan Ljubljana firmware flasher
 **/
#include "progress.h"
#include <math.h>

ProgressStep::ProgressStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, int min, int max)
  : InstructionsStep(stepId, title, instructions, image)
{
  m_progress.setMinimum(min < max ? min : max);
  m_progress.setMaximum(min > max ? min : max);

  addWidget(&m_progress);
}

void ProgressStep::setProgress(int progress) {
  m_progress.setValue(progress);
}

void ProgressStep::setMessage(const QString &message) {
  //TODO m_progress.set

}



