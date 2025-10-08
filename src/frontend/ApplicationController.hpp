#pragma once

#include <QGuiApplication>

#include <filesystem>
#include <memory>

namespace Where
{

class ApplicationController : public QGuiApplication
{
    Q_OBJECT
public:
    ApplicationController(int& argc, char** argv);
    ~ApplicationController();

    void loadQml(const std::filesystem::path& path) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}
