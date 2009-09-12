#include "wizard.h"
#include "ui_wizard.h"

FlashWizard::FlashWizard(QWidget *parent) :
    QWizard(parent),
    m_ui(new Ui::FlashWizard)
{
    m_ui->setupUi(this);
}

FlashWizard::~FlashWizard()
{
    delete m_ui;
}

void FlashWizard::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FlashWizard::on_FlashWizard_currentIdChanged(int id)
{
    printf("%d \n", id);
}
