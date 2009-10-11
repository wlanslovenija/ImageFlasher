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
  QString currentId = static_cast<Step*>(currentPage())->getId();
  int currentIdx = m_plan.indexOf(currentId);
  Plan::ConstIterator current = m_plan.begin() + currentIdx;
  
  // Check for invalid plans
  if (currentIdx == -1)
    qFatal("Current step (%s) cannot be found in active plan! Bailing out as this plan is invalid!", currentId.toAscii().data());
  
  // Check for last page
  if (current + 1 == m_plan.end())
    return -1;
  //printf("%d \n", m_currentStep);
  return m_steps[*(current + 1)];
}

Plan *FlashWizard::getPlan() const
{
  return const_cast<Plan*>(&m_plan);
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

