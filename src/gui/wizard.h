/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef GUI_FLASHWIZARD_H
#define GUI_FLASHWIZARD_H

#include <QWizard>
#include <QMap>
#include <QList>

class Step;

// Our plan type
typedef QList<QString> Plan;

/**
 * The main wizard of our firmware flasher. It is designed to guide
 * the user through firmware flashing process.
 */
class FlashWizard : public QWizard {
    Q_OBJECT
public:
    /**
     * Class constructor.
     */
    FlashWizard();
    
    /**
     * Adds a page to our wizard.
     *
     * @param page A valid Step instance
     */
    void addPage(Step *page);
    
    /**
     * Returns the next page identifier according to a preset forward
     * plan.
     */
    int nextId() const;
    
    /**
     * Returns the plan.
     */
    Plan *getPlan() const;

protected slots:

    void handlePageChange(int id);

    void handleCustomButton(int id);

private:
    // Mapping between string page ids and numeric ids
    QMap<QString, int> m_steps;
    
    // The wizard plan
    Plan m_plan;
};

/**
 * A step is simply an extension of a generic QWizardPage that adds
 * string-based identifiers.
 */
class Step : public QWizardPage {
    Q_OBJECT
public:
    /**
     * Class constructor.
     *
     * @param id Unique step identifier
     */
    Step(const QString &id);
    
    /**
     * Class destructor.
     */
    virtual ~Step();
    
    /**
     * Returns this step's identifier.
     */
    QString getId() const;

    /**
     * Returns true if this step can provide more information. A "More" button is displayed by the wizard,
     * clicking it triggers toggleMoreInformation function. The default implementation returns false.
     */
    virtual bool hasMoreInformation();

    /**
     * If overriden, this function handles toggling of more/less information verbosity of the slide. The
     * default implementation always returns false.
     */
    virtual bool toggleMoreInformation();

    /**
     * Returns the current more/less information verbosity state of the slide. The
     * default implementation always returns false.
     */
    virtual bool testMoreInformation();

protected:
    /**
     * A convenience method for accessing the flash wizard instance.
     */
    FlashWizard *flashWizard() const;
    
    /**
     * Returns a modifiable plan.
     */
    Plan *plan() const;

private:
    // Step identifier
    QString m_id;
};

#endif
