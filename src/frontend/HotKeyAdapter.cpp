#include "HotKeyAdapter.hpp"

#include <QThread>
#include <QCoreApplication>

#include "HotKeyHanlderWorker.hpp"

struct HotKeyAdapter::Impl
{
    HotKeyHandlerWorker worker;
    QThread thread;
};

HotKeyAdapter::HotKeyAdapter()
    : _impl{std::make_unique<Impl>()}
{
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, &_impl->thread, &QThread::quit, Qt::QueuedConnection);
    QObject::connect(&_impl->worker, &HotKeyHandlerWorker::finished, &_impl->thread, &QThread::quit, Qt::QueuedConnection);
    QObject::connect(&_impl->thread, &QThread::started, &_impl->worker, &HotKeyHandlerWorker::run, Qt::QueuedConnection);
    QObject::connect(&_impl->worker, &HotKeyHandlerWorker::actionTriggered, this, &HotKeyAdapter::actionTriggered, Qt::QueuedConnection);
}

HotKeyAdapter::~HotKeyAdapter()
{
    if (_impl->thread.isRunning()) {
        _impl->worker.stop();
        _impl->thread.quit();
        _impl->thread.wait(std::chrono::seconds(5));
    }
}

void HotKeyAdapter::start()
{
    _impl->worker.moveToThread(&_impl->thread);
    _impl->thread.start();
}
