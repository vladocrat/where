#pragma once

#include <QAbstractListModel>

#include "backends/Backend.hpp"

class SearchResultModel : public QAbstractListModel
{
public:
    static SearchResultModel* instance()
    {
        static SearchResultModel rm;
        return &rm;
    }

    enum class Role {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole
    };
    Q_ENUM(Role)

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void clear();
    void setData(const std::vector<Backend::File>& searchResults);

    static void registerType();

private:
    QList<Backend::File> _results;
};

