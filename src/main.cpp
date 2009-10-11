#include <QtGui/QApplication>
#include "gui/wizard.h"

// Steps
#include "gui/steps/welcome.h"
#include "gui/steps/instructions.h"
#include "gui/steps/selection.h"

/**
 * Program entry point.
 */
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  // Flash wizard is our main widget that goes through the whole
  // firmware flashing process.
  FlashWizard w;

  QStringList options;
  options.append("Fonera");
  options.append("Linksys");

  // Initialize steps
  w.addPage(new WelcomeStep);
  w.addPage(new InstructionsStep("sample-1", "Sample 1", "This is a sample instruction page with a nice big image below. Niiice.", "state_power.png"));
  w.addPage(new InstructionsStep("sample-2", "Sample 2", "This is a second sample instruction page with a nice big image below. Veeery niiice.", "state_install.png"));

  w.addPage(new SelectionStep("sample-3", "Sample 3", "Options", "state_select.png", options));
  w.show();
  
  return a.exec();
}
