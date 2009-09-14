#include <QtGui/QApplication>
#include "gui/wizard.h"

// Steps
#include "gui/steps/welcome.h"

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
  
  w.show();
  return a.exec();
}
