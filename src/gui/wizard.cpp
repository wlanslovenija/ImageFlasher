/*
 * wlan Ljubljana firmware flasher
 */
#include "gui/wizard.h"

FlashWizard::FlashWizard()
  : QWizard()
{
  setButtonText(QWizard::CustomButton1, tr("More"));

  connect( this, SIGNAL( currentIdChanged ( int ) ), this, SLOT( handlePageChange( int ) ) );
  connect( this, SIGNAL( customButtonClicked ( int ) ), this, SLOT( handleCustomButton( int ) ) );

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


void FlashWizard::handlePageChange(int id) {
  if (id < 0)
    return;

  Step *step = (Step*) currentPage();

  QList<QWizard::WizardButton> layout;
  layout << QWizard::Stretch << QWizard::BackButton << QWizard::NextButton <<
         QWizard::FinishButton << QWizard::CancelButton;

  if (step->hasMoreInformation()) {
    //setOption(QWizard::HaveCustomButton1, false);
    layout.prepend(QWizard::CustomButton1);
  } 

  setButtonLayout(layout);

  bool more = step->testMoreInformation();
  
  setButtonText(QWizard::CustomButton1, more ? tr("Less") : tr("More"));

}

void FlashWizard::handleCustomButton(int id) {
  if (id != QWizard::CustomButton1) 
    return;

  Step *step = (Step*) currentPage();

  if (!step->hasMoreInformation())
    return;

  bool more = step->toggleMoreInformation();
  
  setButtonText(QWizard::CustomButton1, more ? tr("Less") : tr("More"));
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

bool Step::hasMoreInformation() {
  return false;
}

bool Step::toggleMoreInformation() {
  return false;
}

bool Step::testMoreInformation() {
  return false;
}

