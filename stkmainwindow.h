#ifndef STKMAINWINDOW_H
#define STKMAINWINDOW_H

#include <QQuickView>
#include <QWindow>
#include <QTimer>
#include <QtDBus/QDBusVariant>

class StkIf;
class SimIf;
class StkAgentService;
class StkOfonoProperties;
class StkMenuModel;

class StkMainWindow : public QQuickView
{
    Q_OBJECT
public:
    explicit StkMainWindow(StkIf *stkIf, SimIf *simIf,
                           StkAgentService *stkAgentService,
                           QWindow *parent = nullptr);
    ~StkMainWindow() override;

private:
    void createMainView();

    StkIf *mStkIf = nullptr;
    SimIf *mSimIf = nullptr;
    StkAgentService *mStkAgentService = nullptr;
    class StkOfonoProperties *mStkProperties = nullptr;

signals:
    void requestExit();

private slots:
    void onEndSession();
    void responseOkWithSelection(int selection);
    void stkPropertyChanged(const QString &property, const QDBusVariant &value);
};

#endif // STKMAINWINDOW_H
