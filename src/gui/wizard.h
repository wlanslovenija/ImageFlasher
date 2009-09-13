/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_FLASHWIZARD_H
#define GUI_FLASHWIZARD_H

#include <QtGui/QWizard>

#include "gui/ui_wizard.h"

/**
 * The main wizard of our firmware flasher. It is designed to guide
 * the user thorugh firmware flashing process.
 */
class FlashWizard : public QWizard {
    Q_OBJECT
public:
    /**
     * Ordered names of wizard pages for easier reference.
     */
    enum WizardPages {
      Invalid = -1,
      Intro = 0,
      RouterSelection,
      FirmwareSelection
    };
    
    /**
     * Class constructor.
     */
    FlashWizard();
private:
    Ui::FlashWizard m_ui;
private slots:
    /**
     * This slot gets called when the wizard's active page is changed.
     *
     * @param id The newly activated page
     */
    void slotCurrentIdChanged(int id);
};

#endif
