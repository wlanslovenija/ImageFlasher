/*
 * wlan Ljubljana firmware flasher
 */
#include "gui/wizard.h"

FlashWizard::FlashWizard()
  : QWizard()
{
  resize(640, 480);
    
  // Initialize the plan
  m_plan.append("init");
  m_currentStep = m_plan.begin();
  
  // Connect signals
  connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotStepChanged(int)));
}

void FlashWizard::addPage(Step *page)
{
  if (m_steps.contains(page->getId()))
    qFatal("Attempted registration of step with duplicate identifier '%s'!", page->getId().toAscii().data());
  
  int pageId = QWizard::addPage(page);
  m_steps[page->getId()] = pageId;
  
  // Ensure that we start with init
  if (page->getId() == "init")
    setStartId(pageId);
}

int FlashWizard::nextId() const
{
  if (m_currentStep + 1 == m_plan.end())
    return -1;
  
  return m_steps[*(m_currentStep + 1)];
}

Plan *FlashWizard::getPlan() const
{
  return const_cast<Plan*>(&m_plan);
}

void FlashWizard::slotStepChanged(int id)
{
  if (id == m_steps["init"]) {
    // Wizard started
    m_currentStep = m_plan.begin();
  } else if (id == -1) {
    // TODO Wizard aborted
  } else if (id == m_steps[*(m_currentStep + 1)]) {
    // We have moved forward
    m_currentStep++;
  } else if (id == m_steps[*(m_currentStep - 1)]) {
    // We have moved backward
    m_currentStep--;
  }
}

Step::Step(const QString &id)
  : QWizardPage(),
    m_id(id)
{
}

Step::~Step()
{
}

QString Step::getId() const
{
  return m_id;
}

FlashWizard *Step::flashWizard() const
{
  return static_cast<FlashWizard*>(QWizardPage::wizard());
}

Plan *Step::plan() const
{
  return flashWizard()->getPlan();
}

