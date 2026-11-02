/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.  The full text of the Apache License is at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Written by - Luc Yriarte <luc.yriarte@linux.intel.com>
 */

#include <QApplication>
#include <QDebug>
#include <QQuickView>
#include <QQmlEngine>
#include <QDBusConnection>

#include "ofonodbustypes.h"
#include "stkapplication.h"
#include "stkmainwindow.h"
#include "stkdefines.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Parse arguments
    if (argc > 2) {
        printf("%s\n", SATK_USAGE);
        return -1;
    }
    // Run in menu mode by default
    bool agentMode = false;
    if (argc == 2) {
        QString satkMode(argv[1]);
        if (satkMode == "agent") {
            agentMode = true;
        } else if (satkMode != "menu") {
            printf("%s\n", SATK_USAGE);
            return -1;
        }
    }

    // Register meta types defined in ofonodbustypes.h
    registerOfonoDbusTypes();

    StkApplication stkApp(argc, argv);

    // Initiate connection with oFono
    bool ofonoConnectionReady = stkApp.initOfonoConnection(agentMode);

    StkMainWindow *mainWindow = nullptr;
    if (agentMode) {
        // oFono connection can be deferred, but agent must be registered
        if (ofonoConnectionReady && !stkApp.agentServiceRegistered()) {
            qDebug() << "Error: cannot register agent service";
            return -1;
        }
    } else { // Main menu mode
        // Agent can be already registered, but
        // oFono connection must be up from the start
        if (!ofonoConnectionReady) {
            qDebug() << "Error: oFono connection not ready";
            return -1;
        }
        // hook Sim and Stk interfaces to the main window
        // Open SimToolkit main window in menu mode only
        mainWindow = new StkMainWindow(stkApp.stkIf(), stkApp.simIf(),
                                       stkApp.stkAgentService());
        mainWindow->show();
    }

    // Run SimToolkit application
    int ret = app.exec();

    if (mainWindow != nullptr)
        delete mainWindow;

    return ret;
}
