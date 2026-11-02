#include "stkmainwindow.h"
#include "stkmenumodel.h"
#include "stkofonoproperties.h"
#include "stkdefines.h"
#include "simimageprovider.h"
#include "ofonodbustypes.h"

#include <QQmlEngine>
#include <QQmlContext>
#include <QDBusConnection>
#include <QDebug>
#include <QQuickItem>

StkMainWindow::StkMainWindow(StkIf *stkIf, SimIf *simIf,
                             StkAgentService *stkAgentService,
                             QWindow *parent)
    : QQuickView(parent)
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
}

void StkMainWindow::onEndSession()
{
    if (mStkAgentService)
        // StkAgentService doesn't have setExitOnRelease in this port
        Q_UNUSED(mStkAgentService);
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

    auto delStkProperties = mStkProperties;
    createMainView();
    delete delStkProperties;
}

void StkMainWindow::createMainView()
{
    mStkProperties = new StkOfonoProperties(mStkIf, mSimIf);

    QQmlEngine *engine = this->engine();
    engine->addImageProvider(QLatin1String(SIM_IMAGE_PROVIDER),
                             new SimImageProvider(mSimIf));

    this->setSource(QUrl(QStringLiteral("qrc:/StkMenu.qml")));
    this->setResizeMode(QQuickView::SizeRootObjectToView);

    QObject *root = this->rootObject();
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

    QQmlContext *context = this->rootContext();
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
