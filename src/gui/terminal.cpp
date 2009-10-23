
#include "terminal.h"

TerminalOutput::TerminalOutput(QWidget *parent) : QTextEdit(parent)
{
  setBufferSize(1024 * 10);
}

TerminalOutput::TerminalOutput(const TerminalOutput &object) : QTextEdit(object.parentWidget()) {
  setBufferSize(object.m_bufferSize);
}

void TerminalOutput::setBufferSize(int size) {
  if (size < 1)
    return;

  m_bufferSize = size;
  updateBuffer();
}

void TerminalOutput::append( const QString &text ) {
  m_buffer.append(text);
  updateBuffer();
}

void TerminalOutput::clear() {
  m_buffer.clear();
  updateBuffer();
}

void TerminalOutput::updateBuffer() {
  if (m_buffer.size() > m_bufferSize) {
    int offset = m_buffer.size() - m_bufferSize;
    int crop = m_buffer.indexOf('\n', offset);
    m_buffer = m_buffer.remove(0, crop);
  }

  document()->setPlainText(m_buffer);

}
