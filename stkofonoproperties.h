/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#ifndef STKOFONOPROPERTIES_H
#define STKOFONOPROPERTIES_H

#include <QObject>
#include <QString>
#include <QVector>
#include "stkmenumodel.h"

class StkIf;
class SimIf;

class StkOfonoProperties : public QObject
{
    Q_OBJECT

public:
    StkOfonoProperties(StkIf *stkIf, SimIf *simIf, QObject *parent = nullptr);
    ~StkOfonoProperties() override;

    QString mainMenuTitle() const;
    QString mainMenuIconUrl() const;
    QVector<StkMenuItem> mainMenuItems() const;

private:
    StkIf *mStkIf = nullptr;
    SimIf *mSimIf = nullptr;
};

#endif // STKOFONOPROPERTIES_H
