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
    case SearchResultModel::Role::FileName: return QString::fromStdWString(result.fileName);
    case SearchResultModel::Role::FilePath: return QString::fromStdWString(result.fullFilePath.wstring());
    case SearchResultModel::Role::IsFolder: return result.isFolder;
    default: return {};
    }
}

QHash<int, QByteArray> SearchResultModel::roleNames() const
{
    return {
        { static_cast<int>(SearchResultModel::Role::FileName), "fileName" },
        { static_cast<int>(SearchResultModel::Role::FilePath), "filePath" },
        { static_cast<int>(SearchResultModel::Role::IsFolder), "isFolder" }
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

    _results.clear();

    beginInsertRows(QModelIndex(), 0, 0);

    for (const auto& file : searchResults) {
        _results.push_back(file);
    }

    endInsertRows();
}

void SearchResultModel::registerType()
{
    qmlRegisterUncreatableType<SearchResultModel>("SearchResultModel", 1, 0, "SearchResultModel", "Use from C++");
}
