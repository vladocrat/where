#include "ApplicationController.hpp"

#include <QQmlApplicationEngine>

#include <backends/BackendEnumerator.hpp>
#include <backends/BackendInfo.hpp>
#include <backends/BackendLibrary.hpp>
#include <backends/Backend.hpp>
#include <backends/BackendController.hpp>

namespace Where
{

struct ApplicationController::Impl
{
    QQmlApplicationEngine engine;
    BackendController backend;
};

ApplicationController::ApplicationController(int& argc, char** argv)
    : QGuiApplication(argc, argv)
    , _impl{std::make_unique<Impl>()}
{
    const auto backends = BackendEnumerator::enumerate(std::filesystem::current_path() / "backends.json");

    if (!backends) {
        qDebug() << "Failed to open backends file";
    }

    for (const auto& b : backends.value()) {
        qDebug() << b.name;
    }

    qDebug() << _impl->backend.backendsCount();
    const auto results = _impl->backend.search("logs");

    if (!results) {
        qDebug() << "Failed to fetch res";
    }

    for (size_t i = 0; i < results.value().size; i++) {
        qDebug() <<  results.value().files[i].fileName <<  results.value().files[i].fullFilePath.string();
    }
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
