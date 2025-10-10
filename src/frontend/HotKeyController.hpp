#pragma once

#include <QObject>

namespace Where::HotKey
{
enum class Action;
}

class HotKeyController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(HotKeyController)
public:
    HotKeyController();
    ~HotKeyController();

signals:
    void showSearchBar();

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

