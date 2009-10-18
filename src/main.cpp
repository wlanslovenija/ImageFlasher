#include <QtGui/QApplication>
#include "gui/wizard.h"

// Steps
#include "gui/steps/welcome.h"
#include "gui/steps/instructions.h"
#include "gui/steps/selection.h"
#include "gui/steps/files.h"
#include "gui/steps/progress.h"
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

  FilesList files;
  files.addFile("First file", true);
  files.addFile("Second file", true);

  // Initialize steps
  w.addPage(new WelcomeStep);
  w.addPage(new InstructionsStep("sample-1", "Sample Instructions", "This is a sample instruction page with a nice big image below. Niiice.", "state_power.png"));
  w.addPage(new SelectionStep("sample-2", "Sample selection", "Select option", "state_select.png", options));
  w.addPage(new FilesStep("sample-3", "Sample file form", "Fill the form", "state_select.png", files));
  w.addPage(new ProgressStep("sample-4", "Sample progress", "Progress", "state_install.png"));


  w.show();
  
  return a.exec();
}
