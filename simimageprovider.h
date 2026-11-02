/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#ifndef SIMIMAGEPROVIDER_H
#define SIMIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class SimIf;

class SimImageProvider : public QQuickImageProvider
{
public:
    explicit SimImageProvider(SimIf *simIf);
    ~SimImageProvider() override;

    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize) override;

private:
    SimIf *mSimIf = nullptr;
};

#endif // SIMIMAGEPROVIDER_H
