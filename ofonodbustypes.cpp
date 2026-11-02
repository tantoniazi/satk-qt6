/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 *
 * oFono D-Bus types registration and interface implementations.
 */

#include "ofonodbustypes.h"
#include <QDBusConnection>
#include <QDebug>

void registerOfonoDbusTypes()
{
    // Register custom types for D-Bus marshalling
    qRegisterMetaType<QDBusObjectPath>("QDBusObjectPath");
    qRegisterMetaType<QVariantMap>("QVariantMap");
    qRegisterMetaType<QDBusVariant>("QDBusVariant");
}

QDBusMessage StkIf::SelectItem(uchar selection, const QDBusObjectPath &agentPath)
{
    Q_UNUSED(selection);
    Q_UNUSED(agentPath);
    qDebug() << "StkIf::SelectItem called - stub implementation";
    return QDBusMessage();
}
