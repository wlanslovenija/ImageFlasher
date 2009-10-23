
#ifndef GUI_TERMINALOUTPUT_H
#define GUI_TERMINALOUTPUT_H

#include <QTextEdit>

#ifndef A_CR
#define A_CR (13)
#endif

#ifndef A_LF
#define A_LF (10)
#endif

#ifndef A_BS
#define A_BS (8)
#endif

class TerminalOutput : public QTextEdit
{
  Q_OBJECT

public:
  TerminalOutput( QWidget *parent = 0);
  TerminalOutput(const TerminalOutput &object);

  void setBufferSize(int size);

public slots:
  void append( const QString &text );
  void clear();

private:
  void updateBuffer();
  int m_bufferSize;
  QString m_buffer;
  
};

#endif
