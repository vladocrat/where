#include "ApplicationController.hpp"

#include <QQmlApplicationEngine>

#include <backends/BackendEnumerator.hpp>
#include <backends/BackendInfo.hpp>
#include <backends/BackendLibrary.hpp>
#include <backends/Backend.hpp>
#include <backends/BackendController.hpp>

#include "SearchController.hpp"
#include "SearchResultModel.hpp"

namespace Where
{

struct ApplicationController::Impl
{
    QQmlApplicationEngine engine;
    //SearchController search;
    //SearchResultModel model;
};

ApplicationController::ApplicationController(int& argc, char** argv)
    : QGuiApplication(argc, argv)
    , _impl{std::make_unique<Impl>()}
{
    SearchController::registerType();
    SearchResultModel::registerType();

    //_impl->engine.setObjectOwnership(&_impl->search, QQmlEngine::CppOwnership);
    //_impl->engine.setObjectOwnership(&_impl->model, QQmlEngine::CppOwnership);

    QObject::connect(SearchController::instance(), &SearchController::searchFinished, this, [this](const auto& files) {
        qDebug() << files.size();

        //_impl->model.setData(files);
        SearchResultModel::instance()->setData(files);
    });


    QObject::connect(SearchController::instance(), &SearchController::clear, this, [this]() {
        SearchResultModel::instance()->clear();
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
