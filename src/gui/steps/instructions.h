/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_INSTRUCTIONSSTEP_H
#define GUI_STEPS_INSTRUCTIONSSTEP_H

#include "gui/wizard.h"
#include "gui/ui_instructions.h"

/**
 * The instructions step class. Simple step with title, text instructions and an optional image that is displayed
 * centered in the area below the text. This class is also the foundation for several more complex step classes.
 */
class InstructionsStep : public Step {
    Q_OBJECT
public:
    /**
     * Class constructor.
     *
     * @param stepId Unique step identifier
     * @param title Instructions step title
     * @param instructions Instructions text
     * @param image Image resource location
     */
    InstructionsStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image);
protected:
    /**
     * Inserts an additional widget to the step. The widget is inserted below the text (and above the optional image).
     *
     * @param widget The widget to add.
     */
    void addWidget(QWidget* widget);


protected:
    // Instructions step GUI layout
    Ui::InstructionsStep m_ui;
};

#endif
