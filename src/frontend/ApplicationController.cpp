#include "ApplicationController.hpp"

#include <QQmlApplicationEngine>

#include <backends/BackendEnumerator.hpp>
#include <backends/BackendInfo.hpp>
#include <backends/BackendLibrary.hpp>
#include <backends/Backend.hpp>

namespace Where
{

struct ApplicationController::Impl
{
    QQmlApplicationEngine engine;
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

    BackendLibrary lib;
    qDebug() << backends.value()[0].dllLocation.string().c_str();

    if (!lib.load(backends.value()[0])) {
        qDebug() << ":(";
    }

    auto backend = lib.create();
    backend->executeTask();
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
