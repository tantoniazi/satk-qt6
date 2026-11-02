/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#include "stkofonoutils.h"

#include <QDebug>

class StkAgentService;

OfonoModemList StkOfonoUtils::findModems(MgrIf *mgrIf)
{
    Q_UNUSED(mgrIf)
    // In a full implementation, this would call GetModems() on org.ofono.Manager
    // and return the list of modem object paths.
    return OfonoModemList();
}

QList<ModemIf *> StkOfonoUtils::findModemInterfaces(const QDBusConnection &conn,
                                                    MgrIf *mgrIf)
{
    Q_UNUSED(conn)
    Q_UNUSED(mgrIf)
    return QList<ModemIf *>();
}

QList<SimIf *> StkOfonoUtils::findSimInterfaces(const QDBusConnection &conn,
                                                MgrIf *mgrIf)
{
    Q_UNUSED(conn)
    Q_UNUSED(mgrIf)
    return QList<SimIf *>();
}

QList<StkIf *> StkOfonoUtils::findSimToolkitInterfaces(
    const QDBusConnection &conn, MgrIf *mgrIf)
{
    Q_UNUSED(conn)
    Q_UNUSED(mgrIf)
    return QList<StkIf *>();
}

int StkOfonoUtils::registerSimToolkitAgent(const QDBusConnection &conn,
                                           StkAgentService *service,
                                           StkIf *stkIf)
{
    Q_UNUSED(conn)
    Q_UNUSED(service)
    Q_UNUSED(stkIf)
    qDebug() << "StkOfonoUtils::registerSimToolkitAgent - stub";
    return 0;
}

void StkOfonoUtils::unRegisterSimToolkitAgent(StkIf *stkIf)
{
    Q_UNUSED(stkIf)
    qDebug() << "StkOfonoUtils::unRegisterSimToolkitAgent - stub";
}
