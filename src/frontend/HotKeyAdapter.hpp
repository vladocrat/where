#pragma once

#include <QObject>

namespace Where::HotKey
{
enum class Action;
}

class HotKeyAdapter : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(HotKeyAdapter)
public:
    HotKeyAdapter();
    ~HotKeyAdapter();

    void start();

signals:
    void actionTriggered(const Where::HotKey::Action);

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

