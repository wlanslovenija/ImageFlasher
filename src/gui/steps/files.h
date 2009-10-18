/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_FILESSTEP_H
#define GUI_STEPS_FILESSTEP_H

#include "instructions.h"
#include "../filechooser.h"
#include <QFormLayout>
#include <QLabel>

typedef bool (*ValidatorCallback)(const QString &stepId);

class FilesList {
public:
    FilesList();
    ~FilesList();
    void addFile(const QString &title, bool required, ValidatorCallback validator);
    void addFile(const QString &title, bool required) { addFile(title, required, NULL); }
    int getCount();
    QString getTitle(int i);
    bool isRequired(int i);
    bool isValid(int i, const QString &file);
private:

    QList<bool> m_requiredList;
    QList<ValidatorCallback> m_validatorList;
    QStringList m_titleList;
};


/**
 * The instructions step.
 */
class FilesStep : public InstructionsStep {
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
    FilesStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image, FilesList &files);

    QString getFile(int i);

    virtual bool isComplete();
private:

    FilesList m_list;
    QList<FileChooser*> m_choosers;
    QWidget m_panel;

private slots:
    void fileNameChanged(const QString &file);
};

#endif
