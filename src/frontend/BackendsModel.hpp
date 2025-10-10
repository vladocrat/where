#pragma once

#include <QAbstractListModel>

#include "backends/BackendInfo.hpp"

class BackendsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum class Role
    {
        Name = Qt::UserRole + 1,
        DllPath
    };
    Q_ENUM(Role);

    static BackendsModel* instance()
    {
        static BackendsModel bm;
        return &bm;
    }

    BackendsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setData(const std::vector<Where::BackendInfo>& vec) noexcept;

    static void registerType();

private:
    QList<Where::BackendInfo> _backends;
};


