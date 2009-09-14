/*
 * wlan Ljubljana firmware flasher
 */
#include "gui/wizard.h"

FlashWizard::FlashWizard()
  : QWizard()
{
  // Initialize forward plan
  m_forwardPlan.push("init");
  
  // Connect signals
  connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotStepChanged(int)));
}

void FlashWizard::addPage(Step *page)
{
  int pageId = QWizard::addPage(page);
  m_steps[page->getId()] = pageId;
  
  // Ensure that we start with init
  if (page->getId() == "init")
    setStartId(pageId);
}

int FlashWizard::nextId() const
{
  return m_steps[m_forwardPlan.top()];
}

Plan *FlashWizard::getForwardPlan() const
{
  return const_cast<Plan*>(&m_forwardPlan);
}

void FlashWizard::slotStepChanged(int id)
{
  if (id == m_steps[m_forwardPlan.top()]) {
    // We have moved forward, update plans
    QString stepId = m_forwardPlan.pop();
    m_backwardPlan.push(stepId);
  } else if (id == m_steps[m_backwardPlan.top()]) {
    // We have moved backward, update plans
    QString stepId = m_backwardPlan.pop();
    m_forwardPlan.push(stepId);
  } else {
    // Unplanned manual move, we are dead
    qWarning("Unplanned manual wizard move!");
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
  return flashWizard()->getForwardPlan();
}

