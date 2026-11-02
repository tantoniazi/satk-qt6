/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#ifndef STKOFONOUTILS_H
#define STKOFONOUTILS_H

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusObjectPath>
#include <QtCore/QVariantMap>
#include "ofonodbustypes.h"

class StkAgentService;

class StkOfonoUtils
{
public:
    static OfonoModemList findModems(MgrIf *mgrIf);
    static QList<ModemIf *> findModemInterfaces(const QDBusConnection &conn,
                                                MgrIf *mgrIf);
    static QList<SimIf *> findSimInterfaces(const QDBusConnection &conn,
                                            MgrIf *mgrIf);
    static QList<StkIf *> findSimToolkitInterfaces(const QDBusConnection &conn,
                                                   MgrIf *mgrIf);

    static int registerSimToolkitAgent(const QDBusConnection &conn,
                                       StkAgentService *service,
                                       StkIf *stkIf);
    static void unRegisterSimToolkitAgent(StkIf *stkIf);
};

#endif // STKOFONOUTILS_H
