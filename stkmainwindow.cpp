/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#include "stkmainwindow.h"
#include "stkmenumodel.h"
#include "stkdefines.h"
#include "simimageprovider.h"
#include "ofonodbustypes.h"

#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDBusConnection>
#include <QDebug>

StkMainWindow::StkMainWindow(StkIf *stkIf, SimIf *simIf,
                             StkAgentService *stkAgentService,
                             QWidget *parent)
    : QMainWindow(parent)
{
    mStkIf = stkIf;
    mSimIf = simIf;
    mStkAgentService = stkAgentService;

    createMainView();

    connect(mStkIf, &StkIf::propertyChanged, this,
            &StkMainWindow::stkPropertyChanged);
}

StkMainWindow::~StkMainWindow()
{
    delete mStkProperties;
    // mView is deleted as QMainWindow's centralWidget
}

void StkMainWindow::onEndSession()
{
    if (mStkAgentService)
        mStkAgentService->setExitOnRelease(true);
    close();
}

void StkMainWindow::responseOkWithSelection(int selection)
{
    uchar sel = static_cast<uchar>(selection);
    QDBusObjectPath stkAgentPath(STK_AGENT_PATH);
    if (mStkIf)
        mStkIf->SelectItem(sel, stkAgentPath);
}

void StkMainWindow::stkPropertyChanged(const QString &property,
                                       const QDBusVariant &value)
{
    Q_UNUSED(property);
    Q_UNUSED(value);

    // save properties and view for deletion
    auto delStkProperties = mStkProperties;
    auto delView = mView;

    // reload properties, recreate main view
    createMainView();

    // delete old view and properties
    delete delStkProperties;
    delete delView;
}

void StkMainWindow::createMainView()
{
    mStkProperties = new StkOfonoProperties(mStkIf, mSimIf);

    mView = new QQuickView;
    QQmlEngine *engine = mView->engine();
    engine->addImageProvider(QLatin1String(SIM_IMAGE_PROVIDER),
                             new SimImageProvider(mSimIf));

    mView->setSource(QUrl(QStringLiteral("qrc:/StkMenu.qml")));
    mView->setResizeMode(QQuickView::SizeRootObjectToView);
    setCentralWidget(mView);

    QObject *root = mView->rootObject();
    if (!root)
        return;

    QObject *icon = root->findChild<QObject *>(QStringLiteral("icon"));
    if (icon)
        icon->setProperty("source",
                          mStkProperties->mainMenuIconUrl());

    QObject *title = root->findChild<QObject *>(QStringLiteral("title"));
    if (title) {
        QString mainMenuTitle = mStkProperties->mainMenuTitle();
        if (!mainMenuTitle.isEmpty())
            title->setProperty("text", mainMenuTitle);
    }

    QQmlContext *context = mView->rootContext();
    StkMenuModel *menuModel = new StkMenuModel();
    menuModel->setMenuItems(mStkProperties->mainMenuItems());
    context->setContextProperty(QStringLiteral("menuModel"), menuModel);

    QObject *panel = root->findChild<QObject *>(QStringLiteral("panel"));
    if (panel)
        panel->setProperty("showBackButton", false);

    connect(root, SIGNAL(itemSelected(int)), this,
            SLOT(responseOkWithSelection(int)));
    connect(root, SIGNAL(endSession()), this, SLOT(onEndSession()));
}
