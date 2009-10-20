/*
 * wlan Ljubljana firmware flasher
 **/
#include "gui/steps/instructions.h"

InstructionsStep::InstructionsStep(const QString &stepId, const QString &title, const QString &instructions, const QString &image)
  : Step(stepId)
{
  setTitle(title);
  
  m_ui.setupUi(this);
  m_ui.instructions->setText(instructions);

  if (image != NULL) {
    QString* html = new QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"> \
<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; } \
</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\"> \
<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/{{image}}\" /></p></body></html>");
    html->replace("{{image}}", image);
    m_ui.image->setText(*html);
  }
}

void InstructionsStep::addWidget(QWidget* widget)
{
  m_ui.container->addWidget(widget);
}

void InstructionsStep::addLayout(QLayout* layout)
{
  m_ui.container->addItem(layout);
}

