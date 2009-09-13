/*
 * wlan Ljubljana firmware flasher
 **/
#ifndef BACKENDS_BASE_H
#define BACKENDS_BASE_H

#include <QObject>
#include <QMap>
#include <QVariant>

/**
 * An interface for a flasher backend.
 */
class Backend : public QObject {
    Q_OBJECT
public:
    /**
     * Class constructor.
     */
    Backend(const QString &name);
    
    /**
     * Finds a backend by its name and returns it. If no backend by
     * that name exists, this method will return NULL.
     *
     * @param name A valid backend name
     * @return Backend instance or NULL if none exists
     */
    static Backend *get(const QString &name);
    
    /**
     * Registers a new backend for later use.
     *
     * @param backend Backend instance to register
     */
    static void registerBackend(Backend *backend);
    
    /**
     * Returns a backend's name.
     */
    QString getName() const;
    
    /**
     * Sets a backend's parameter. Paramteres depend on backend
     * type.
     *
     * @param key Parameter name
     * @param value Parameter value
     */
    void setParameter(const QString &key, const QVariant &value);
    
    /**
     * Returns a parameter's value.
     *
     * @param key Parameter name
     * @param def Default value
     * @return Parameter value or default value when none exists
     */
    template <typename T>
    T getParameter(const QString &key, const T &def = T()) const
    {
      return m_config.contains(key) ? m_config[key].value<T>() : def;
    }
    
    /**
     * Executes the flashing procedure. This method should be overriden
     * by individual backends.
     */
    virtual void flash() {}
private:
    // Backend registry
    static QMap<QString, Backend*> m_backends;
    
    // Unique backend identifier
    QString m_name;
    
    // Current backend configuration
    QMap<QString, QVariant> m_config;
};

#endif
