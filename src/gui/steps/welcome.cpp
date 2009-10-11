/*
 * wlan Ljubljana firmware flasher
 **/
#include "gui/steps/welcome.h"

WelcomeStep::WelcomeStep()
  : Step("init")
{
  m_ui.setupUi(this);
}

void WelcomeStep::initializePage()
{
  // Setup a dummy plan, this should actually be done as a result of some
  // GUI action (like selecting a router or flashing method). Other than
  // this API, wizard steps should use standard Qt wizard API (eg. for
  // validation, marking fields as mandatory, marking pages as points of
  // no return, ...).
  plan()->append("sample-1");
  plan()->append("sample-2");
  plan()->append("sample-3");
}

