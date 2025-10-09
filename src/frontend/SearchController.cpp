#include "SearchController.hpp"

#include <QQmlEngine>

SearchController::SearchController()
{

}

void SearchController::search(const QString& query)
{
    const auto res = backend.search(query.toStdString());

    if (!res) {
        emit error();
    }

    emit searchFinished(res.value());
}

void SearchController::registerType()
{
    qmlRegisterSingletonInstance<SearchController>("SearchController", 1, 0, "SearchController", SearchController::instance());
}
