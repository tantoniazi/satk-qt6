/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#include "simimageprovider.h"

#include <QImage>

SimImageProvider::SimImageProvider(SimIf *simIf)
    : QQuickImageProvider(QQuickImageProvider::Image), mSimIf(simIf)
{
}

SimImageProvider::~SimImageProvider()
{
}

QImage SimImageProvider::requestImage(const QString &id, QSize *size,
                                      const QSize &requestedSize)
{
    Q_UNUSED(mSimIf)
    Q_UNUSED(requestedSize)

    QImage image(64, 64, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    if (size)
        *size = image.size();

    return image;
}
