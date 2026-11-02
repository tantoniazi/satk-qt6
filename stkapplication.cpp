/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.
 */

#include "stkapplication.h"
#include "stkofonoutils.h"
#include "stkagentservice.h"

#include <QIcon>
#include <QPixmap>
#include <QDBusConnection>
#include <QDebug>


StkApplication::StkApplication(int &argc, char **argv, int version)
    : QApplication(argc, argv, version)
{
    mAgentServiceRegistered = mAgentMode = false;
    mStkAgentService = nullptr;
    mMgrIf = nullptr;
    mModemIf = nullptr;
    mSimIf = nullptr;
    mStkIf = nullptr;
    setWindowIcon(QIcon::fromTheme("dialog-information"));
}

StkApplication::~StkApplication()
{
    deleteInterfaces();
}

void StkApplication::resetInterfaces()
{
    // Unregister StkAgentService if we registered it
    if (mAgentServiceRegistered)
        StkOfonoUtils::unRegisterSimToolkitAgent(mStkIf);

    // Disconnect all signals sent from oFono interfaces
    if (mMgrIf) {
        disconnect(mMgrIf, &MgrIf::modemAdded, this,
                   &StkApplication::mgrModemAdded);
        disconnect(mMgrIf, &MgrIf::modemRemoved, this,
                   &StkApplication::mgrModemRemoved);
    }
    if (mModemIf)
        disconnect(mModemIf, &ModemIf::propertyChanged, this,
                   &StkApplication::modemPropertyChanged);
    if (mSimIf)
        disconnect(mSimIf, &SimIf::propertyChanged, this,
                   &StkApplication::simPropertyChanged);

    mModemIf = nullptr;
    mSimIf = nullptr;
    mStkIf = nullptr;
    mStkAgentService = nullptr;
    mAgentServiceRegistered = mAgentMode = false;
}

void StkApplication::deleteInterfaces()
{
    resetInterfaces();

    // delete all org.ofono.SimToolkit interfaces
    qDeleteAll(mStkIfs);
    mStkIfs.clear();

    // delete all org.ofono.SimManager interfaces
    qDeleteAll(mSimIfs);
    mSimIfs.clear();

    // delete all org.ofono.Modem interfaces
    qDeleteAll(mModemIfs);
    mModemIfs.clear();

    if (mMgrIf) {
        delete mMgrIf;
        mMgrIf = nullptr;
    }
}

bool StkApplication::initOfonoConnection(bool agentMode)
{
    deleteInterfaces();
    mAgentMode = agentMode;

    QDBusConnection connection = QDBusConnection::systemBus();
    if (!connection.isConnected()) {
        QDBusError dbusError = connection.lastError();
        qDebug() << "Error:" << dbusError.name() << ":" << dbusError.message();
        return false;
    }

    // Instanciate proxy for org.ofono.Manager interface
    mMgrIf = new MgrIf("org.ofono", "/", connection, nullptr);

    // find all modems
    OfonoModemList modems = StkOfonoUtils::findModems(mMgrIf);
    if (modems.isEmpty()) {
        qDebug() << "No modem found, registering for modem add / removed";
        registerModemMgrChanges();
        return false;
    }

    // find org.ofono.Modem interfaces
    mModemIfs = StkOfonoUtils::findModemInterfaces(connection, mMgrIf);
    if (mModemIfs.isEmpty()) {
        qDebug() << "No modem interface found, registering for modem add / removed";
        registerModemMgrChanges();
        return false;
    }
    mModemIf = mModemIfs.first();

    // find org.ofono.SimManager interfaces for all modems
    mSimIfs = StkOfonoUtils::findSimInterfaces(connection, mMgrIf);
    if (mSimIfs.isEmpty()) {
        qDebug() << "No SIM interface found, registering for Modem property changes";
        registerModemPropertyChanged();
        return false;
    }
    mSimIf = mSimIfs.first();

    // find org.ofono.SimToolkit interfaces for all modems
    mStkIfs = StkOfonoUtils::findSimToolkitInterfaces(connection, mMgrIf);
    if (mStkIfs.isEmpty()) {
        qDebug() << "No SIM Toolkit interface found, registering for SIM property changes";
        registerSimPropertyChanged();
        return false;
    }
    mStkIf = mStkIfs.first();

    // Create StkAgentService
    mStkAgentService = new StkAgentService(mSimIf);

    // Register agent service
    mAgentServiceRegistered = registerStkAgentService();

    if (mAgentMode)
        setQuitOnLastWindowClosed(false);

    return true;
}

bool StkApplication::registerModemMgrChanges()
{
    bool reg1 = connect(mMgrIf, &MgrIf::modemAdded, this,
                        &StkApplication::mgrModemAdded);
    bool reg2 = connect(mMgrIf, &MgrIf::modemRemoved, this,
                        &StkApplication::mgrModemRemoved);
    return reg1 && reg2;
}

bool StkApplication::registerModemPropertyChanged()
{
    return connect(mModemIf, &ModemIf::propertyChanged, this,
                   &StkApplication::modemPropertyChanged);
}

bool StkApplication::registerSimPropertyChanged()
{
    return connect(mSimIf, &SimIf::propertyChanged, this,
                   &StkApplication::simPropertyChanged);
}

bool StkApplication::registerStkAgentService()
{
    if (mStkAgentService == nullptr || mStkIf == nullptr)
        return false;
    QDBusConnection connection = QDBusConnection::systemBus();
    if (StkOfonoUtils::registerSimToolkitAgent(connection, mStkAgentService,
                                               mStkIf) != 0)
        return false;
    return true;
}

void StkApplication::unRegisterStkAgentService()
{
    StkOfonoUtils::unRegisterSimToolkitAgent(mStkIf);
}

void StkApplication::mgrModemAdded(const QDBusObjectPath &path,
                                   const QVariantMap &properties)
{
    Q_UNUSED(properties)
    qDebug() << "mgrModemAdded:" << path.path();
    initOfonoConnection(mAgentMode);
}

void StkApplication::mgrModemRemoved(const QDBusObjectPath &path)
{
    Q_UNUSED(path)
    qDebug() << "mgrModemRemoved:" << path.path();
    initOfonoConnection(mAgentMode);
}

void StkApplication::modemPropertyChanged(const QString &property,
                                          const QDBusVariant &value)
{
    Q_UNUSED(property)
    Q_UNUSED(value)
    qDebug() << "modemPropertyChanged";
    initOfonoConnection(mAgentMode);
}

void StkApplication::simPropertyChanged(const QString &property,
                                        const QDBusVariant &value)
{
    Q_UNUSED(property)
    Q_UNUSED(value)
    qDebug() << "simPropertyChanged";
    initOfonoConnection(mAgentMode);
}
