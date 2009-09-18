/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_INSTRUCTIONSSTEP_H
#define GUI_STEPS_INSTRUCTIONSSTEP_H

#include "gui/wizard.h"
#include "gui/ui_instructions.h"

/**
 * The initial welcome step.
 */
class InstructionsStep : public Step {
    Q_OBJECT
public:
    /**
     * Class constructor.
     */
    InstructionsStep(QString title, QString instructions, QString image);
private:
    // Welcome step GUI layout
    Ui::InstructionsStep m_ui;
};

#endif
