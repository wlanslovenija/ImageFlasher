/*
 * wlan Ljubljana firmware flasher
 */
#include "backends/base.h"

Backend::Backend(const QString &name)
  : QObject(),
    m_name(name)
{
}

Backend *Backend::get(const QString &name)
{
  return Backend::m_backends.value(name);
}

void Backend::registerBackend(Backend *backend)
{
  Backend::m_backends[backend->getName()] = backend;
}

QString Backend::getName() const
{
  return m_name;
}

void Backend::setParameter(const QString &key, const QVariant &value)
{
  m_config[key] = value;
}
