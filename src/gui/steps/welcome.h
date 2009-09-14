/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_WELCOMESTEP_H
#define GUI_STEPS_WELCOMESTEP_H

#include "gui/wizard.h"
#include "gui/ui_welcome.h"

/**
 * The initial welcome step.
 */
class WelcomeStep : public Step {
    Q_OBJECT
public:
    /**
     * Class constructor.
     */
    WelcomeStep();
private:
    // Welcome step GUI layout
    Ui::WelcomeStep m_ui;
};

#endif
