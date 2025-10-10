#include "BackendsModel.hpp"

#include <QQmlEngine>

BackendsModel::BackendsModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int BackendsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _backends.count();
}

QVariant BackendsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= _backends.size()) {
        return {};
    }

    const auto& backend = _backends.at(index.row());

    switch (static_cast<BackendsModel::Role>(role)) {
    case BackendsModel::Role::Name: return QString::fromStdString(backend.name);
    case BackendsModel::Role::DllPath:  return QString(backend.dllLocation.c_str());
    default: return {};
    }
}

QHash<int, QByteArray> BackendsModel::roleNames() const
{
    return {
        { static_cast<int>(BackendsModel::Role::Name), "name" },
        { static_cast<int>(BackendsModel::Role::DllPath), "dllPath" }
    };
}

void BackendsModel::setData(const std::vector<Where::BackendInfo>& vec) noexcept
{
    if (vec.empty()) {
        return;
    }

    _backends.clear();

    beginInsertRows(QModelIndex(), 0, 0);

    for (const auto& info : vec) {
        _backends.push_back(info);
    }

    endInsertRows();
}

void BackendsModel::registerType()
{
    qmlRegisterUncreatableType<BackendsModel>("BackendsModel", 1, 0, "BackendsModel", "Use from C++");
}
