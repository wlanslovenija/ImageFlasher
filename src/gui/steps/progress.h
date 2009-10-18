/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_PROGRESSSTEP_H
#define GUI_STEPS_PROGRESSSTEP_H

#include "instructions.h"
#include <QProgressBar>


/**
 * The instructions step.
 */
class ProgressStep : public InstructionsStep {
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
    ProgressStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, int min = 0, int max = 100);

public slots:
    void setProgress(int progress);
    void setMessage(const QString &message);
private:
    QProgressBar m_progress;

};

#endif
