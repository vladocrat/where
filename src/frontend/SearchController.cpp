#include "SearchController.hpp"

#include <QQmlEngine>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QClipboard>

SearchController::SearchController()
{

}

void SearchController::search(const QString& query)
{
    const auto res = backend.search(query.toStdWString());

    if (!res) {
        emit error();
        return;
    }

    emit searchFinished(res.value());
}

void SearchController::open(const QString& filePath)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void SearchController::copy(const QString& filePath)
{
    const auto clipboard = qApp->clipboard();
    clipboard->setText(filePath);
}

void SearchController::registerType()
{
    qmlRegisterSingletonInstance<SearchController>("SearchController", 1, 0, "SearchController", SearchController::instance());
}
