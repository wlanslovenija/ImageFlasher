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
 * the user thorugh firmware flashing process.
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
     * Returns the next page identifier accoording to a preset forward
     * plan.
     */
    int nextId() const;
    
    /**
     * Returns the plan.
     */
    Plan *getPlan() const;
private slots:
    /**
     * This slot gets called when the current step has changed.
     *
     * @param id New step identifier
     */
    void slotStepChanged(int id);
private:
    // Mapping between string page ids and numeric ids
    QMap<QString, int> m_steps;
    
    // The wizard plan
    Plan m_plan;
    Plan::Iterator m_currentStep;
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
