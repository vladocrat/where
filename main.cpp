#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/frontend/ApplicationController.hpp>

int main(int argc, char *argv[])
{
    Where::ApplicationController app(argc, argv);
    app.loadQml("Main");

    return app.exec();
}
