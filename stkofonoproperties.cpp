/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#include "stkofonoproperties.h"

#include <QDebug>

StkOfonoProperties::StkOfonoProperties(StkIf *stkIf, SimIf *simIf,
                                       QObject *parent)
    : QObject(parent), mStkIf(stkIf), mSimIf(simIf)
{
}

StkOfonoProperties::~StkOfonoProperties()
{
}

QString StkOfonoProperties::mainMenuTitle() const
{
    Q_UNUSED(mStkIf)
    Q_UNUSED(mSimIf)
    return QStringLiteral(MAIN_MENU_TITLE);
}

QString StkOfonoProperties::mainMenuIconUrl() const
{
    Q_UNUSED(mStkIf)
    Q_UNUSED(mSimIf)
    return QStringLiteral("image://simimage/sim_32x32.png");
}

QVector<StkMenuItem> StkOfonoProperties::mainMenuItems() const
{
    Q_UNUSED(mStkIf)
    Q_UNUSED(mSimIf)

    // Placeholder menu items - will be populated from oFono SIM Toolkit
    // when D-Bus integration is complete
    QVector<StkMenuItem> items;
    items.append({"SIM Contacts", "image://simimage/contact.png"});
    items.append({"SIM Messages", "image://simmessage/message.png"});
    items.append({"SIM Services", "image://simimage/service.png"});
    return items;
}
