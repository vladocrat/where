#pragma once

#include "frontend/BackendsModel.hpp"
#include "frontend/SearchResultModel.hpp"

#include <QObject>

class SearchResultModel;
class BackendsModel;

class ModelController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SearchResultModel* searchResultModel READ searchResultModel NOTIFY searchResultModelChanged FINAL)
    Q_PROPERTY(BackendsModel* backendsModel READ backendsModel NOTIFY backendsModelChanged FINAL)

    Q_DISABLE_COPY_MOVE(ModelController)
public:
    ModelController();
    ~ModelController();

    SearchResultModel* searchResultModel() const noexcept;
    BackendsModel* backendsModel() const noexcept;

signals:
    void searchResultModelChanged();
    void backendsModelChanged();

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

