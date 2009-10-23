/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_PROGRESSSTEP_H
#define GUI_STEPS_PROGRESSSTEP_H

#include "gui/steps/instructions.h"
#include "../terminal.h"
#include <QProgressBar>

class ProgressBar : public QProgressBar {
    Q_OBJECT
public:
    ProgressBar(QWidget *parent = 0);

    virtual QString text() const;

    void setText(const QString &text);
private:
    QString m_text;


};


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

    virtual bool isComplete() const;

    void appendTerminalOutput(const QString &text);

    virtual bool hasMoreInformation();

    virtual bool toggleMoreInformation();

    virtual bool testMoreInformation();
public slots:
    void setProgress(int progress);
    void setMessage(const QString &message);
    void setBusy();
private:
    ProgressBar *m_progress;
    TerminalOutput m_terminal;
    int m_max, m_min;
};

#endif

