/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#include "stkagentservice.h"

#include <QDebug>

StkAgentService::StkAgentService(class SimIf *simIf, QObject *parent)
    : QObject(parent), mSimIf(simIf)
{
    Q_UNUSED(mSimIf)
}

StkAgentService::~StkAgentService()
{
}

void StkAgentService::setExitOnRelease(bool exit)
{
    mExitOnRelease = exit;
}

QDBusMessage StkAgentService::handleSetMenu(const QVariantMap &menu)
{
    Q_UNUSED(menu)
    qDebug() << "StkAgentService: handleSetMenu";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleSelectItem(uchar selection)
{
    Q_UNUSED(selection)
    qDebug() << "StkAgentService: handleSelectItem:" << selection;
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleSendText(const QString &text)
{
    Q_UNUSED(text)
    qDebug() << "StkAgentService: handleSendText";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleSendDtmf(const QString &dtmf)
{
    Q_UNUSED(dtmf)
    qDebug() << "StkAgentService: handleSendDtmf";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleDisplayText(const QString &text)
{
    Q_UNUSED(text)
    qDebug() << "StkAgentService: handleDisplayText";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleGetInput(const QString &text)
{
    Q_UNUSED(text)
    qDebug() << "StkAgentService: handleGetInput";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleGetInkey(const QString &text)
{
    Q_UNUSED(text)
    qDebug() << "StkAgentService: handleGetInkey";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handlePlayTone(const QString &tone)
{
    Q_UNUSED(tone)
    qDebug() << "StkAgentService: handlePlayTone";
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}

QDBusMessage StkAgentService::handleEndSession()
{
    qDebug() << "StkAgentService: handleEndSession";
    if (mExitOnRelease) {
        qDebug() << "Exit on release requested";
    }
    return QDBusMessage::createSuccessMessage(QDBusMessage());
}
