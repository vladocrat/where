#pragma once

#include <QObject>

class HotKeyAdapter : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(HotKeyAdapter)
public:
    HotKeyAdapter();
    ~HotKeyAdapter();

    void start();

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

