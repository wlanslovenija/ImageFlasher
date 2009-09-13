#include <QtGui/QApplication>
#include "gui/wizard.h"

/**
 * Program entry point.
 */
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  // Flash wizard is our main widget that goes through the whole
  // firmware flashing process.
  FlashWizard w;
  w.show();
  
  return a.exec();
}
