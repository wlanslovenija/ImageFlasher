/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_SELECTIONSTEP_H
#define GUI_STEPS_SELECTIONSTEP_H

#include "gui/steps/instructions.h"

class QComboBox;

/**
 * The instructions step.
 */
class SelectionStep : public InstructionsStep {
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
    SelectionStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, QStringList items);

    int getSelection();
private:
    QComboBox *m_selector;
};

#endif
