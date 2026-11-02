/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#include "stkmenumodel.h"

StkMenuModel::StkMenuModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

StkMenuModel::~StkMenuModel()
{
}

int StkMenuModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_menuItems.size();
}

QVariant StkMenuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_menuItems.size())
        return QVariant();

    const StkMenuItem &item = m_menuItems[index.row()];

    switch (role) {
    case TitleRole:
        return item.title;
    case IconRole:
        return item.icon;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> StkMenuModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[IconRole] = "icon";
    return roles;
}

void StkMenuModel::setMenuItems(const QVector<StkMenuItem> &items)
{
    beginResetModel();
    m_menuItems = items;
    endResetModel();
}
