/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.
 */

#ifndef STKAPPLICATION_H
#define STKAPPLICATION_H

#include <QApplication>
#include <QDBusAbstractInterface>
#include <QDBusConnection>
#include <QList>

class StkAgentService;
class StkAgentIfAdaptor;

// Forward declarations for oFono D-Bus interfaces
class MgrIf;
class ModemIf;
class SimIf;
class StkIf;

class StkApplication : public QApplication
{
    Q_OBJECT

public:
    StkApplication(int &argc, char **argv, int version = 0);
    ~StkApplication();

    bool initOfonoConnection(bool agentMode);

    MgrIf *mgrIf() const { return mMgrIf; }
    ModemIf *modemIf() const { return mModemIf; }
    SimIf *simIf() const { return mSimIf; }
    StkIf *stkIf() const { return mStkIf; }
    StkAgentService *stkAgentService() const { return mStkAgentService; }
    bool agentServiceRegistered() const { return mAgentServiceRegistered; }

public slots:
    void mgrModemAdded(const QDBusObjectPath &path, const QVariantMap &properties);
    void mgrModemRemoved(const QDBusObjectPath &path);
    void modemPropertyChanged(const QString &property, const QDBusVariant &value);
    void simPropertyChanged(const QString &property, const QDBusVariant &value);

private:
    void resetInterfaces();
    void deleteInterfaces();
    bool registerModemMgrChanges();
    bool registerModemPropertyChanged();
    bool registerSimPropertyChanged();
    bool registerStkAgentService();
    void unRegisterStkAgentService();

    bool mAgentServiceRegistered = false;
    bool mAgentMode = false;

    class StkAgentIfAdaptor *mStkAgentIfAdaptor = nullptr;
    class StkAgentService *mStkAgentService = nullptr;

    MgrIf *mMgrIf = nullptr;
    QList<ModemIf *> mModemIfs;
    ModemIf *mModemIf = nullptr;
    QList<SimIf *> mSimIfs;
    SimIf *mSimIf = nullptr;
    QList<StkIf *> mStkIfs;
    StkIf *mStkIf = nullptr;
};

#endif // STKAPPLICATION_H
