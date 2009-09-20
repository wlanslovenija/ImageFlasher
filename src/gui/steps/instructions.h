/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_INSTRUCTIONSSTEP_H
#define GUI_STEPS_INSTRUCTIONSSTEP_H

#include "gui/wizard.h"
#include "gui/ui_instructions.h"

/**
 * The instructions step.
 */
class InstructionsStep : public Step {
    Q_OBJECT
public:
    /**
     * Class constructor.
     *
     * @param stepId Unique step identifier
     * @param title Instruction title
     * @param instructions Instruction text
     * @param image Image resource location
     */
    InstructionsStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image);
private:
    // Instructions step GUI layout
    Ui::InstructionsStep m_ui;
};

#endif
