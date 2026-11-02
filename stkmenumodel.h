/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

#ifndef STKMENUMODEL_H
#define STKMENUMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QVector>

struct StkMenuItem {
    QString title;
    QString icon;
};

class StkMenuModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MenuRoles {
        TitleRole = Qt::UserRole + 1,
        IconRole
    };

    explicit StkMenuModel(QObject *parent = nullptr);
    ~StkMenuModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setMenuItems(const QVector<StkMenuItem> &items);

private:
    QVector<StkMenuItem> m_menuItems;
};

#endif // STKMENUMODEL_H
