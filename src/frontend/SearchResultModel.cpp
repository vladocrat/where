#include "SearchResultModel.hpp"

#include <QQmlEngine>

int SearchResultModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _results.size();
}

QVariant SearchResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= _results.size()) {
        return {};
    }

    const auto& result = _results.at(index.row());

    switch (static_cast<SearchResultModel::Role>(role)) {
    case SearchResultModel::Role::FileNameRole: return QString::fromStdWString(result.fileName);
    case SearchResultModel::Role::FilePathRole:  return QString::fromStdWString(result.fullFilePath.wstring());
    default: return {};
    }
}

QHash<int, QByteArray> SearchResultModel::roleNames() const
{
    return {
        { static_cast<int>(SearchResultModel::Role::FileNameRole), "fileName" },
        { static_cast<int>(SearchResultModel::Role::FilePathRole), "filePath" }
    };
}

void SearchResultModel::clear()
{
    beginResetModel();
    _results.clear();
    endResetModel();
}

void SearchResultModel::setData(const std::vector<Backend::File>& searchResults)
{
    if (searchResults.empty()) {
        return;
    }

    beginResetModel();

    for (const auto& file : searchResults) {
        _results.push_back(file);
    }

    endResetModel();
}

void SearchResultModel::registerType()
{
    qmlRegisterSingletonInstance<SearchResultModel>("SearchResultModel", 1, 0, "SearchResultModel", SearchResultModel::instance());
}
