#include "ApplicationController.hpp"

#include <QQmlApplicationEngine>

#include "SearchController.hpp"
#include "SearchResultModel.hpp"
#include "ModelController.hpp"

namespace Where
{

struct ApplicationController::Impl
{
    QQmlApplicationEngine engine;
    ModelController modelController;
};

ApplicationController::ApplicationController(int& argc, char** argv)
    : QGuiApplication(argc, argv)
    , _impl{std::make_unique<Impl>()}
{
    qmlRegisterSingletonType<ModelController>("ModelController", 1, 0, "ModelController", [this](QQmlEngine*, QJSEngine*) -> QObject* {
        return &_impl->modelController;
    });

    SearchController::registerType();

    _impl->engine.setObjectOwnership(_impl->modelController.searchResultModel(), QQmlEngine::CppOwnership);
    _impl->engine.setObjectOwnership(_impl->modelController.backendsModel(), QQmlEngine::CppOwnership);

    QObject::connect(SearchController::instance(), &SearchController::searchFinished, this, [this](const auto& files) {
        qDebug() << files.size();
        _impl->modelController.searchResultModel()->setData(files);
    });

    QObject::connect(SearchController::instance(), &SearchController::clear, this, [this]() {
        _impl->modelController.searchResultModel()->clear();
    });
}

ApplicationController::~ApplicationController()
{

}

void ApplicationController::loadQml(const std::filesystem::path& path) noexcept
{
    QObject::connect(&_impl->engine, &QQmlApplicationEngine::objectCreationFailed, this, []() {
        QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    _impl->engine.loadFromModule("where", path.c_str());
}

}
