#ifndef FLASHWIZARD_H
#define FLASHWIZARD_H

#include <QtGui/QWizard>

namespace Ui {
    class FlashWizard;
}

class FlashWizard : public QWizard {
    Q_OBJECT
    Q_DISABLE_COPY(FlashWizard)
public:
    explicit FlashWizard(QWidget *parent = 0);
    virtual ~FlashWizard();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FlashWizard *m_ui;

private slots:
    void on_FlashWizard_currentIdChanged(int id);
};

#endif // FLASHWIZARD_H
