/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 *
 * oFono D-Bus types registration.
 */

#ifndef OFONODBUSTYPES_H
#define OFONODBUSTYPES_H

#include <QtDBus/QDBusAbstractInterface>
#include <QtDBus/QDBusArgument>
#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusVariant>
#include <QtDBus/QDBusMessage>
#include <QtCore/QVariantMap>
#include <QtCore/QList>

typedef QList<QDBusObjectPath> OfonoModemList;
typedef QList<QDBusObjectPath> OfonoSimList;
typedef QList<QDBusObjectPath> OfonoStkList;

void registerOfonoDbusTypes();

// Forward declarations for D-Bus interfaces (generated from oFono XML)
class MgrIf : public QDBusAbstractInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.Manager")
public:
    explicit MgrIf(const QString &service, const QString &path,
                   const QDBusConnection &connection, QObject *parent = nullptr)
        : QDBusAbstractInterface(service, path, "org.ofono.Manager", connection, parent) {}
    ~MgrIf() override {}

Q_SIGNALS:
    void modemAdded(const QDBusObjectPath &path, const QVariantMap &properties);
    void modemRemoved(const QDBusObjectPath &path);
};

class ModemIf : public QDBusAbstractInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.Modem")
public:
    explicit ModemIf(const QString &service, const QString &path,
                     const QDBusConnection &connection, QObject *parent = nullptr)
        : QDBusAbstractInterface(service, path, "org.ofono.Modem", connection, parent) {}
    ~ModemIf() override {}

Q_SIGNALS:
    void propertyChanged(const QString &property, const QDBusVariant &value);
};

class SimIf : public QDBusAbstractInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.SimManager")
public:
    explicit SimIf(const QString &service, const QString &path,
                   const QDBusConnection &connection, QObject *parent = nullptr)
        : QDBusAbstractInterface(service, path, "org.ofono.SimManager", connection, parent) {}
    ~SimIf() override {}

Q_SIGNALS:
    void propertyChanged(const QString &property, const QDBusVariant &value);
};

class StkIf : public QDBusAbstractInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.SimToolkit")
public:
    explicit StkIf(const QString &service, const QString &path,
                   const QDBusConnection &connection, QObject *parent = nullptr)
        : QDBusAbstractInterface(service, path, "org.ofono.SimToolkit", connection, parent) {}
    ~StkIf() override {}

Q_SIGNALS:
    void propertyChanged(const QString &property, const QDBusVariant &value);
public Q_SLOTS:
    QDBusMessage SelectItem(uchar selection, const QDBusObjectPath &agentPath);
};

#endif // OFONODBUSTYPES_H
