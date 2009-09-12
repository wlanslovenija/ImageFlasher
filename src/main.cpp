#include <QtGui/QApplication>
#include "gui/wizard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlashWizard w;
    w.show();
    return a.exec();
}
