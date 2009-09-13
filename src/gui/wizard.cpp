/*
 * wlan Ljubljana firmware flasher
 */
#include "gui/wizard.h"

FlashWizard::FlashWizard()
  : QWizard()
{
  // Setup layout
  m_ui.setupUi(this);
  
  // Connect to signals
  connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotCurrentIdChanged(int)));
}

void FlashWizard::slotCurrentIdChanged(int id)
{
  switch (id) {
    case Intro: break;
    case RouterSelection: break;
    case FirmwareSelection: break;
  }
  qDebug("hello %d", id);
}
