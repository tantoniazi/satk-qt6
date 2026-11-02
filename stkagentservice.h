/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#ifndef STKAGENTSERVICE_H
#define STKAGENTSERVICE_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusObjectPath>

class StkAgentService : public QObject
{
    Q_OBJECT

public:
    explicit StkAgentService(class SimIf *simIf, QObject *parent = nullptr);
    ~StkAgentService() override;

    void setExitOnRelease(bool exit);
    bool exitOnRelease() const { return mExitOnRelease; }

public Q_SLOTS:
    QDBusMessage handleSetMenu(const QVariantMap &menu);
    QDBusMessage handleSelectItem(uchar selection);
    QDBusMessage handleSendText(const QString &text);
    QDBusMessage handleSendDtmf(const QString &dtmf);
    QDBusMessage handleDisplayText(const QString &text);
    QDBusMessage handleGetInput(const QString &text);
    QDBusMessage handleGetInkey(const QString &text);
    QDBusMessage handlePlayTone(const QString &tone);
    QDBusMessage handleEndSession();

private:
    class SimIf *mSimIf = nullptr;
    bool mExitOnRelease = false;
};

#endif // STKAGENTSERVICE_H
