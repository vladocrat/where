#pragma once

#include <QObject>

namespace Where
{
namespace HotKey
{
enum class Action;
}
}

class HotKeyHandlerWorker : public QObject
{
    Q_OBJECT
public:
    HotKeyHandlerWorker();
    ~HotKeyHandlerWorker();

public slots:
    void run();
    void stop();

signals:
    void actionTriggered(const Where::HotKey::Action);
    void finished();

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};
