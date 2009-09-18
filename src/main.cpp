#include <QtGui/QApplication>
#include "gui/wizard.h"

// Steps
#include "gui/steps/welcome.h"
#include "gui/steps/instructions.h"

/**
 * Program entry point.
 */
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  // Flash wizard is our main widget that goes through the whole
  // firmware flashing process.
  FlashWizard w;
  
  // Initialize steps
  w.addPage(new WelcomeStep);
  w.addPage(new InstructionsStep("Sample 1", "This is a sample instruction page with a nice big image below. Niiice.", "state_power.png"));
  w.addPage(new InstructionsStep("Sample 2", "This is a second sample instruction page with a nice big image below. Veeery niiice.", "state_install.png"));
  w.show();
  return a.exec();
}
