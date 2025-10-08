#pragma once

#include <QObject>

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
    void finished();

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};
