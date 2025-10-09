#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/frontend/ApplicationController.hpp>

int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");

    Where::ApplicationController app(argc, argv);
    app.loadQml("Main");

    return app.exec();
}
