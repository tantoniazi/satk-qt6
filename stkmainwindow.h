/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#ifndef STKMAINWINDOW_H
#define STKMAINWINDOW_H

#include <QMainWindow>
#include <QDeclarativeView>

class StkIf;
class SimIf;
class StkAgentService;

class StkMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    StkMainWindow(StkIf *stkIf, SimIf *simIf,
                  StkAgentService *stkAgentService, QWidget *parent = nullptr);
    ~StkMainWindow() override;

public Q_SLOTS:
    void onEndSession();
    void responseOkWithSelection(int selection);
    void stkPropertyChanged(const QString &property, const QDBusVariant &value);

private:
    void createMainView();

    StkIf *mStkIf = nullptr;
    SimIf *mSimIf = nullptr;
    StkAgentService *mStkAgentService = nullptr;
    class StkOfonoProperties *mStkProperties = nullptr;
    QQuickView *mView = nullptr;
};

#endif // STKMAINWINDOW_H
