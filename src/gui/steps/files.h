/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_STEPS_FILESSTEP_H
#define GUI_STEPS_FILESSTEP_H

#include "gui/steps/instructions.h"
#include "gui/filechooser.h"

#include <QFormLayout>
#include <QLabel>

typedef bool (*ValidatorCallback)(const QString &stepId);

class FilesList {
public:
    FilesList();
    ~FilesList();
    void addFile(const QString &title, bool required, ValidatorCallback validator);
    void addFile(const QString &title, bool required);
    int getCount() const;
    QString getTitle(int i) const;
    bool isRequired(int i) const;
    bool isValid(int i, const QString &file) const;
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

    virtual bool isComplete() const;
private:
    FilesList m_list;
    QList<FileChooser*> m_choosers;
    QList<QLabel*> m_notices;
    QWidget *m_panel;
private slots:
    void fileNameChanged(const QString &file);
};

#endif
