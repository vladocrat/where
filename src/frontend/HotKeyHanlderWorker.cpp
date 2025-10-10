#include "HotKeyHanlderWorker.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

#include <QDebug>

#include <core/HotKeyHandler.hpp>

struct HotKeyHandlerWorker::Impl
{
    std::unique_ptr<Where::HotKey::HotKeyHandler> handler;
};

HotKeyHandlerWorker::HotKeyHandlerWorker()
    : _impl{std::make_unique<Impl>()}
{

}

HotKeyHandlerWorker::~HotKeyHandlerWorker()
{

}

void HotKeyHandlerWorker::run()
{
    _impl->handler = std::make_unique<Where::HotKey::HotKeyHandler>();
    Where::HotKey::HotKeyEntry entry;
    entry.action = Where::HotKey::Action::SHOW_SEARCH_BAR;
    entry.key = VK_F1;
    entry.mode = Where::HotKey::Mode::NO_REPEAT;
    qDebug() << "starting";
    qDebug() << _impl->handler->setHandler(entry, [this, action = entry.action]() {
        emit actionTriggered(action);
    });

    _impl->handler->start();
}

void HotKeyHandlerWorker::stop()
{
    qDebug() << "stopping";
    _impl->handler->stop();
    emit finished();
}

