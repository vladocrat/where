#include "ApplicationController.hpp"

#include <QQmlApplicationEngine>

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
